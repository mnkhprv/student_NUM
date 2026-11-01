#!/usr/bin/env python3
"""Build one flat training_data.txt from the raw message exports.

Unlike build_dataset.py (which produced structured JSONL), this writes a
plain chat-log text file — "Name: message" lines, chronological, all three
conversations concatenated — for a character-level GPT trained from scratch.
"""
import json
from pathlib import Path

from text_utils import fix_mojibake, force_alternate, is_noise, transliterate

ROOT = Path(__file__).parent / "conversation_dataset_messages_only"
OWNER = "Munkhpurev"
OUT_PATH = Path(__file__).parent / "training_data.txt"

# Collapse per-platform usernames to one static name per real person.
SENDER_ALIASES = {
    "odmabe": "Odmaa",
    "Odmaa Bayasgalan": "Odmaa",
    "scarletheartryeoe": "Odmaa",
}


def load_lines(path):
    data = json.loads(path.read_text(encoding="utf-8"))
    lines = []
    for m in data["messages"]:
        # two export schemas seen so far:
        #   official Meta export: content / sender_name / timestamp_ms
        #   third-party export:   text / senderName / timestamp
        content = m.get("content") or m.get("text")
        if not content:
            continue
        content = fix_mojibake(content).strip()
        if not content or is_noise(content):
            continue
        content = transliterate(content)
        sender_raw = m.get("sender_name") or m.get("senderName")
        sender = fix_mojibake(sender_raw)
        sender = SENDER_ALIASES.get(sender, sender)
        ts = m.get("timestamp_ms")
        if ts is None:
            ts = m["timestamp"]
        lines.append((ts, sender, content))
    lines.sort(key=lambda x: x[0])
    return lines


def main():
    chunks = []
    for source_dir in sorted(ROOT.iterdir()):
        msg_file = source_dir / "message_1.json"
        if not msg_file.exists():
            continue
        lines = load_lines(msg_file)
        lines = force_alternate(lines)
        text = "\n".join(f"{sender}: {content}" for _, sender, content in lines)
        chunks.append(text)
        print(f"{source_dir.name:35s} -> {len(lines):5d} lines, {len(text):7d} chars")

    full_text = "\n\n".join(chunks) + "\n"
    OUT_PATH.write_text(full_text, encoding="utf-8")

    vocab = sorted(set(full_text))
    print(f"\nTotal: {len(full_text)} chars, vocab size {len(vocab)}")
    print(f"Wrote {OUT_PATH}")


if __name__ == "__main__":
    main()
