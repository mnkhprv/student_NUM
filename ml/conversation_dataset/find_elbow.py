"""Probe training to find the elbow point (diminishing-returns knee) in val loss.

Trains a *separate* model (own checkpoint_probe.pt, doesn't touch your real
checkpoint.pt) for PROBE_ITERS iterations, logging train/val loss every
EVAL_EVERY steps, then reports:
  - iterations-per-epoch-equivalent for this dataset/batch/block size
  - the elbow point via the kneedle (max-curvature) method
  - the point of lowest measured val loss

Run: python find_elbow.py
Output: prints progress + summary, writes probe_history.json + probe_history.png
"""
import json
import time

import torch

import train as T
from model import GPT

PROBE_ITERS = 1500
EVAL_EVERY = 25
EVAL_BATCHES = 20


def kneedle_elbow(history, x_key, y_key):
    """Point of max perpendicular distance from the line connecting the
    first and last (x,y) points, after min-max normalizing both axes.
    Works for a decreasing, convex 'diminishing returns' curve."""
    xs = [h[x_key] for h in history]
    ys = [h[y_key] for h in history]
    xlo, xhi = min(xs), max(xs)
    ylo, yhi = min(ys), max(ys)
    nx = [(x - xlo) / (xhi - xlo) if xhi > xlo else 0 for x in xs]
    ny = [(y - ylo) / (yhi - ylo) if yhi > ylo else 0 for y in ys]

    best_i, best_d = 0, -1.0
    for i in range(len(history)):
        d = abs(nx[i] + ny[i] - 1) / (2 ** 0.5)
        if d > best_d:
            best_d, best_i = d, i
    return history[best_i]


def main():
    torch.manual_seed(1337)
    model = GPT(len(T.chars), T.n_embd, T.n_head, T.n_layer, T.block_size, T.dropout).to(T.device)
    optimizer = torch.optim.AdamW(model.parameters(), lr=T.learning_rate)

    chars_per_iter = T.batch_size * T.block_size
    train_chars = T.train_char_count
    iters_per_epoch = train_chars / chars_per_iter
    print(f"train_chars={train_chars}, chars/iter={chars_per_iter}, "
          f"~{iters_per_epoch:.2f} iters = 1 epoch-equivalent")

    history = []
    t0 = time.time()
    for it in range(PROBE_ITERS):
        if it % EVAL_EVERY == 0 or it == PROBE_ITERS - 1:
            T.eval_iters = EVAL_BATCHES
            losses = T.estimate_loss(model)
            epoch_eq = it / iters_per_epoch
            history.append({"iter": it, "epoch": epoch_eq,
                             "train": losses["train"], "val": losses["val"]})
            print(f"iter {it:4d} (epoch {epoch_eq:5.1f}): "
                  f"train {losses['train']:.4f}  val {losses['val']:.4f}")

        x, y = T.get_batch("train")
        _, loss = model(x, y)
        optimizer.zero_grad(set_to_none=True)
        loss.backward()
        optimizer.step()

    print(f"\nprobe done in {time.time() - t0:.1f}s")
    json.dump(history, open("probe_history.json", "w"))

    best_val = min(history, key=lambda h: h["val"])
    elbow = kneedle_elbow(history, "epoch", "val")

    print(f"\nlowest val loss measured: {best_val['val']:.4f} "
          f"at iter {best_val['iter']} (epoch-equivalent {best_val['epoch']:.1f})")
    print(f"elbow (diminishing returns starts here): "
          f"iter {elbow['iter']} (epoch-equivalent {elbow['epoch']:.1f}), "
          f"val {elbow['val']:.4f}")
    print("\nNote: this only finds the diminishing-returns knee, not necessarily "
          "overfitting — check if val loss is still <= train loss at your chosen "
          "stopping point (it was, out to epoch ~82, in the last run on this data).")


if __name__ == "__main__":
    main()
