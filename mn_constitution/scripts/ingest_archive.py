"""Ingest legalinfo.mn acts from web.archive.org (legalinfo itself is unreachable from here).

  python3 scripts/ingest_archive.py index            # list every archived lawId + newest snapshot -> laws/_index.json
  python3 scripts/ingest_archive.py fetch [--all-acts] [--limit N] [--workers W] [ids...]   # default: laws in force only
  python3 scripts/ingest_archive.py retry [--workers W]   # empty shells / 404s: walk back through older snapshots
  python3 scripts/ingest_archive.py status

Each act -> constitution/text/laws/<lawId>.txt with a header: title, source url, snapshot timestamp.
Only laws («МОНГОЛ УЛСЫН ХУУЛЬ» header) without a whole-law repeal note are saved by default.
in_force=False when a repeal note is present; None = no repeal note in that snapshot
(presumed in force, not confirmed: legalinfo's status list is not archived).  Resumable: existing files are skipped.
"""
from __future__ import annotations

import html
import json
import re
import sys
import threading
import time
import urllib.error
from concurrent.futures import ThreadPoolExecutor
import unicodedata
import urllib.request
from pathlib import Path

DIR = Path(__file__).resolve().parent.parent / "constitution" / "text" / "laws"
INDEX = DIR / "_index.json"
CDX = "https://web.archive.org/cdx/search/cdx"
UA = {"User-Agent": "mn_constitution research (archive reader)"}
LOCK = threading.Lock()
PAUSE_UNTIL = [0.0]     # shared back-off: a 429 on any worker pauses all of them


def get(url: str, timeout=300, tries=6) -> str:
    for i in range(tries):
        while (w := PAUSE_UNTIL[0] - time.time()) > 0:
            time.sleep(w)
        try:
            with urllib.request.urlopen(urllib.request.Request(url, headers=UA), timeout=timeout) as r:
                body = r.read().decode("utf-8", "replace")
            if "Internet Archive: Temporarily Offline" in body[:500]:
                raise OSError("archive offline")
            return body
        except urllib.error.HTTPError as e:
            if e.code != 429 or i == tries - 1:
                raise
            with LOCK:
                PAUSE_UNTIL[0] = max(PAUSE_UNTIL[0], time.time() + 60 * (i + 1))
            print(f"  429 rate-limited: all workers pause {60 * (i + 1)}s", file=sys.stderr)
            continue
        except Exception as e:  # noqa: BLE001 — network: retry with backoff
            if i == tries - 1:
                raise
            if "Connection refused" in str(e):          # archive's soft rate limit: back off together
                with LOCK:
                    PAUSE_UNTIL[0] = max(PAUSE_UNTIL[0], time.time() + 30 * (i + 1))
                print(f"  refused: all workers pause {30 * (i + 1)}s", file=sys.stderr)
                continue
            print(f"  retry {i + 1}: {e}", file=sys.stderr)
            time.sleep(10 * (i + 1))


def build_index() -> dict:
    """lawId -> newest 200 snapshot timestamp, from the CDX API (paged by resumeKey)."""
    out, resume = {}, None
    while True:
        url = (f"{CDX}?url=legalinfo.mn/mn/detail?lawId=&matchType=prefix&filter=statuscode:200"
               "&fl=original,timestamp&output=json&limit=5000&showResumeKey=true")
        if resume:
            url += "&resumeKey=" + urllib.request.quote(resume)
        rows = json.loads(get(url) or "[]")
        resume = None
        if rows and rows[-1] and len(rows[-1]) == 1:          # [resumeKey] after an empty row
            resume = rows.pop()[0]
            if rows and not rows[-1]:
                rows.pop()
        for orig, ts in rows[1:]:
            m = re.search(r"lawId=(\d+)", orig)
            if m and ts > out.get(m[1], {}).get("ts", ""):
                out[m[1]] = {"ts": ts, "url": orig}
        print(f"  {len(out)} ids", file=sys.stderr)
        if not resume:
            return out


def extract(page: str) -> tuple[str, str]:
    """(title, Mongolian body text) from a legalinfo detail page."""
    title = html.unescape(re.search(r"<title>(.*?)</title>", page, re.S)[1]).strip()
    a = page.find('class="nom-more-content"')
    if a < 0:
        return title, ""
    b = min([i for i in (page.find("nom-more-divider", a), page.find("<footer", a)) if i > 0] or [len(page)])
    a = page.find(">", a) + 1
    b = page.rfind("<div", a, b) if page.rfind("<div", a, b) > a else b        # don't cut mid-tag
    seg = re.sub(r"(?s)<!--.*?-->|<(script|style)\b.*?</\1>", "", page[a:b])
    seg = re.sub(r"(?i)<br\s*/?>|</(p|div|h\d|li|tr)>", "\n", seg)
    seg = unicodedata.normalize("NFC", html.unescape(re.sub(r"<[^>]+>", "", seg)))
    lines = [re.sub(r"\s+", " ", l).strip() for l in seg.splitlines()]
    lines = [re.sub(r"^Хэвлэх", "", l) for l in lines if l and l not in ("Хэвлэх", "A", "-->")]   # Print / font-size UI
    lines = [re.sub(r'^[\w-]+:[^"<>]*">', "", l) for l in lines]                 # attribute tail leaked by a split tag
    if "Сонсох / Сонгосон утга сонсох" in lines:                                  # reader toolbar after the text
        lines = lines[:lines.index("Сонсох / Сонгосон утга сонсох")]
    return title, "\n".join(l for l in lines if l)


LAW_HEAD = re.compile(r"^МОНГОЛ УЛСЫН ХУУЛЬ$", re.M)
REPEAL = re.compile(r"Энэ хуулийг[\s\S]{0,400}?хүчингүй болсонд тооц", re.I)
FIRST_ART = re.compile(r"^(\d+\s*(дугаар|дүгээр)\s*зүйл|[А-ЯӨҮ]+ДУГААР БҮЛЭГ|[А-ЯӨҮ]+ДҮГЭЭР БҮЛЭГ)", re.M)


def is_law(body: str) -> bool:
    """legalinfo titles omit «хууль»; the body header says «МОНГОЛ УЛСЫН ХУУЛЬ» for a law
    (resolutions/decrees/orders carry other headers)."""
    return bool(LAW_HEAD.search(body[:2000]))


def is_repealed(title: str, body: str) -> bool:
    """Whole-law repeal note in the title or header (before the first article/chapter).
    «Энэ хэсгийг/заалтыг …» notes repeal only a part and are ignored."""
    m = FIRST_ART.search(body)
    return bool(REPEAL.search(title) or REPEAL.search(body[: m.start() if m else 3000]))


def fetch_one(lid: str, idx: dict, laws_only: bool):
    p, e = DIR / f"{lid}.txt", idx[lid]
    src = f"https://legalinfo.mn/mn/detail?lawId={lid}"
    t0 = time.time()
    try:
        page = get(f"https://web.archive.org/web/{e['ts']}id_/{e.get('url', src)}")
        title, body = extract(page)
    except Exception as ex:  # noqa: BLE001
        with LOCK:
            e["error"] = str(ex)
        print(f"{lid}: FAILED {ex}", flush=True)
        return
    with LOCK:
        law, rep = is_law(body), is_repealed(title, body)
        e.update(title=title, is_law=law, repealed=rep, in_force=False if rep else None, chars=len(body), error=None)
        if not body or (laws_only and (not law or rep)):
            e["skip"] = "no body" if not body else ("not a law" if not law else "repealed")
            print(f"{lid}: skip ({e['skip']}) {title[:60]}", flush=True)
        else:
            p.write_text(f"{title}\nЭх сурвалж: {src} (web.archive.org/web/{e['ts']})\n\n{body}\n", encoding="utf-8")
            print(f"{lid}: {len(body):>7} chars {time.time() - t0:5.0f}s  {e['ts'][:8]}  {title[:70]}", flush=True)
        INDEX.write_text(json.dumps(idx, ensure_ascii=False, indent=1), encoding="utf-8")


def fetch(ids: list[str], idx: dict, laws_only: bool, limit: int | None, workers: int):
    todo = [i for i in ids if i in idx and "ts" in idx[i] and not (DIR / f"{i}.txt").exists() and not idx[i].get("skip")]
    todo = todo[:limit] if limit is not None else todo
    print(f"{len(todo)} to fetch with {workers} workers", flush=True)
    t0 = time.time()
    with ThreadPoolExecutor(workers) as ex:
        list(ex.map(lambda i: fetch_one(i, idx, laws_only), todo))
    print(f"done in {(time.time() - t0) / 60:.1f} min", flush=True)


def snapshots(lid: str) -> list[str]:
    """All 200-status timestamps for one lawId, newest first."""
    rows = json.loads(get(f"{CDX}?url=legalinfo.mn/mn/detail?lawId={lid}&filter=statuscode:200"
                          "&fl=timestamp&output=json&collapse=digest") or "[]")
    return sorted((r[0] for r in rows[1:]), reverse=True)


def retry_one(lid: str, idx: dict, max_tries: int = 4):
    e, src = idx[lid], f"https://legalinfo.mn/mn/detail?lawId={lid}"
    try:
        older = [t for t in snapshots(lid) if t != e.get("ts")][:max_tries]
    except Exception as ex:  # noqa: BLE001
        print(f"{lid}: cdx failed {ex}", flush=True); return
    for ts in older:
        try:
            title, body = extract(get(f"https://web.archive.org/web/{ts}id_/{src}"))
        except Exception:  # noqa: BLE001
            continue
        if not body:
            continue
        law, rep = is_law(body), is_repealed(title, body)
        with LOCK:
            e.update(ts=ts, title=title, is_law=law, repealed=rep, in_force=False if rep else None,
                     chars=len(body), error=None, skip=None if law and not rep else ("not a law" if not law else "repealed"))
            if law and not rep:
                (DIR / f"{lid}.txt").write_text(f"{title}\nЭх сурвалж: {src} (web.archive.org/web/{ts})\n\n{body}\n", encoding="utf-8")
            INDEX.write_text(json.dumps(idx, ensure_ascii=False, indent=1), encoding="utf-8")
        print(f"{lid}: recovered from {ts[:8]} -> {e['skip'] or 'SAVED'}  {title[:60]}", flush=True)
        return
    with LOCK:
        e["retried"] = True
        INDEX.write_text(json.dumps(idx, ensure_ascii=False, indent=1), encoding="utf-8")
    print(f"{lid}: no older snapshot with text ({len(older)} tried)", flush=True)


def main(argv):
    DIR.mkdir(parents=True, exist_ok=True)
    idx = json.loads(INDEX.read_text(encoding="utf-8")) if INDEX.exists() else {}
    cmd = argv[0] if argv else "status"
    if cmd == "index":
        for k, v in build_index().items():
            idx.setdefault(k, {}).update(v)
        INDEX.write_text(json.dumps(idx, ensure_ascii=False, indent=1), encoding="utf-8")
        print(f"{len(idx)} ids -> {INDEX}")
    elif cmd == "fetch":
        args, limit = argv[1:], None
        if "--limit" in args:
            i = args.index("--limit"); limit = int(args[i + 1]); del args[i:i + 2]
        workers = 8
        if "--workers" in args:
            i = args.index("--workers"); workers = int(args[i + 1]); del args[i:i + 2]
        laws_only = "--all-acts" not in args
        ids = [a for a in args if a.isdigit()] or sorted(idx, key=int)
        fetch(ids, idx, laws_only, limit, workers)
    elif cmd == "retry":
        workers = int(argv[argv.index("--workers") + 1]) if "--workers" in argv else 8
        todo = [k for k, v in idx.items() if not v.get("retried") and not (DIR / f"{k}.txt").exists()
                and (v.get("skip") == "no body" or "404" in (v.get("error") or ""))]
        print(f"{len(todo)} to retry with {workers} workers", flush=True)
        t0 = time.time()
        with ThreadPoolExecutor(workers) as ex:
            list(ex.map(lambda i: retry_one(i, idx), todo))
        print(f"done in {(time.time() - t0) / 60:.1f} min", flush=True)
    else:
        got = [k for k in idx if (DIR / f"{k}.txt").exists()]
        from collections import Counter
        print(f"indexed {len(idx)}  saved {len(got)}  fetched {sum(1 for v in idx.values() if 'title' in v)}"
              f"  errors {sum(1 for v in idx.values() if v.get('error'))}")
        print("skipped:", dict(Counter(v["skip"] for v in idx.values() if v.get("skip"))))
        years = sorted(v["ts"][:4] for k, v in idx.items() if k in got)
        print("snapshot years:", {y: years.count(y) for y in sorted(set(years))})


if __name__ == "__main__":
    main(sys.argv[1:])
