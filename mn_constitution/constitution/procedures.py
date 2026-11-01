"""Constitutional procedures as finite state machines.

Each machine lists, per state, the events that can realistically occur.
An event with no transition is an UNDEFINED TRANSITION (the text is silent).
A transition that requires an actor to act but has no deadline and no default
outcome is a STALL POINT (the actor can block forever by doing nothing).
"""
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Optional


@dataclass(frozen=True)
class T:
    to: str
    pid: str                         # article that defines this transition
    actor: str = ""
    deadline_days: Optional[float] = None
    default_on_timeout: Optional[str] = None   # state reached if actor does nothing
    level: str = "constitution"      # "constitution" | "statute" (see statute_machines.py)
    law: str = ""                    # legalinfo lawId of the statute that defines this edge or its deadline
    law_pid: str = ""                # article/section in that statute
    phrase: str = ""                 # verbatim statute wording (checked by q_law)
    unit: str = "days"               # "days" | "working_days"


@dataclass
class Machine:
    name: str
    title: str
    start: str
    transitions: dict[tuple[str, str], T]
    possible: dict[str, list[str]]          # state -> events that can occur
    must_act: set[tuple[str, str]] = field(default_factory=set)  # (state, event) an actor is obliged to trigger
    note: dict[tuple[str, str], str] = field(default_factory=dict)  # why an undefined event matters
    case: dict[tuple[str, str], str] = field(default_factory=dict)  # real-world occurrence


PM_DISMISSAL = Machine(
    "pm_dismissal", "Ерөнхий сайдыг огцруулах (43, 33.1.1, 22.3, 66)", "IN_OFFICE",
    transitions={
        ("IN_OFFICE", "motion_by_quarter"): T("MOTION_FILED", "43.1", "УИХ-ын 1/4"),
        ("MOTION_FILED", "debate_after_3_days"): T("DEBATE", "43.1", "УИХ", 3),
        ("DEBATE", "vote_majority_total"): T("DISMISSED", "43.1", "УИХ", 10),
        ("DEBATE", "vote_fails"): T("IN_OFFICE", "43.1", "УИХ", 10),
        ("DISMISSED", "new_pm_appointed"): T("NEW_PM", "43.1", "УИХ", 30, default_on_timeout="DISSOLUTION_DUE"),
        ("DISMISSED", "tsets_petition"): T("TSETS_REVIEW", "66.2.1", "Цэц", None),
        ("DISSOLUTION_DUE", "president_dissolves"): T("DISSOLVED", "22.3", "Ерөнхийлөгч", None),
        ("TSETS_REVIEW", "tsets_finds_void"): T("IN_OFFICE", "66.4", "Цэц", None),
        ("TSETS_REVIEW", "tsets_upholds"): T("DISMISSED", "66.4", "Цэц", None),
    },
    possible={
        "IN_OFFICE": ["motion_by_quarter"],
        "MOTION_FILED": ["debate_after_3_days"],
        "DEBATE": ["vote_majority_total", "vote_fails", "no_vote_within_10_days", "quorum_lost"],
        "DISMISSED": ["new_pm_appointed", "president_veto", "tsets_petition", "no_pm_in_30_days"],
        "DISSOLUTION_DUE": ["president_dissolves", "president_does_nothing"],
        "TSETS_REVIEW": ["tsets_finds_void", "tsets_upholds", "tsets_silent"],
    },
    must_act={("DISSOLUTION_DUE", "president_dissolves"), ("TSETS_REVIEW", "tsets_finds_void")},
    note={
        ("DISMISSED", "president_veto"): "33.1.1 «бусад шийдвэр» огцруулах тогтоолыг хамрах эсэх тодорхойгүй; хамарвал 43.1-ийн нийт олонхийн шийдвэрийг оролцсон гишүүний 2/3-оор л сэргээх боломжтой",
        ("DEBATE", "no_vote_within_10_days"): "10 хоногийн хугацаа хэтэрвэл санал хүчингүй юу, хүчинтэй юу — заагаагүй",
        ("DEBATE", "quorum_lost"): "27.6 ирцийн шаардлагыг хэлэлцүүлгийн аль шатанд шалгах нь тодорхойгүй",
        ("DISSOLUTION_DUE", "president_does_nothing"): "22.3 Ерөнхийлөгч «тараах шийдвэр гаргана» гэсэн ч хугацаа, татгалзсан үеийн үр дагавар алга",
        ("TSETS_REVIEW", "tsets_silent"): "Цэцийн хянан шийдвэрлэх хугацаа Үндсэн хуульд алга",
        ("DISMISSED", "no_pm_in_30_days"): "Тодорхойлогдсон: 22.3-аар тараах үүрэг үүснэ (энэ нь бусад нүхийг хаадаггүй)",
    },
    case={
        ("DISMISSED", "president_veto"): "2025.10.17 огцруулсан тогтоолд Ерөнхийлөгч 10.20-нд хориг тавьсан; Цэц 10.22-нд тогтоолыг Үндсэн хуульд нийцээгүй гэж шийдсэн",
        ("DEBATE", "quorum_lost"): "2025.10.20 Ерөнхийлөгчийн хоригийн үндэслэл: хэлэлцэж эхлэхэд ирц бүрдээгүй",
    },
)
# the 30-day branch IS defined (default_on_timeout); remove it from the "undefined" probe
PM_DISMISSAL.transitions[("DISMISSED", "no_pm_in_30_days")] = T("DISSOLUTION_DUE", "22.3", "", 30)

CONFIDENCE = Machine(
    "confidence", "Итгэл хүлээлгэх (44)", "IN_OFFICE",
    transitions={
        ("IN_OFFICE", "pm_requests_confidence"): T("DEBATE", "44.1", "Ерөнхий сайд"),
        ("DEBATE", "passed"): T("IN_OFFICE", "44.2", "УИХ", 13),
        ("DEBATE", "not_passed"): T("DEEMED_RESIGNED", "44.2", "УИХ", 13),
        ("DEEMED_RESIGNED", "new_pm_appointed"): T("NEW_PM", "44.2", "УИХ", 30, default_on_timeout="DISSOLUTION_DUE"),
        ("DEEMED_RESIGNED", "no_pm_in_30_days"): T("DISSOLUTION_DUE", "22.3", "", 30),
    },
    possible={
        "IN_OFFICE": ["pm_requests_confidence"],
        "DEBATE": ["passed", "not_passed", "no_vote_within_10_days"],
        "DEEMED_RESIGNED": ["new_pm_appointed", "no_pm_in_30_days"],
    },
    note={("DEBATE", "no_vote_within_10_days"): "«батлаагүй бол огцорсонд тооцно» — санал хураалт огт явуулаагүйг «батлаагүй» гэж үзэх үү? Ерөнхий сайдын хувь заяа УИХ-ын идэвхгүй байдлаас хамаарна"},
)

FORMATION = Machine(
    "formation", "Засгийн газар бүрдүүлэх (39.2, 22.3)", "AFTER_ELECTION",
    transitions={
        ("AFTER_ELECTION", "party_nominates"): T("NOMINATED", "39.2", "нам/эвсэл"),
        ("NOMINATED", "president_submits_5d"): T("SUBMITTED", "39.2", "Ерөнхийлөгч", 5),
        ("SUBMITTED", "hural_appoints"): T("PM_APPOINTED", "25.1.6", "УИХ", 45, default_on_timeout="DISSOLUTION_DUE"),
        ("SUBMITTED", "no_appointment_45d"): T("DISSOLUTION_DUE", "22.3", "", 45),
        ("DISSOLUTION_DUE", "president_dissolves"): T("DISSOLVED", "22.3", "Ерөнхийлөгч", None),
    },
    possible={
        "AFTER_ELECTION": ["party_nominates", "no_majority_coalition_forms"],
        "NOMINATED": ["president_submits_5d", "president_misses_5d"],
        "SUBMITTED": ["hural_appoints", "no_appointment_45d"],
        "DISSOLUTION_DUE": ["president_dissolves", "president_does_nothing"],
    },
    must_act={("DISSOLUTION_DUE", "president_dissolves")},
    note={
        ("AFTER_ELECTION", "no_majority_coalition_forms"): "45 хоногийн цаг Ерөнхийлөгч санал «анх оруулснаас» эхэлнэ; нэр дэвшигч огт гараагүй бол цаг эхлэхгүй — хязгааргүй гацаа",
        ("NOMINATED", "president_misses_5d"): "5 хоногийн хугацаа хэтэрвэл үр дагавар заагаагүй",
        ("DISSOLUTION_DUE", "president_does_nothing"): "22.3 тараах шийдвэрийн хугацаагүй",
    },
)

VETO = Machine(
    "veto", "Ерөнхийлөгчийн хориг (33.1.1)", "LAW_PASSED",
    transitions={
        ("LAW_PASSED", "president_vetoes"): T("VETOED", "33.1.1", "Ерөнхийлөгч", None),
        ("LAW_PASSED", "president_accepts"): T("IN_FORCE", "26.3", "Ерөнхийлөгч", None),
        ("VETOED", "override_2_3_present"): T("IN_FORCE", "33.1.1", "УИХ", None),
        ("VETOED", "veto_accepted"): T("DEAD", "33.1.1", "УИХ", None),
    },
    possible={
        "LAW_PASSED": ["president_vetoes", "president_accepts", "president_silent"],
        "VETOED": ["override_2_3_present", "veto_accepted", "hural_never_considers"],
    },
    note={
        ("LAW_PASSED", "president_silent"): "Хориг тавих хугацаа Үндсэн хуульд алга (хуулиар тогтоосон байж болно)",
        ("VETOED", "hural_never_considers"): "Хоригийг хэлэлцэх хугацаагүй — хууль хязгааргүй хугацаагаар «хориотой» төлөвт үлдэнэ",
    },
)

EMERGENCY = Machine(
    "emergency", "Онц/дайны байдал (25.1.18, 33.1.12, 19.2)", "NORMAL",
    transitions={
        ("NORMAL", "hural_declares"): T("EMERGENCY", "25.1.18", "УИХ"),
        ("NORMAL", "president_declares_in_recess"): T("PRES_DECREE", "33.1.12", "Ерөнхийлөгч"),
        ("PRES_DECREE", "hural_approves_7d"): T("EMERGENCY", "33.1.12", "УИХ", 7, default_on_timeout="NORMAL"),
        ("PRES_DECREE", "hural_silent_7d"): T("NORMAL", "33.1.12", "", 7),
        ("PRES_DECREE", "hural_rejects"): T("NORMAL", "33.1.12", "УИХ", 7),
        ("EMERGENCY", "hural_lifts"): T("NORMAL", "25.1.18", "УИХ"),
        ("EMERGENCY", "regular_election_due"): T("HURAL_HOLDS_OVER", "22.1", "УИХ"),
        ("HURAL_HOLDS_OVER", "hural_lifts"): T("NORMAL", "22.1", "УИХ"),
    },
    possible={
        "NORMAL": ["hural_declares", "president_declares_in_recess"],
        "PRES_DECREE": ["hural_approves_7d", "hural_silent_7d", "hural_rejects"],
        "EMERGENCY": ["hural_lifts", "regular_election_due", "max_duration_reached"],
        "HURAL_HOLDS_OVER": ["hural_lifts", "max_duration_reached"],
    },
    note={
        ("EMERGENCY", "max_duration_reached"): "Онц байдлын дээд хугацаа, сунгах журам Үндсэн хуульд алга",
        ("HURAL_HOLDS_OVER", "max_duration_reached"): "22.1: УИХ онц байдлыг ӨӨРӨӨ зарлаж (25.1.18), ӨӨРӨӨ цуцлах хүртэл бүрэн эрхээ сунгана — хугацааны хязгаар, гуравдагч хяналт алга",
    },
)

TSETS = Machine(
    "tsets", "Цэцийн хяналт (66)", "PETITION",
    transitions={
        ("PETITION", "tsets_accepts_case"): T("HEARING", "66.1", "Цэц", None),
        ("HEARING", "conclusion_issued"): T("CONCLUSION", "66.2", "Цэц", None),
        ("CONCLUSION", "hural_accepts"): T("RESOLVED", "66.4", "УИХ", None),
        ("CONCLUSION", "hural_rejects"): T("RE_REVIEW", "66.3", "УИХ", None),
        ("RE_REVIEW", "final_decision"): T("RESOLVED", "66.3", "Цэц", None),
    },
    possible={
        "PETITION": ["tsets_accepts_case", "tsets_ignores_petition"],
        "HEARING": ["conclusion_issued", "tsets_silent"],
        "CONCLUSION": ["hural_accepts", "hural_rejects", "hural_never_considers"],
        "RE_REVIEW": ["final_decision", "tsets_silent"],
    },
    must_act={("CONCLUSION", "hural_accepts"), ("RE_REVIEW", "final_decision")},
    note={
        ("PETITION", "tsets_ignores_petition"): "Иргэний мэдээллийг хүлээн авах эсэх шийдвэрийн хугацаа, үндэслэлийн шаардлага алга",
        ("HEARING", "tsets_silent"): "Дүгнэлт гаргах хугацаа алга",
        ("CONCLUSION", "hural_never_considers"): "УИХ дүгнэлтийг хэлэлцэх хугацаагүй; энэ хугацаанд маргаантай хууль үйлчилсээр байна (66.4 зөвхөн эцсийн шийдвэрт)",
        ("RE_REVIEW", "tsets_silent"): "Эцсийн шийдвэрийн хугацаа алга",
    },
)

PRES_ELECTION = Machine(
    "pres_election", "Ерөнхийлөгчийн сонгууль (31, 32.1, 30.2)", "ROUND_1",
    transitions={
        ("ROUND_1", "majority"): T("ELECTED", "31.4", "сонгогч"),
        ("ROUND_1", "no_majority"): T("ROUND_2", "31.5", "сонгогч"),
        ("ROUND_2", "majority"): T("ELECTED", "31.5", "сонгогч"),
        ("ROUND_2", "no_majority"): T("ROUND_1", "31.6", "сонгогч"),   # rerun, unbounded
        ("ELECTED", "hural_recognizes"): T("OATH", "31.4", "УИХ", None),
        ("OATH", "oath_30d"): T("NEW_PRESIDENT", "32.2", "Ерөнхийлөгч", 30),
    },
    possible={
        "ROUND_1": ["majority", "no_majority"],
        "ROUND_2": ["majority", "no_majority"],
        "ELECTED": ["hural_recognizes", "hural_delays_recognition"],
        "OATH": ["oath_30d"],
    },
    must_act={("ELECTED", "hural_recognizes")},
    note={("ELECTED", "hural_delays_recognition"): "УИХ ялагчийн бүрэн эрхийг хүлээн зөвшөөрөх хуулийг гаргах хугацаагүй; 32.1-ээр одоогийн Ерөнхийлөгч хугацаагүй үргэлжилнэ"},
)

AMENDMENT = Machine(
    "amendment", "Үндсэн хуульд нэмэлт өөрчлөлт (68, 69)", "DRAFT",
    transitions={
        ("DRAFT", "vote_3_4_total"): T("ADOPTED", "69.1", "УИХ"),
        ("DRAFT", "fails_twice"): T("FROZEN", "69.2", "УИХ"),
        ("DRAFT", "referendum_2_3"): T("REFERENDUM", "68.2", "УИХ"),
        ("REFERENDUM", "valid_majority"): T("ADOPTED", "25.1.16", "сонгогч"),
        ("FROZEN", "new_composition"): T("DRAFT", "69.2", ""),
    },
    possible={
        "DRAFT": ["vote_3_4_total", "fails_twice", "referendum_2_3", "within_6m_of_snap_election"],
        "REFERENDUM": ["valid_majority"],
        "FROZEN": ["new_composition"],
    },
    note={("DRAFT", "within_6m_of_snap_election"): "69.3 зөвхөн ЭЭЛЖИТ сонгуульд хамаарна; 22.2-оор өөрөө тарах шийдвэр гаргасан УИХ ээлжит бус сонгуулийн өмнө Үндсэн хуулийг өөрчилж болно"},
)

MACHINES = [PM_DISMISSAL, CONFIDENCE, FORMATION, VETO, EMERGENCY, TSETS, PRES_ELECTION, AMENDMENT]


def undefined_transitions(m: Machine):
    for state, events in m.possible.items():
        for e in events:
            if (state, e) not in m.transitions:
                yield state, e


def stall_points(m: Machine):
    """Obligatory actions with no deadline and no default outcome."""
    for key in sorted(m.must_act):
        t = m.transitions.get(key)
        if t and t.deadline_days is None and t.default_on_timeout is None:
            yield key, t


def run(m: Machine, events: list[str]) -> tuple[str, list[str]]:
    """Replay a sequence of events. Returns (final_state, trace). Stops at the first undefined event."""
    state, trace = m.start, [m.start]
    for e in events:
        t = m.transitions.get((state, e))
        if t is None:
            trace.append(f"UNDEFINED({e})")
            return f"UNDEFINED:{state}:{e}", trace
        state = t.to
        trace.append(f"--{e}[{'⚖' + t.law_pid if t.level == 'statute' else t.pid}]--> {state}")
    return state, trace
