#!/usr/bin/env python3
"""Build one flat munkhpurev_training_data.txt from ALL available exports.

Unlike prepare_data.py (which only used the 3 curated Odmaa/Scarlet
conversations), this walks every Facebook export, the Instagram export, and
the third-party 'messages/' export, groups files belonging to the same
thread (a thread can be split across multiple message_N.json files, and can
appear in more than one Facebook export if Meta split a big data request
into several downloads), dedupes messages, and concatenates every
conversation into one corpus — so we can train a model on Munkhpurev's
overall texting style, not just one relationship.
"""
import json
from collections import defaultdict
from pathlib import Path

from text_utils import (fix_mojibake, force_alternate, is_business_signal,
                         is_noise, transliterate)

ROOT = Path(__file__).parent
OWNER = "Munkhpurev"
OUT_PATH = ROOT / "munkhpurev_training_data.txt"

FACEBOOK_ROOTS = sorted(ROOT.glob("facebook-munkhpurev2025-*"))
INSTAGRAM_ROOTS = sorted(ROOT.glob("instagram-*"))
THIRD_PARTY_DIR = ROOT / "messages"

MIN_MESSAGES_PER_THREAD = 2


def extract_messages(json_path):
    """Yield (timestamp_ms, sender, content) for one message file,
    supporting both the official Meta schema and the third-party one."""
    try:
        data = json.loads(json_path.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, UnicodeDecodeError):
        return
    for m in data.get("messages", []):
        content = m.get("content") or m.get("text")
        if not content:
            continue
        content = fix_mojibake(content).strip()
        if not content or is_noise(content):
            continue
        content = transliterate(content)
        sender_raw = m.get("sender_name") or m.get("senderName")
        if not sender_raw:
            continue
        sender = fix_mojibake(sender_raw)
        ts = m.get("timestamp_ms", m.get("timestamp"))
        if ts is None:
            continue
        yield ts, sender, content


def collect_threads():
    """thread_key -> list of message json file Paths belonging to it."""
    threads = defaultdict(list)

    for fb_root in FACEBOOK_ROOTS:
        messages_dir = fb_root / "your_facebook_activity" / "messages"
        if not messages_dir.exists():
            continue
        for msg_file in messages_dir.rglob("message_*.json"):
            thread_key = "fb:" + msg_file.parent.name
            threads[thread_key].append(msg_file)

    for ig_root in INSTAGRAM_ROOTS:
        messages_dir = ig_root / "your_instagram_activity" / "messages" / "inbox"
        if not messages_dir.exists():
            continue
        for msg_file in messages_dir.rglob("message_*.json"):
            thread_key = "ig:" + msg_file.parent.name
            threads[thread_key].append(msg_file)

    if THIRD_PARTY_DIR.exists():
        for msg_file in THIRD_PARTY_DIR.glob("*.json"):
            thread_key = "tp:" + msg_file.stem
            threads[thread_key].append(msg_file)

    return threads


def build_thread_text(files):
    seen = set()
    rows = []
    for f in files:
        for ts, sender, content in extract_messages(f):
            key = (ts, sender, content)
            if key in seen:
                continue
            seen.add(key)
            rows.append((ts, sender, content))
    rows.sort(key=lambda r: r[0])
    return rows


OTHER_LABEL = "Other"


def main():
    threads = collect_threads()
    print(f"found {len(threads)} distinct threads across "
          f"{len(FACEBOOK_ROOTS)} facebook export(s), "
          f"{len(INSTAGRAM_ROOTS)} instagram export(s), "
          f"and the third-party export.")

    chunks = []
    kept = skipped_small = skipped_no_owner = skipped_group = skipped_business = 0
    for thread_key in sorted(threads):
        rows = build_thread_text(threads[thread_key])
        if len(rows) < MIN_MESSAGES_PER_THREAD:
            skipped_small += 1
            continue
        senders = {r[1] for r in rows}
        if OWNER not in senders:
            skipped_no_owner += 1
            continue
        if len(senders) != 2:
            # only keep clean one-on-one threads: Munkhpurev + exactly one
            # other person. Group chats have 3+ senders and would make
            # 'Other' look like one person replying to itself.
            skipped_group += 1
            continue
        if any(is_business_signal(content) for _, sender, content in rows):
            # this "person" is a business page / customer-service bot, not
            # a real friend — drop the whole thread, not just the giveaway line.
            skipped_business += 1
            continue
        rows = force_alternate(rows)
        text = "\n".join(
            f"{OWNER if sender == OWNER else OTHER_LABEL}: {content}"
            for _, sender, content in rows
        )
        chunks.append(text)
        kept += 1

    full_text = "\n\n".join(chunks) + "\n"
    OUT_PATH.write_text(full_text, encoding="utf-8")

    vocab = sorted(set(full_text))
    print(f"kept {kept} threads (skipped {skipped_small} too-small, "
          f"{skipped_no_owner} without {OWNER}, {skipped_group} group chats, "
          f"{skipped_business} business/bot threads)")
    print(f"Total: {len(full_text)} chars, vocab size {len(vocab)}")
    print(f"Wrote {OUT_PATH}")


if __name__ == "__main__":
    main()
