"""Interactively chat with the trained model — it's forced to speak as
Munkhpurev, so you're talking to a simulation of him.

Run: python chat.py
Type your line as "Other: <text>" is added automatically; the model
always completes as "Munkhpurev: ...".
"""
import torch

from model import GPT

checkpoint_path = "checkpoint.pt"
device = "cuda" if torch.cuda.is_available() else "cpu"
you = "Other"
other = "Munkhpurev"


def main():
    ckpt = torch.load(checkpoint_path, map_location=device)
    chars = ckpt["vocab"]
    stoi = {ch: i for i, ch in enumerate(chars)}
    itos = {i: ch for i, ch in enumerate(chars)}

    def encode(s):
        return [stoi[c] for c in s if c in stoi]

    def decode(ids):
        return "".join(itos[i] for i in ids)

    cfg = ckpt["config"]
    model = GPT(len(chars), cfg["n_embd"], cfg["n_head"], cfg["n_layer"],
                cfg["block_size"], cfg["dropout"]).to(device)
    model.load_state_dict(ckpt["model"])
    model.eval()
    print(f"loaded checkpoint at iter {ckpt['iter']} (block_size={cfg['block_size']})")

    history = ""
    print("Type a message (empty line to quit).")
    while True:
        user_line = input(f"{you}> ").strip()
        if not user_line:
            break
        history += f"{you}: {user_line}\n"

        # Force the model to continue as `other` (Munkhpurev) by ending the
        # prompt with its name prefix, so it always speaks as him.
        prefix = f"{other}: "
        room = cfg["block_size"] - len(prefix)
        context = history[-room:] if room > 0 else ""
        prompt = context + prefix

        idx = torch.tensor([encode(prompt)], dtype=torch.long, device=device)
        out = model.generate(idx, max_new_tokens=200, temperature=0.8, top_k=40)
        generated = decode(out[0].tolist())[len(prompt):]
        reply = generated.split("\n")[0].strip() or "..."
        print(f"{other}> {reply}")
        history += f"{prefix}{reply}\n"


if __name__ == "__main__":
    main()
