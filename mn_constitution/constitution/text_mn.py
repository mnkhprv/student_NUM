"""Parse the official Mongolian text into articles / sections / sub-items,
and analyse its normative language directly (no translation involved)."""
from __future__ import annotations

import re
from dataclasses import dataclass, field
from pathlib import Path

TEXT_PATH = Path(__file__).parent / "text" / "undsen_khuuli_mn.txt"

UNITS = {"нэг": 1, "хоёр": 2, "гурав": 3, "дөрөв": 4, "тав": 5,
         "зургаа": 6, "зурга": 6, "долоо": 7, "дол": 7, "найм": 8, "ес": 9}
TENS_ATTR = {"арван": 10, "хорин": 20, "гучин": 30, "дөчин": 40, "тавин": 50, "жаран": 60, "далан": 70}
TENS_ORD = {"арав": 10, "хорь": 20, "гуч": 30, "дөч": 40, "тавь": 50, "жар": 60, "дал": 70}
ORD_SUFFIX = re.compile(r"(дугаар|дүгээр)$")

HEADING = re.compile(r"^([А-ЯӨҮЁа-яөүё ]+?)(1)? ?(дугаар|дүгээр)? зүйл\.$")
SECTION = re.compile(r"^(\d+)\.(.*)$")
ITEM = re.compile(r"^(\d+)/(.*)$")
NOTE = re.compile(r"^/(.*)/$")
CHAPTER = re.compile(r"^[А-ЯӨҮЁ]+ БҮЛЭГ$")


def ordinal_to_int(words: str) -> int:
    """'Гучин гуравдугаар' -> 33, 'Далдугаар' -> 70, 'Арван ес' (+1 suffix) -> 19."""
    parts = words.lower().split()
    total = 0
    for w in parts:
        w = ORD_SUFFIX.sub("", w)
        if w in TENS_ATTR:
            total += TENS_ATTR[w]
        elif w in TENS_ORD:
            total += TENS_ORD[w]
        elif w in UNITS:
            total += UNITS[w]
        else:
            raise ValueError(f"unknown numeral word: {w!r} in {words!r}")
    return total


@dataclass
class Section:
    pid: str
    text: str
    items: dict[str, str] = field(default_factory=dict)
    notes: list[str] = field(default_factory=list)

    def full_text(self) -> str:
        return " ".join([self.text, *self.items.values()]).strip()


@dataclass
class ArticleText:
    number: str
    heading: str
    chapter: int
    preamble: str = ""
    sections: dict[str, Section] = field(default_factory=dict)
    notes: list[str] = field(default_factory=list)

    def full_text(self) -> str:
        return " ".join([self.preamble, *(s.full_text() for s in self.sections.values())]).strip()


def parse(path: Path = TEXT_PATH) -> dict[str, ArticleText]:
    arts: dict[str, ArticleText] = {}
    cur: ArticleText | None = None
    sec: Section | None = None
    chapter = 0
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line:
            continue
        if CHAPTER.match(line):
            chapter += 1
            cur, sec = None, None   # skip the chapter title line(s)
            continue
        m = HEADING.match(line)
        if m:
            n = ordinal_to_int(m.group(1).strip())
            num = f"{n}¹" if m.group(2) else str(n)
            cur = ArticleText(num, line, chapter)
            arts[num] = cur
            sec = None
            continue
        if cur is None:
            continue
        nm = NOTE.match(line)
        if nm:
            (sec.notes if sec else cur.notes).append(nm.group(1))
            continue
        im = ITEM.match(line)
        if im:
            if sec is None:  # Art. 16 has items directly under the article
                sec = cur.sections.setdefault(cur.number, Section(cur.number, cur.preamble))
            sec.items[f"{sec.pid}.{im.group(1)}" if sec.pid != cur.number else f"{cur.number}.{im.group(1)}"] = im.group(2).strip()
            continue
        sm = SECTION.match(line)
        if sm:
            pid = f"{cur.number}.{sm.group(1)}"
            sec = Section(pid, sm.group(2).strip())
            cur.sections[pid] = sec
            continue
        # continuation / preamble line
        if sec is None:
            cur.preamble = (cur.preamble + " " + line).strip()
        else:
            sec.text = (sec.text + " " + line).strip()
    return arts


def lookup(arts: dict[str, ArticleText], pid: str) -> str:
    """Best-effort text for a provision id like '33.1.1', '6.2.c', '19¹.3', '20'."""
    parts = pid.split(".")
    art = arts.get(parts[0])
    if art is None:
        return ""
    if len(parts) == 1:
        return art.full_text()
    sec = art.sections.get(f"{parts[0]}.{parts[1]}")
    if sec is None:  # Art. 16 style: items hang off the article
        sec = art.sections.get(parts[0])
        return sec.items.get(f"{parts[0]}.{parts[1]}", "") if sec else ""
    if len(parts) >= 3 and parts[2].isdigit():
        return sec.items.get(f"{sec.pid}.{parts[2]}", sec.full_text())
    return sec.full_text()


# ── Normative modality on the Mongolian wording ──────────────────────────
MODALITY = [
    ("prohibition", re.compile(r"хориглоно|үл болно|болохгүй|эрхгүй|үл хөндөнө|хуулиар хязгаарлахгүй|дагаж мөрдөхгүй|хавсарч болохгүй")),
    ("obligation", re.compile(r"үүрэгтэй|үүргийг .{0,40}хариуцна|заавал биелүүлнэ|төлнө|хангана\b")),
    ("right", re.compile(r"эрхтэй|эрх чөлөөтэй|эдэлнэ")),
    ("permission", re.compile(r"болно\b|болох\b")),
    ("soft", re.compile(r"байвал зохино|баримтлах|хүндэтгэж|дээдэлнэ")),
]
DELEGATION = re.compile(
    r"хуулиар (?:тогтоон? ?|тогтооно|тогтоож|хамгаална|зохицуулна|бататгана|хязгаарлаж|олгож|тусгайлан|ногдуулсан)"
    r"|хуульд (?:заасан|зааснаар|тусгайлан)|хуулийн дагуу")
SENT_SPLIT = re.compile(r"(?<=[.;:])\s+")


def sentences(text: str) -> list[str]:
    return [s.strip() for s in SENT_SPLIT.split(text) if s.strip()]


def classify(sentence: str) -> str:
    for name, rx in MODALITY:
        if rx.search(sentence):
            return name
    return "descriptive"


def linguistic_profile(arts: dict[str, ArticleText]) -> dict:
    counts: dict[str, int] = {}
    delegations: list[tuple[str, str]] = []
    per_article: dict[str, dict] = {}
    for num, a in arts.items():
        units = [(num, a.preamble)] if a.preamble else []
        for s in a.sections.values():
            units.append((s.pid, s.text))
            units += list(s.items.items())
        art_counts: dict[str, int] = {}
        for pid, text in units:
            for sent in sentences(text):
                c = classify(sent)
                counts[c] = counts.get(c, 0) + 1
                art_counts[c] = art_counts.get(c, 0) + 1
                for m in DELEGATION.finditer(sent):
                    delegations.append((pid, m.group(0)))
        per_article[num] = art_counts
    total = sum(counts.values())
    return {
        "sentences": total,
        "modality": counts,
        "modality_share": {k: round(v / total, 3) for k, v in counts.items()},
        "delegation_count": len(delegations),
        "delegations": delegations,
        "per_article": per_article,
    }


def amendment_history(arts: dict[str, ArticleText]) -> list[dict]:
    year = re.compile(r"(19\d\d|20\d\d) оны")
    out = []
    for num, a in arts.items():
        for where, notes in [(num, a.notes), *((s.pid, s.notes) for s in a.sections.values())]:
            for n in notes:
                out.append({"pid": where, "years": sorted(set(map(int, year.findall(n)))),
                            "annulled_by_tsets": "цэцийн" in n.lower() and "хүчингүй" in n, "note": n})
    return out
