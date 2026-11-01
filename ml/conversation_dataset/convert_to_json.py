#!/usr/bin/env python3
"""Convert a flat 'Name: text' training file into structured JSON.

Each conversation (blank-line-separated block) becomes an object with an
ordered list of turns: {"speaker": ..., "text": ...}. A turn's text can
itself contain newlines (merged consecutive messages), so only lines that
start with a known speaker prefix start a new turn — other lines are
continuations of the previous turn.
"""
import argparse
import json
from pathlib import Path

KNOWN_SPEAKERS = ["Munkhpurev", "Other", "Odmaa"]


def parse_block(block):
    turns = []
    for line in block.split("\n"):
        matched = False
        for speaker in KNOWN_SPEAKERS:
            prefix = speaker + ": "
            if line.startswith(prefix):
                turns.append({"speaker": speaker, "text": line[len(prefix):]})
                matched = True
                break
        if not matched:
            if turns:
                turns[-1]["text"] += "\n" + line
    return turns


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("input", help="flat training .txt file")
    ap.add_argument("output", nargs="?", help="output .json path (default: same name, .json)")
    args = ap.parse_args()

    in_path = Path(args.input)
    out_path = Path(args.output) if args.output else in_path.with_suffix(".json")

    text = in_path.read_text(encoding="utf-8")
    blocks = [b for b in text.split("\n\n") if b.strip()]

    conversations = []
    for block in blocks:
        turns = parse_block(block)
        if turns:
            conversations.append({"turns": turns})

    out_path.write_text(json.dumps(conversations, ensure_ascii=False, indent=2), encoding="utf-8")
    n_turns = sum(len(c["turns"]) for c in conversations)
    print(f"{len(conversations)} conversations, {n_turns} turns -> {out_path}")


if __name__ == "__main__":
    main()
