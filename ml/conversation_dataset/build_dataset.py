#!/usr/bin/env python3
"""Turn raw Instagram/Messenger message_1.json exports into fine-tuning JSONL.

Reads every conversation_dataset_messages_only/<name>/message_1.json, and for
each writes a chat-style JSONL file where the export owner is "user" and the
other participant is "assistant". Also writes a combined dataset.jsonl.
"""
import json
import re
from pathlib import Path

ROOT = Path(__file__).parent / "conversation_dataset_messages_only"
OWNER = "Munkhpurev"

MERGE_GAP_MS = 2 * 60 * 1000       # merge same-sender messages within 2 min
EPISODE_GAP_MS = 6 * 60 * 60 * 1000  # start a new episode after a 6h silence

NOISE_PATTERNS = [
    re.compile(r"^.+ sent an attachment\.$"),
    re.compile(r"^Liked a message$"),
    re.compile(r"^.+ liked a message$"),
    re.compile(r"^.+ set the .+ theme\.$"),
    re.compile(r"^.+ (missed a video chat|missed a call)\.?$"),
    re.compile(r"^Reacted .+ to your message\s*$"),
    re.compile(r"^You are now connected on Messenger\.?$"),
    re.compile(r"^You're now friends with .+\.?$"),
    re.compile(r"^You can now message and call each other.*$"),
    re.compile(r"^This account was created before.*$"),
    re.compile(r"^(You started|.+ started) (a video chat|an audio call)\.?$"),
    re.compile(r"^(Video chat|Audio call) ended\.?$"),
    re.compile(r"^.+ changed the group photo\.?$"),
    re.compile(r"^.+ (added|removed|left the group|joined the (group|call))\.?$"),
]


def fix_mojibake(text):
    try:
        return text.encode("latin1").decode("utf-8")
    except (UnicodeDecodeError, UnicodeEncodeError):
        return text


def is_noise(content):
    return any(p.match(content) for p in NOISE_PATTERNS)


def load_messages(path):
    data = json.loads(path.read_text(encoding="utf-8"))
    participants = [p["name"] for p in data["participants"]]
    other = next(p for p in participants if p != OWNER)

    cleaned = []
    for m in data["messages"]:
        content = m.get("content")
        if not content:
            continue  # photo/video/audio-only message, no text
        content = fix_mojibake(content).strip()
        if not content or is_noise(content):
            continue
        cleaned.append({
            "sender": fix_mojibake(m["sender_name"]),
            "ts": m["timestamp_ms"],
            "content": content,
        })

    cleaned.sort(key=lambda m: m["ts"])
    return other, cleaned


def merge_consecutive(messages):
    """Collapse same-sender messages sent within MERGE_GAP_MS into one turn."""
    turns = []
    for m in messages:
        if (turns
                and turns[-1]["sender"] == m["sender"]
                and m["ts"] - turns[-1]["ts"] <= MERGE_GAP_MS):
            turns[-1]["content"] += "\n" + m["content"]
            turns[-1]["ts"] = m["ts"]
        else:
            turns.append(dict(m))
    return turns


def split_episodes(turns):
    episodes, current = [], []
    for t in turns:
        if current and t["ts"] - current[-1]["ts"] > EPISODE_GAP_MS:
            episodes.append(current)
            current = []
        current.append(t)
    if current:
        episodes.append(current)
    return episodes


def role_for(sender, other):
    return "user" if sender == OWNER else "assistant"


def episode_to_example(episode, other):
    msgs = [{"role": "system", "content": f"You are {other}. Reply the way they text."}]
    for turn in episode:
        msgs.append({"role": role_for(turn["sender"], other), "content": turn["content"]})
    # need at least one turn from each side to be a useful training example
    roles = {m["role"] for m in msgs[1:]}
    if not {"user", "assistant"} <= roles:
        return None
    return {"messages": msgs}


def build_for_source(dir_path):
    other, cleaned = load_messages(dir_path / "message_1.json")
    turns = merge_consecutive(cleaned)
    episodes = split_episodes(turns)
    examples = [episode_to_example(ep, other) for ep in episodes]
    return other, [e for e in examples if e is not None]


def main():
    combined = []
    for source_dir in sorted(ROOT.iterdir()):
        if not source_dir.is_dir():
            continue
        msg_file = source_dir / "message_1.json"
        if not msg_file.exists():
            continue

        other, examples = build_for_source(source_dir)
        out_path = source_dir / "dataset.jsonl"
        with out_path.open("w", encoding="utf-8") as f:
            for ex in examples:
                f.write(json.dumps(ex, ensure_ascii=False) + "\n")
        combined.extend(examples)
        print(f"{source_dir.name:35s} -> {len(examples):4d} examples ({other})")

    combined_path = ROOT / "dataset.jsonl"
    with combined_path.open("w", encoding="utf-8") as f:
        for ex in combined:
            f.write(json.dumps(ex, ensure_ascii=False) + "\n")
    print(f"\nTotal: {len(combined)} examples -> {combined_path}")


if __name__ == "__main__":
    main()
