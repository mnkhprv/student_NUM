"""Build report.json (for the explorer) and REPORT.md (Mongolian)."""
from __future__ import annotations

import json
from collections import Counter
from dataclasses import asdict
from pathlib import Path

from . import checks, stress
from .articles import ARTICLES, TOTAL_SEATS
from .procedures import MACHINES
from .text_mn import amendment_history, linguistic_profile, lookup, parse

SEV_MN = {"critical": "Ноцтой", "high": "Өндөр", "medium": "Дунд", "low": "Бага"}
CAT_MN = {"bug": "Алдаа (bug)", "design": "Загварын сул тал", "text": "Найруулгын алдаа"}
VERDICT_MN = {"pass": "Тэнцсэн", "partial": "Хэсэгчлэн", "fail": "Унасан"}


def build() -> dict:
    arts = parse()
    findings = checks.run_all()
    results = stress.run_all()
    prof = linguistic_profile(arts)
    by_article: dict[str, list[int]] = {}
    for i, f in enumerate(findings):
        for a in f.articles:
            num = a.split(".")[0]
            if num in arts:
                by_article.setdefault(num, []).append(i)
    return {
        "source": "https://legalinfo.mn/mn/detail?lawId=367",
        "fetched": "2026-10-29",
        "total_seats": TOTAL_SEATS,
        "summary": {
            "articles": len(arts),
            "findings": len(findings),
            "by_severity": dict(Counter(f.severity for f in findings)),
            "by_category": dict(Counter(f.category for f in findings)),
            "stress": dict(Counter(r.verdict for r in results)),
        },
        "articles": [{
            "number": a.number, "chapter": arts[a.number].chapter if a.number in arts else a.chapter,
            "title": a.title, "text": arts[a.number].full_text() if a.number in arts else "",
            "provisions": [{"pid": p.pid, "kind": p.kind.value, "actor": p.actor, "summary": p.summary,
                            "delegates": p.delegates, "limits": p.limits, "amended": list(p.amended)} for p in a.provisions],
            "findings": by_article.get(a.number, []),
            "modality": prof["per_article"].get(a.number, {}),
        } for a in ARTICLES],
        "findings": [asdict(f) for f in findings],
        "stress": [asdict(r) for r in results],
        "capture": checks.majority_capture_table(),
        "linguistics": {k: v for k, v in prof.items() if k != "per_article"},
        "amendments": amendment_history(arts),
        "layers": _layers(),
        "machines": [{"name": m.name, "title": m.title, "start": m.start,
                      "transitions": [{"from": s, "event": e, "to": t.to, "pid": t.pid, "deadline": t.deadline_days}
                                      for (s, e), t in m.transitions.items()],
                      "undefined": [{"state": s, "event": e, "note": m.note.get((s, e), "")}
                                    for s, evs in m.possible.items() for e in evs if (s, e) not in m.transitions]}
                     for m in MACHINES],
    }


def _layers() -> list[dict]:
    from . import statute_machines as sm
    return sm.summary() if sm.available() else []


def markdown(data: dict) -> str:
    s = data["summary"]
    L = ["# Монгол Улсын Үндсэн хуулийн «код ревью»", "",
         f"Эх: {data['source']} (татсан {data['fetched']}). Шинжилгээ бүхэлдээ монгол эх дээр хийгдсэн.", "",
         f"**{s['articles']} зүйл, {s['findings']} олдвор** — " +
         ", ".join(f"{SEV_MN[k]} {v}" for k, v in sorted(s['by_severity'].items(), key=lambda kv: checks.SEV_ORDER[kv[0]])) +
         ". Стресс тест: " + ", ".join(f"{VERDICT_MN[k]} {v}" for k, v in s["stress"].items()) + ".", "",
         "## Олдворууд", ""]
    for i, f in enumerate(data["findings"], 1):
        L.append(f"### {i}. [{SEV_MN[f['severity']]} · {CAT_MN[f['category']]}] {f['title']}")
        L.append(f"Зүйл: {', '.join(f['articles'])} · Дүрэм: `{f['rule']}`")
        if f["detail"]:
            L.append(f"\n{f['detail']}")
        if f["evidence"]:
            L.append(f"\nНотолгоо: {f['evidence']}")
        if f["fix"]:
            L.append(f"\nЗасвар: {f['fix']}")
        L.append("")
    if data["layers"]:
        L += ["## Процедурын давхарга: Үндсэн хууль → Үндсэн хууль + хууль", "",
              "Энгийн хууль ямар шилжилт, хугацаа нэмсэн, юу нээлттэй үлдсэн. «Хугацаатай ч үр дагаваргүй» — хугацаа "
              "хэтэрвэл юу болохыг хууль ч заагаагүй.", "",
              "| Процедур | Хуулийн шилжилт/хугацаа | Тодорхойгүй шилжилт | Гацах цэг | Хугацаатай ч үр дагаваргүй |", "|---|---|---|---|---|"]
        for l in data["layers"]:
            L.append(f"| {l['title']} | {len(l['statute_edges'])} | {l['undefined']['constitution']} → {l['undefined']['with_statute']} "
                     f"| {l['stalls']['constitution']} → {l['stalls']['with_statute']} | {', '.join(l['deadline_without_consequence']) or '—'} |")
        L.append("")
        for l in data["layers"]:
            if l["statute_edges"] or l["state_notes"]:
                L.append(f"**{l['title']}:** " + "; ".join(f"{e['from']} —{e['event']}→ {e['to']} [{e['cite']}]" for e in l["statute_edges"])
                         + "".join(f"; {st}: {n}" for st, n in l["state_notes"].items()) + "\n")
    L += ["## Стресс тест", ""]
    for r in data["stress"]:
        L.append(f"**{r['n']}. {r['title']} — {VERDICT_MN[r['verdict']]}.** {r['break_point']}\n")
        if r.get("verdict_laws"):
            L.append(f"*Хуультай хамт — {VERDICT_MN[r['verdict_laws']]}.* {r['note_laws']}\n")
    L += ["## Нэг нам дангаараа юу хийж чадах вэ", "", "| Эрх мэдэл | Зүйл | Шаардлагатай суудал | Хувь |", "|---|---|---|---|"]
    for c in data["capture"]:
        L.append(f"| {c['power']} | {c['pid']} | {c['seats_needed']}/{data['total_seats']} | {c['share']:.0%} |")
    li = data["linguistics"]
    L += ["", "## Хэл найруулга", "",
          f"{li['sentences']} өгүүлбэр. Модаль байдал: {li['modality']}. «Хуулиар тогтооно»-ийн төрлийн шилжүүлэлт: {li['delegation_count']}."]
    return "\n".join(L) + "\n"


def main(out_dir: str = "out") -> None:
    data = build()
    out = Path(out_dir)
    out.mkdir(exist_ok=True)
    (out / "report.json").write_text(json.dumps(data, ensure_ascii=False, indent=1), encoding="utf-8")
    (out / "REPORT.md").write_text(markdown(data), encoding="utf-8")
    print(f"{data['summary']}")


if __name__ == "__main__":
    main()
