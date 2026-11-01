"""Train the char-level GPT on munkhpurev_training_data.json, from scratch.

Unlike the old flat-.txt version, this samples training windows from
*within a single conversation* only, using the JSON's explicit conversation
boundaries — a random block_size window can no longer straddle two
unrelated conversations the way naive whole-corpus sampling could.

Run: python train.py
Resumes automatically from checkpoint.pt if it exists.
"""
import json
import random

import torch

from model import GPT

# --- hyperparameters (~2.1M chars of data, sized for GPU training e.g. Kaggle) ---
data_path = "munkhpurev_training_data.json"
checkpoint_path = "checkpoint.pt"
block_size = 256       # how many characters of context per prediction
batch_size = 64
n_embd = 384
n_head = 6
n_layer = 6
dropout = 0.2
learning_rate = 1e-3
max_iters = 5000
eval_interval = 250
eval_iters = 100
train_frac = 0.9
device = "cuda" if torch.cuda.is_available() else "cpu"

torch.manual_seed(1337)
split_rng = random.Random(1337)

# --- data ---
with open(data_path, "r", encoding="utf-8") as f:
    conversations = json.load(f)


def conv_to_text(conv):
    return "\n".join(f"{t['speaker']}: {t['text']}" for t in conv["turns"])


conv_texts = [conv_to_text(c) for c in conversations]

chars = sorted(set("\n".join(conv_texts)))
vocab_size = len(chars)
stoi = {ch: i for i, ch in enumerate(chars)}
itos = {i: ch for i, ch in enumerate(chars)}


def encode(s):
    return [stoi[c] for c in s]


def decode(ids):
    return "".join(itos[i] for i in ids)


# split by conversation (not by raw char position), so train/val never
# share a conversation
order = list(range(len(conv_texts)))
split_rng.shuffle(order)
n_train_convs = int(train_frac * len(order))
train_idx, val_idx = order[:n_train_convs], order[n_train_convs:]

train_convs = [torch.tensor(encode(conv_texts[i]), dtype=torch.long) for i in train_idx]
val_convs = [torch.tensor(encode(conv_texts[i]), dtype=torch.long) for i in val_idx]
train_weights = [len(c) for c in train_convs]
val_weights = [len(c) for c in val_convs]

train_char_count = sum(train_weights)
val_char_count = sum(val_weights)


def get_batch(split):
    convs, weights = (train_convs, train_weights) if split == "train" else (val_convs, val_weights)
    picks = random.choices(convs, weights=weights, k=batch_size)
    xs, ys = [], []
    for conv in picks:
        if len(conv) < block_size + 1:
            # too short for a full window on its own: cyclically repeat
            # this conversation's own text to fill it, rather than reaching
            # into a different, unrelated conversation
            reps = block_size // len(conv) + 2
            conv = conv.repeat(reps)
        i = random.randint(0, len(conv) - block_size - 1)
        xs.append(conv[i:i + block_size])
        ys.append(conv[i + 1:i + block_size + 1])
    x = torch.stack(xs).to(device)
    y = torch.stack(ys).to(device)
    return x, y


@torch.no_grad()
def estimate_loss(model):
    model.eval()
    out = {}
    for split in ("train", "val"):
        losses = torch.zeros(eval_iters)
        for k in range(eval_iters):
            x, y = get_batch(split)
            _, loss = model(x, y)
            losses[k] = loss.item()
        out[split] = losses.mean().item()
    model.train()
    return out


def main():
    total_chars = train_char_count + val_char_count
    print(f"data: {len(conv_texts)} conversations, {total_chars} chars, "
          f"vocab_size: {vocab_size}, device: {device}")
    print(f"train: {len(train_convs)} conversations ({train_char_count} chars), "
          f"val: {len(val_convs)} conversations ({val_char_count} chars)")

    model = GPT(vocab_size, n_embd, n_head, n_layer, block_size, dropout).to(device)
    optimizer = torch.optim.AdamW(model.parameters(), lr=learning_rate)
    start_iter = 0

    try:
        ckpt = torch.load(checkpoint_path, map_location=device)
        model.load_state_dict(ckpt["model"])
        optimizer.load_state_dict(ckpt["optimizer"])
        start_iter = ckpt["iter"] + 1
        print(f"resumed from {checkpoint_path} at iter {start_iter}")
    except FileNotFoundError:
        # Karpathy's sanity check: a randomly-initialized model predicting
        # uniformly over vocab_size classes should start near -ln(1/vocab_size)
        import math
        expected = -math.log(1 / vocab_size)
        x, y = get_batch("train")
        _, loss = model(x, y)
        print(f"initial loss: {loss.item():.4f} (expected ~{expected:.4f} if untrained)")

    n_params = sum(p.numel() for p in model.parameters())
    print(f"model params: {n_params:,}")

    for it in range(start_iter, max_iters):
        if it % eval_interval == 0 or it == max_iters - 1:
            losses = estimate_loss(model)
            print(f"step {it}: train loss {losses['train']:.4f}, val loss {losses['val']:.4f}")
            torch.save({
                "model": model.state_dict(),
                "optimizer": optimizer.state_dict(),
                "iter": it,
                "vocab": chars,
                "config": dict(n_embd=n_embd, n_head=n_head, n_layer=n_layer,
                                block_size=block_size, dropout=dropout),
            }, checkpoint_path)

        x, y = get_batch("train")
        _, loss = model(x, y)
        optimizer.zero_grad(set_to_none=True)
        loss.backward()
        optimizer.step()

    print("done training.")


if __name__ == "__main__":
    main()
