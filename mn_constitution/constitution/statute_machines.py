"""Statute layer for the procedure state machines.

procedures.py stays constitution-only. This module adds what ordinary law defines on top:
  ADD       new transitions (an outcome the statute defines and the Constitution does not)
  DEADLINE  a statute deadline on an existing constitutional transition
  NOTES     statute rules that hold while a machine sits in a state
Every entry quotes the statute verbatim (verify() runs q_law on all of them).

layered(m) = constitution + statute. Gaps that remain in the layered machine are gaps
neither the Constitution nor the statute closes.
"""
from __future__ import annotations

import copy

from .laws import load, q_law
from .procedures import MACHINES, Machine, T
from .statutes import EMERGENCY as EMERG_LAW, HURAL, RULES, TSETS_PROC


LAW_NAME = {RULES: "Дэгийн тухай", HURAL: "УИХ-ын тухай", TSETS_PROC: "Цэцийн ажиллагааны тухай", EMERG_LAW: "Онц байдлын тухай"}


def S(to: str, law: str, pid: str, phrase: str, actor: str = "", days=None, unit="days", default=None) -> T:
    return T(to, pid, actor, days, default, level="statute", law=law, law_pid=pid, phrase=phrase, unit=unit)


def cite(t: T) -> str:
    """Human label: '33.1.1; ⚖ Дэгийн тухай 46.5 ≤5 ажлын өдөр' or '⚖ Цэцийн ажиллагааны тухай 21.5 ≤14х'."""
    dl = "" if t.deadline_days is None else f" ≤{t.deadline_days:g}{' ажлын өдөр' if t.unit == 'working_days' else 'х'}"
    law = f"⚖ {LAW_NAME.get(t.law, t.law)} {t.law_pid}" if t.law else ""
    if t.level == "statute":
        return law + dl
    return f"{t.pid}; {law}{dl}" if law else t.pid + dl


# (state, event) -> T   — new transitions with an outcome defined by statute
ADD: dict[str, dict[tuple[str, str], T]] = {
    "veto": {
        ("VETOED", "override_fails"): S("IN_FORCE", RULES, "46.6",
            "гуравны хоёр буюу 66.6 хувь нь хоригийг хүлээн аваагүй бол тухайн хууль, тогтоол хүчин төгөлдөр хэвээр үлдэнэ", "УИХ",
            14, "working_days"),
    },
    "tsets": {
        ("PETITION", "tsets_refuses"): S("REFUSED", TSETS_PROC, "21.5",
            "маргаан хянан шийдвэрлэх ажиллагаа үүсгэхээс татгалзаж тогтоол гаргана", "Цэцийн гишүүн", 14),
        ("HEARING", "tie_vote"): S("HEARING", TSETS_PROC, "29.6",
            "уг маргааныг 30 хоногийн дотор дахин хянан хэлэлцэж шийдвэрлэхээр хойшлуулж", "Цэц", 30),
        ("RE_REVIEW", "no_two_thirds"): S("RESOLVED", TSETS_PROC, "3.6",
            "Хэрэв гишүүдийн гуравны хоёр хувийн санал авч чадаагүй бол уг хууль, тогтоол, зарлиг, бусад шийдвэр, Монгол Улсын олон улсын гэрээний заалт хүчинтэй хэвээр үлдэнэ", "Цэц"),
    },
    "emergency": {
        ("EMERGENCY", "end_date_reached"): S("NORMAL", EMERG_LAW, "5.7",
            "онц байдал үргэлжлэх хугацаа /эхлэх, дуусах он, сар, өдөр, цаг/"),
        ("EMERGENCY", "nsc_extension"): S("EMERGENCY", EMERG_LAW, "6.2",
            "Үндэсний аюулгүй байдлын зөвлөлийн саналыг үндэслэн Улсын Их Хурал онц байдлын үргэлжлэх хугацааг сунгаж болно", "УИХ"),
        ("EMERGENCY", "nsc_early_end"): S("NORMAL", EMERG_LAW, "6.3",
            "Үндэсний аюулгүй байдлын зөвлөлийн саналыг үндэслэн Улсын Их Хурал онц байдлыг хугацаанаас нь өмнө цуцална", "УИХ"),
        ("HURAL_HOLDS_OVER", "end_date_reached"): S("NORMAL", EMERG_LAW, "5.7",
            "онц байдал үргэлжлэх хугацаа /эхлэх, дуусах он, сар, өдөр, цаг/"),
        ("HURAL_HOLDS_OVER", "nsc_extension"): S("HURAL_HOLDS_OVER", EMERG_LAW, "6.2",
            "Үндэсний аюулгүй байдлын зөвлөлийн саналыг үндэслэн Улсын Их Хурал онц байдлын үргэлжлэх хугацааг сунгаж болно", "УИХ"),
    },
    "pm_dismissal": {
        ("DISSOLVED", "snap_election_called"): S("SNAP_ELECTION", RULES, "94.1",
            "10 хоногийн дотор ээлжит бус сонгуулийг товлон зарлана", "УИХ", 10),
    },
    "formation": {
        ("DISSOLVED", "snap_election_called"): S("SNAP_ELECTION", RULES, "94.1",
            "10 хоногийн дотор ээлжит бус сонгуулийг товлон зарлана", "УИХ", 10),
    },
}

# (state, event) -> statute deadline on an existing constitutional transition
DEADLINE: dict[str, dict[tuple[str, str], T]] = {
    "veto": {
        ("LAW_PASSED", "president_vetoes"): S("", RULES, "46.5", "ажлын 5 өдөрт багтаан", "Ерөнхийлөгч", 5, "working_days"),
        ("VETOED", "override_2_3_present"): S("", RULES, "90.1", "хоригийг чуулганы үеэр ажлын 14 өдрийн дотор", "УИХ", 14, "working_days"),
        ("VETOED", "veto_accepted"): S("", RULES, "90.1", "хоригийг чуулганы үеэр ажлын 14 өдрийн дотор", "УИХ", 14, "working_days"),
    },
    "tsets": {
        ("PETITION", "tsets_accepts_case"): S("", TSETS_PROC, "21.2", "анхны шалгалтыг 14 хоногийн дотор хийж", "Цэцийн гишүүн", 14),
        ("CONCLUSION", "hural_accepts"): S("", TSETS_PROC, "35.2", "Цэцийн дүгнэлтийг Улсын Их Хурал хүлээн авснаас хойш 15 хоногийн дотор", "УИХ", 15),
        ("CONCLUSION", "hural_rejects"): S("", TSETS_PROC, "35.2", "Цэцийн дүгнэлтийг Улсын Их Хурал хүлээн авснаас хойш 15 хоногийн дотор", "УИХ", 15),
    },
    "formation": {
        ("SUBMITTED", "hural_appoints"): S("", RULES, "24.1", "ажлын 3 өдрийн дотор хуралдаанаараа хэлэлцэж санал, дүгнэлт гаргана", "Байнгын хороо", 3, "working_days"),
    },
}

# state -> (law, pid, phrase, Mongolian gloss)   — rules that hold while in that state
NOTES: dict[str, dict[str, tuple[str, str, str, str]]] = {
    "veto": {"VETOED": (HURAL, "5.4", "уг хууль тогтоомж бүхэлдээ буюу түүний зарим хэсгийн үйлчлэл түр зогсоно",
                        "хориг хэлэлцэгдэх хүртэл хууль түр зогсоно")},
    "tsets": {"CONCLUSION": (TSETS_PROC, "32.4", "заалтын үйлчилгээ нь Цэцийн эцсийн шийдвэр гарах хүртэл түдгэлзэнэ",
                             "эцсийн шийдвэр хүртэл заалт түдгэлзэнэ"),
              "RE_REVIEW": (TSETS_PROC, "32.4", "заалтын үйлчилгээ нь Цэцийн эцсийн шийдвэр гарах хүртэл түдгэлзэнэ",
                            "эцсийн шийдвэр хүртэл заалт түдгэлзэнэ")},
    "pm_dismissal": {"DEBATE": (HURAL, "21.5", "хуралдаан эхлэхэд болон санал хураахад заавал бүрдүүлсэн байна",
                                "ирц нээлт, санал хураалтад заавал")},
    "emergency": {"EMERGENCY": (EMERG_LAW, "19", "Үндсэн хуульд нэмэлт, өөрчлөлт оруулж болохгүй",
                                "онц байдлын үед Үндсэн хуулийг өөрчлөхгүй")},
}


def _all_cites():
    for m in ADD.values():
        yield from ((t.law, t.law_pid, t.phrase) for t in m.values())
    for m in DEADLINE.values():
        yield from ((t.law, t.law_pid, t.phrase) for t in m.values())
    for m in NOTES.values():
        yield from ((l, p, ph) for l, p, ph, _ in m.values())


def available() -> bool:
    return all(load(l) for l, _, _ in _all_cites())


def verify() -> int:
    """q_law every statute citation; raises on the first non-verbatim phrase."""
    n = 0
    for l, p, ph in _all_cites():
        q_law(l, p, ph); n += 1
    return n


def layered(m: Machine) -> Machine:
    """Constitution + statute. Constitutional transitions win; statute deadlines fill missing ones."""
    lm = copy.deepcopy(m)
    lm.title = m.title + " + хууль"
    for key, t in ADD.get(m.name, {}).items():
        lm.transitions.setdefault(key, t)
        evs = lm.possible.setdefault(key[0], [])
        if key[1] not in evs:
            evs.append(key[1])
    for key, d in DEADLINE.get(m.name, {}).items():
        c = lm.transitions.get(key)
        if c and c.deadline_days is None:
            lm.transitions[key] = T(c.to, c.pid, c.actor, d.deadline_days, c.default_on_timeout,
                                    level="constitution", law=d.law, law_pid=d.law_pid, phrase=d.phrase, unit=d.unit)
    return lm


def state_notes(m: Machine) -> dict[str, str]:
    return {s: f"{gloss} [⚖ {LAW_NAME.get(law, law)} {pid}]" for s, (law, pid, _, gloss) in NOTES.get(m.name, {}).items()}


def layered_machines() -> list[Machine]:
    return [layered(m) for m in MACHINES]


def unenforced_deadlines(m: Machine):
    """Transitions with a deadline but no outcome if the deadline passes (a softer stall)."""
    for key, t in m.transitions.items():
        if t.deadline_days is not None and t.default_on_timeout is None and key in m.must_act | set(DEADLINE.get(m.name, {})):
            yield key, t


def summary() -> list[dict]:
    """Per machine: what the statute layer adds and what stays open."""
    from .procedures import stall_points, undefined_transitions
    out = []
    for m in MACHINES:
        lm = layered(m)
        out.append({
            "name": m.name, "title": m.title,
            "statute_edges": [{"from": s, "event": e, "to": t.to, "level": t.level, "cite": cite(t),
                               "law": t.law, "law_pid": t.law_pid, "deadline": t.deadline_days, "unit": t.unit}
                              for (s, e), t in lm.transitions.items() if t.law],
            "undefined": {"constitution": len(list(undefined_transitions(m))), "with_statute": len(list(undefined_transitions(lm)))},
            "stalls": {"constitution": len(list(stall_points(m))), "with_statute": len(list(stall_points(lm)))},
            "deadline_without_consequence": [f"{s}/{e}" for (s, e), _ in unenforced_deadlines(lm)],
            "state_notes": state_notes(m),
        })
    return out
