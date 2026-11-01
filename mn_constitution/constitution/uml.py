"""Generate UML (Mermaid) from the live model: docs/UML.md and out/uml.html.

State diagrams are built from procedures.MACHINES, so they cannot drift from the code.
Dashed red arrows to UNDEFINED = undefined_transitions(); bold = stall_points().
"""
from __future__ import annotations

import html
from pathlib import Path

from .procedures import MACHINES, undefined_transitions, stall_points

ROOT = Path(__file__).resolve().parent.parent


def _id(s: str) -> str:
    return s.replace(".", "_")


def _safe(x: str) -> str:
    return x.replace(":", " ").replace(";", ",").replace("[", "‹").replace("]", "›")


def state_diagram(m, notes: dict | None = None) -> str:
    from .statute_machines import cite
    L = ["stateDiagram-v2", "    direction LR", f"    [*] --> {m.start}",
         "    state \"НӨХЦӨЛ ТОДОРХОЙГҮЙ\" as UNDEFINED"]
    const_states = {m.start} | {s for (s, _), t in m.transitions.items() if t.level == "constitution"} \
        | {t.to for t in m.transitions.values() if t.level == "constitution"}
    for (s, e), t in m.transitions.items():
        L.append(f"    {s} --> {t.to}: {'⚖ ' if t.level == 'statute' else ''}{e} ‹{_safe(cite(t))}›")
        if t.default_on_timeout:
            L.append(f"    {s} --> {t.default_on_timeout}: timeout [{t.pid}]")
    for s, e in undefined_transitions(m):
        L.append(f"    {s} --> UNDEFINED: ✗ {e}")
    for (s, e), _t in stall_points(m):
        L.append(f"    note right of {s}: STALL - {e} - хугацаа, анхдагч үр дагаваргүй")
    for s, n in (notes or {}).items():
        L.append(f"    note left of {s}: ⚖ {_safe(n)}")
    L.append("    classDef bad fill:#fdd,stroke:#c00,color:#900")
    L.append("    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123")
    L.append("    class UNDEFINED bad")
    extra = sorted({t.to for t in m.transitions.values()} - const_states - {"UNDEFINED"})
    if extra:
        L.append(f"    class {','.join(extra)} statute")
    return "\n".join(L)


CLASS = """classDiagram
    class Article { +str number +int chapter +str title }
    class Provision { +str pid +Kind kind +str actor +bool delegates +str limits +float deadline_days +tuple terms }
    class Threshold { +Fraction fraction +Base base +seats_needed(total) int }
    class Finding { +str rule +str severity +str category +tuple articles +str evidence +str fix }
    class Machine { +str name +str start +dict transitions +dict possible +set must_act }
    class T { +str to +str pid +str actor +float deadline_days +str default_on_timeout }
    class Kind { <<enum>> right duty prohibition power procedure declaration delegation }
    class Base { <<enum>> total present voters }
    Article "1" *-- "many" Provision
    Provision --> Kind
    Provision "0..1" --> Threshold
    Threshold --> Base
    Machine "1" *-- "many" T
    Finding ..> Provision : cites via q()
    Finding ..> Machine : derived from"""

PIPELINE = """flowchart LR
    TXT[(undsen_khuuli_mn.txt<br/>legalinfo lawId=367)] --> P[text_mn.py<br/>parse / modality / delegations]
    P --> Q{{q&#40;pid, phrase&#41;<br/>verbatim guard}}
    A[articles.py<br/>71 articles, TOTAL_SEATS=126] --> C
    M[model.py] -.types.-> A
    PR[procedures.py<br/>8 state machines] --> C[checks.py<br/>rules]
    PR --> S[stress.py<br/>7 scenarios]
    Q --> C
    C --> R[report.py]
    S --> R
    R --> J[out/report.json]
    R --> MD[out/REPORT.md]
    J --> E[explorer/build.py] --> H[out/explorer.html]
    PR --> U[uml.py] --> UM[docs/UML.md + out/uml.html]"""

SEQ = """sequenceDiagram
    autonumber
    actor H as УИХ
    actor P as Ерөнхийлөгч
    participant C as Цэц
    participant M as PM_DISMISSAL machine
    H->>M: vote_majority_total [43.1] 2025-10-17
    M-->>H: DISMISSED
    P->>M: president_veto [33.1.1] 2025-10-20
    M--xP: ✗ UNDEFINED_TRANSITION (DISMISSED, president_veto)
    Note over M,P: 33.1.1 «бусад шийдвэр» хамрах эсэх тодорхойгүй
    H->>C: tsets_petition [66.2.1]
    C->>M: tsets_finds_void [66.4] 2025-10-22
    M-->>H: IN_OFFICE"""


def build() -> str:
    parts = ["# UML баримт (автоматаар үүсгэсэн: `python3 -m constitution.uml`)\n",
             "## 1. Бүрэлдэхүүн / өгөгдлийн урсгал\n```mermaid\n" + PIPELINE + "\n```\n",
             "## 2. Ангийн диаграм (model.py, procedures.py)\n```mermaid\n" + CLASS + "\n```\n",
             "## 3. Тохиолдол: 2025 оны 10-р сар (дараалал)\n```mermaid\n" + SEQ + "\n```\n"]
    from . import statute_machines as sm
    with_laws = sm.available()
    if with_laws:
        parts.append("Төлөвт машин бүрийг хоёр давхаргаар: (а) зөвхөн Үндсэн хууль, (б) Үндсэн хууль + хууль. "
                     "⚖ — зөвхөн энгийн хуулиар тодорхойлогдсон шилжилт/хугацаа; цэнхэр төлөв — зөвхөн хуульд байдаг; "
                     "улаан — аль ч давхаргад заагаагүй.\n")
    for i, m in enumerate(MACHINES, 4):
        parts.append(f"## {i}. Төлөвт машин: {m.title}\n```mermaid\n{state_diagram(m)}\n```\n")
        if with_laws and (sm.ADD.get(m.name) or sm.DEADLINE.get(m.name) or sm.NOTES.get(m.name)):
            parts.append(f"## {i}б. {m.title} + хууль\n```mermaid\n{state_diagram(sm.layered(m), sm.state_notes(m))}\n```\n")
    return "\n".join(parts)


def main():
    md = build()
    (ROOT / "docs").mkdir(exist_ok=True)
    (ROOT / "docs" / "UML.md").write_text(md, encoding="utf-8")
    blocks, title = [], []
    for chunk in md.split("```mermaid\n")[1:]:
        blocks.append(chunk.split("\n```")[0])
    heads = [l[3:] for l in md.splitlines() if l.startswith("## ")]
    body = "".join(f"<h2>{html.escape(h)}</h2><pre class='mermaid'>{html.escape(b)}</pre>" for h, b in zip(heads, blocks))
    page = ("<!doctype html><meta charset=utf-8><title>mn_constitution UML</title>"
            "<style>body{font-family:sans-serif;max-width:1200px;margin:2em auto}pre.mermaid{background:#fff}</style>"
            f"{body}<script type=module>import m from 'https://cdn.jsdelivr.net/npm/mermaid@11/dist/mermaid.esm.min.mjs';"
            "m.initialize({startOnLoad:true,securityLevel:'loose'});</script>")
    (ROOT / "out" / "uml.html").write_text(page, encoding="utf-8")
    print("wrote docs/UML.md, out/uml.html")


if __name__ == "__main__":
    main()
