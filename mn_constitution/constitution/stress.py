"""The seven stress-test scenarios, replayed against the model."""
from __future__ import annotations

from dataclasses import dataclass, field

from .articles import TOTAL_SEATS, get
from .procedures import AMENDMENT, EMERGENCY, FORMATION, PM_DISMISSAL, TSETS, run


@dataclass
class StressResult:
    n: int
    title: str
    verdict: str        # "pass" | "partial" | "fail"
    break_point: str
    trace: list[str]
    verdict_laws: str | None = None       # same scenario on Constitution + statute (None = no statute modelled)
    note_laws: str = ""
    trace_laws: list[str] = field(default_factory=list)


def _laws():
    from . import statute_machines as sm
    return sm if sm.available() else None


def with_laws(r: StressResult, verdict: str, note: str, *runs) -> StressResult:
    sm = _laws()
    if sm:
        r.verdict_laws, r.note_laws = verdict, note
        for m, evs in runs:
            r.trace_laws += (["‖"] if r.trace_laws else []) + run(sm.layered(m), evs)[1]
    return r


def s1_supermajority_extends_term(seats: int = 96) -> StressResult:
    need = get("69.1").threshold.seats_needed(TOTAL_SEATS)
    route_a, trace_a = run(AMENDMENT, ["vote_3_4_total"])          # amend 21.2 directly
    route_b, trace_b = run(EMERGENCY, ["hural_declares", "regular_election_due"])  # 22.1 holdover
    can_amend = seats >= need
    r = StressResult(1, f"Нэг нам {seats}/{TOTAL_SEATS} суудалтай бүрэн эрхээ сунгах", "fail" if can_amend else "partial",
                     f"69.1: {need} санал хангалттай ({seats} ≥ {need}); өөрчлөгдөшгүй цөм алга. Эсвэл 25.1.18 + 22.1-ээр "
                     f"онц байдал зарлаж хугацаагүй сунгана (төгсгөл: {route_b}).",
                     trace_a + ["‖"] + trace_b)
    return with_laws(r, "fail" if can_amend else "partial",
                     "Онц байдлын тухай хууль: дуусах огноо заавал (5.7), сунгахад ҮАБЗ-ийн санал (6.2), онц байдлын үед Үндсэн хуулийг "
                     "өөрчлөхийг хориглоно (19). Гэвч сунгалтын тоо хязгааргүй — 22.1-ийн замаар сунгалт бүрийг ҮАБЗ дэмжвэл зогсолтгүй; "
                     "69.1-ийн зам онц байдлаас гадуур нээлттэй хэвээр.",
                     (EMERGENCY, ["hural_declares", "regular_election_due", "nsc_extension", "nsc_extension", "nsc_extension"]))


def s2_president_emergency_final_year() -> StressResult:
    final, trace = run(EMERGENCY, ["president_declares_in_recess", "hural_silent_7d"])
    ok = final == "NORMAL"
    return StressResult(2, "Ерөнхийлөгч сүүлийн жилдээ жагсаалын үед онц байдал зарлах", "pass" if ok else "fail",
                        "33.1.12: УИХ 7 хоногт батлахгүй бол зарлиг автоматаар хүчингүй; 27.5: 72 цагт чуулна; 30.2: дахин сонгогдохгүй тул "
                        "сунгах хөшүүрэггүй. Үлдэх цоорхой: 19.2-ын хязгаарлалтад хугацаа, пропорциональ шалгуургүй.", trace)


def s3_mine_vs_herders() -> StressResult:
    return StressResult(3, "Гадаадын уурхайн тусгай зөвшөөрөл малчдын цорын ганц өвөлжөө, худагтай зөрчилдөх", "fail",
                        "6.1 «ард түмний мэдэл» нь үүрэг хүлээгч, тэргүүлэх дарааллыг заадаггүй; 6.3 бэлчээрийг өмчлүүлэхгүй ч "
                        "ашиглах эрхийг хамгаалдаггүй; 16.2 эрх бий ч 66.1-ээр Цэц зөвхөн хууль, шийдвэрийг хянана — тусгай зөвшөөрлийг биш. "
                        "Шийдлийг ердийн хууль, тусгай зөвшөөрөл олгогч Засгийн газар гаргана.",
                        ["NO MACHINE: Үндсэн хуульд процедур алга"])


def s4_government_falls_before_budget() -> StressResult:
    final, trace = run(FORMATION, ["party_nominates", "president_submits_5d", "no_appointment_45d", "president_does_nothing"])
    r = StressResult(4, "Төсөв батлахаас сарын өмнө Засгийн газар унах", "partial",
                     "40.2: огцорсон Засгийн газар шинэ Ерөнхий сайд томилогдтол үргэлжилнэ (тасралтгүй байдал хангагдана). "
                     "Гэвч анхдагч төсөв (санхүүгийн жил эхлэхэд төсөвгүй үеийн журам) алга; 22.3-ын тараах шийдвэрт хугацаагүй "
                     f"(төгсгөл: {final}).", trace)
    return with_laws(r, "partial",
                     "Дэгийн тухай хууль: тараасны дараа 10 хоногт ээлжит бус сонгууль зарлана (94.1) — тараасан бол зам тодорхой. "
                     "Ерөнхийлөгч тараах шийдвэр гаргахгүй байвал хууль ч юу болохыг заагаагүй; анхдагч төсвийн журмыг энэ загвар "
                     "Төсвийн тухай хуулиас шалгаагүй.",
                     (FORMATION, ["party_nominates", "president_submits_5d", "no_appointment_45d", "president_dissolves", "snap_election_called"]),
                     (FORMATION, ["party_nominates", "president_submits_5d", "no_appointment_45d", "president_does_nothing"]))


def s5_tsets_vs_majority() -> StressResult:
    final, trace = run(TSETS, ["tsets_accepts_case", "conclusion_issued", "hural_rejects", "final_decision"])
    stalled, trace2 = run(TSETS, ["tsets_accepts_case", "conclusion_issued", "hural_never_considers"])
    r = StressResult(5, "Цэц эдийн засгийн чухал хуульд УИХ-ын олонхын эсрэг шийдвэр гаргах", "partial",
                     f"Эцсийн шийдвэр гарвал 66.4, 67-оор шууд хүчингүй ({final}) — хүчтэй. Гэвч УИХ дүгнэлтийг хэлэлцэхгүй "
                     f"орхивол хугацаагүй гацна ({stalled}); энэ хугацаанд хууль үйлчилнэ. 65.1: шинэ олонх Цэцийн бүрэлдэхүүнийг солих боломжтой.",
                     trace + ["‖"] + trace2)
    return with_laws(r, "partial",
                     "Цэцийн ажиллагааны тухай хууль: УИХ 15 хоногт шийдвэрлэнэ (35.2), дүгнэлт гармагц заалт түдгэлзэнэ (32.4) — "
                     "УИХ-ын хойшлуулах хөшүүрэг алга болно. Шинэ сул тал: дахин хянахад гишүүдийн 2/3 шаардлагатай, хүрэхгүй бол "
                     "хууль хүчинтэй үлдэнэ (3.6) — 9 гишүүний 4 нь УИХ-ын олонхыг хамгаалж чадна.",
                     (TSETS, ["tsets_accepts_case", "conclusion_issued", "hural_rejects", "no_two_thirds"]),
                     (TSETS, ["tsets_accepts_case", "conclusion_issued", "hural_never_considers"]))


def s6_ai_surveillance() -> StressResult:
    return StressResult(6, "Хуулийн үндэслэлгүй төрийн хиймэл оюуны тандалт", "partial",
                        "16.13 «хуульд заасан үндэслэл, журмаас гадуур дур мэдэн ... мөрдөн мөшгих»-ийг хориглоно — хуульгүй тандалтад "
                        "хамаарна гэж тайлбарлаж болно. Гэвч хувийн мэдээлэл, алгоритм, биометрийн тухай заалт алга; Цэц захиргааны бодит "
                        "үйл ажиллагааг шууд хянадаггүй (66.2.1 — «шийдвэр»).", ["NO MACHINE"])


def s7_dzud() -> StressResult:
    final, trace = run(EMERGENCY, ["hural_declares", "hural_lifts"])
    r = StressResult(7, "Зудаар нийт малын 20% хорогдох", "partial",
                        "25.2.1-ээр байгалийн гамшгийн онц байдал зарлаж болно; 5.5 мал «төрийн хамгаалалтад» ч үүрэг, хэмжүүр, "
                        "нэхэмжлэх эрх алга; 16.5 тусламж зөвхөн нас, хөдөлмөрийн чадвар, хүүхэдтэй холбоотой — малчны амьжиргааны "
                        "алдагдлыг хамарсан баталгаа алга.", trace)
    return with_laws(r, "partial",
                     "Онц байдлын тухай хууль 4-р зүйл: «гамшиг»-аар онц байдал зарлаж болно, дуусах огноотой. Малчны алдагдлын нөхөн "
                     "олговрыг Гамшгаас хамгаалах, Малын генетик нөөцийн тухай зэрэг хуулиас хараахан шалгаагүй.",
                     (EMERGENCY, ["hural_declares", "end_date_reached"]))


ALL = [s1_supermajority_extends_term, s2_president_emergency_final_year, s3_mine_vs_herders,
       s4_government_falls_before_budget, s5_tsets_vs_majority, s6_ai_surveillance, s7_dzud]


def run_all() -> list[StressResult]:
    return [f() for f in ALL]
