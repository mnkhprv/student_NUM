"""Ordinary/organic laws that the constitution delegates to (texts in constitution/text/laws/<key>.txt).

  python3 -m constitution.laws          # registry status + every delegation sentence to close
"""
from __future__ import annotations

import json
import re
from dataclasses import dataclass, field
from pathlib import Path

from .text_mn import parse, sentences, DELEGATION

DIR = Path(__file__).parent / "text" / "laws"
ART = re.compile(r"^(\d+)\s*(?:дугаар|дүгээр)?\s*зүйл\.?\s*(.*)$")   # '12 дугаар зүйл. Гарчиг' or '12.Гарчиг' headers
ITEM3 = re.compile(r"^(\d+)\.(\d+)\.(\d+)\.\s*(.*)$")  # new style item: '46.1.4.text' -> '46.1.4'
SEC = re.compile(r"^(\d+)\.(\d+)\.\s*(.*)$")          # new style: '12.3.text'
OLD_SEC = re.compile(r"^(\d+)\.(?!\d)\s*(.*)$")         # old style: '3.text' inside article 12 -> 12.3
NOTE = re.compile(r"^/.*/$")
CAPS = re.compile(r"^[^а-яөүё]{4,}$")                  # chapter heading / signature line: no lowercase letters


@dataclass
class LawArticle:
    number: int
    title: str
    sections: dict[str, str] = field(default_factory=dict)   # "12.3" -> text; "12" = unnumbered body
    notes: list[str] = field(default_factory=list)            # /…/ amendment notes


def registry() -> list[dict]:
    return json.loads((DIR / "registry.json").read_text(encoding="utf-8"))["laws"]


def parse_law(text: str) -> dict[int, LawArticle]:
    arts, cur, last = {}, None, None
    for line in (l.strip() for l in text.splitlines()):
        if not line:
            continue
        if m := ART.match(line):
            cur = arts[int(m[1])] = LawArticle(int(m[1]), m[2]); last = None
        elif cur is None:
            continue
        elif NOTE.match(line):
            cur.notes.append(line)
        elif CAPS.match(line) and not re.match(r"^\d", line):
            last = None; cur = None                     # structure ends the article until the next heading
        elif (m := ITEM3.match(line)) and int(m[1]) == cur.number:
            last = f"{m[1]}.{m[2]}.{m[3]}"; cur.sections[last] = m[4]
        elif (m := SEC.match(line)) and int(m[1]) == cur.number:
            last = f"{m[1]}.{m[2]}"; cur.sections[last] = m[3]
        elif (m := OLD_SEC.match(line)) and not SEC.match(line) and not ITEM3.match(line):
            last = f"{cur.number}.{m[1]}"; cur.sections[last] = m[2]
        elif last:
            cur.sections[last] += " " + line
        else:
            last = str(cur.number); cur.sections[last] = line
    return arts


def index() -> dict[str, dict]:
    """lawId -> {title, ts, in_force (always None: unknown), ...}, written by scripts/ingest_archive.py."""
    p = DIR / "_index.json"
    return json.loads(p.read_text(encoding="utf-8")) if p.exists() else {}


def corpus() -> dict[str, str]:
    """lawId -> title for every saved law text."""
    return {k: v.get("title", "") for k, v in index().items() if (DIR / f"{k}.txt").exists()}


def load(key: str) -> dict[int, LawArticle] | None:
    """key = a lawId ('367') or a registry key ('hural', resolved through its law_id)."""
    if not key.isdigit():
        key = str(next((r["law_id"] for r in registry() if r["key"] == key and r["law_id"]), key))
    p = DIR / f"{key}.txt"
    return parse_law(p.read_text(encoding="utf-8")) if p.exists() else None


def q_law(key: str, pid: str | int, phrase: str) -> str:
    """Verbatim guard for ordinary laws, same contract as checks.q().
    pid = '35.2' (that section) or '35' / 35 (anywhere in the article)."""
    pid = str(pid); n = int(pid.split(".")[0])
    a = (load(key) or {}).get(n)
    blob = (a.sections.get(pid, "") if "." in pid else " ".join(a.sections.values())) if a else ""
    if phrase not in blob:
        raise ValueError(f"{key} {pid}: «{phrase}» эхэд байхгүй")
    return f"[TEXT law {key} {pid}: «{phrase}»]"


def q_law_note(key: str, art: int, phrase: str) -> str:
    """Verbatim guard for an amendment/annulment note (/…/) of a law article."""
    a = (load(key) or {}).get(int(art))
    if not a or not any(phrase in n for n in a.notes):
        raise ValueError(f"{key} {art} (тэмдэглэл): «{phrase}» эхэд байхгүй")
    return f"[TEXT law {key} {art} note: «{phrase}»]"


INLINE_ITEM = re.compile(r"(?:^|(?<=[:;.]) )(\d+)/")


def _units(sec):
    """(pid, text) per addressable unit: lead text, then items ('16.14', '17.1.3'), incl. items inlined on one line."""
    head, *rest = INLINE_ITEM.split(sec.text)
    if head.strip():
        yield sec.pid, head.strip()
    for n, t in zip(rest[::2], rest[1::2]):
        yield f"{sec.pid}.{n}", t.strip()
    yield from sec.items.items()


def delegation_index() -> list[tuple[str, str]]:
    """(constitution pid, sentence) for every sentence that hands content to a statute."""
    out = []
    for a in parse().values():
        for sec in a.sections.values():
            for pid, text in _units(sec):
                out.extend((pid, s) for s in sentences(text) if DELEGATION.search(s))
    return out


def _norm(t: str) -> str:
    t = re.sub(r"/[^/]*/?", " ", t).upper().replace("Y", "Ү")           # drop /notes/ and /Шинэчилсэн найруулга/; Latin Y typo
    t = re.sub(r"\s+", " ", t).strip()
    t = re.sub(r"^(МОНГОЛ )?УЛСЫН ", "", t)
    return re.sub(r" ХУУЛЬ$", "", t)


def link_registry() -> list[str]:
    """Fill law_id for registry entries whose title exactly matches a saved law (never guesses)."""
    p = DIR / "registry.json"
    data, c = json.loads(p.read_text(encoding="utf-8")), corpus()
    by_title: dict[str, list[str]] = {}
    for k, t in c.items():
        by_title.setdefault(_norm(t), []).append(k)
    msgs = []
    for r in data["laws"]:
        hits = by_title.get(_norm(r["title_mn"]), [])
        if r["law_id"] or not hits:
            continue
        if len(hits) == 1:
            r.update(law_id=int(hits[0]), verified=True); msgs.append(f"{r['key']} -> {hits[0]}")
        else:
            msgs.append(f"{r['key']}: several matches {hits}, left empty")
    p.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    return msgs


def delegation_coverage() -> list[tuple[str, str, str]]:
    """(pid, registry key or '', 'text' | 'missing' | 'unmapped') for each delegation sentence."""
    c, pid2 = corpus(), {}
    for r in registry():
        for pid in r.get("delegations", []):
            pid2[pid] = r
    out = []
    for pid, _ in delegation_index():
        r = pid2.get(pid)
        out.append((pid, r["key"] if r else "", "unmapped" if not r else
                    ("text" if r["law_id"] and str(r["law_id"]) in c else "missing")))
    return out


if __name__ == "__main__":
    import sys
    if "--link" in sys.argv:
        print("\n".join(link_registry()) or "no new matches")
    c = corpus()
    print(f"corpus: {len(c)} saved texts (in-force status unknown for all)\n")
    for r in registry():
        st = "TEXT OK" if r["law_id"] and str(r["law_id"]) in c else "missing"
        print(f"{r['key']:11} id={r['law_id']!s:5} {st:8} {r['title_mn']}")
    from collections import Counter
    cov = delegation_coverage()
    print(f"\n{len(cov)} delegation sentences:", dict(Counter(st for _, _, st in cov)))
    for (pid, s), (_, key, st) in zip(delegation_index(), cov):
        print(f"  {pid:8} {st:8} {key:10} {s[:90]}")
