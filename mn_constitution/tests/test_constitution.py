from constitution import checks, stress
from constitution.articles import ARTICLES, TOTAL_SEATS, all_provisions
from constitution.procedures import MACHINES, PM_DISMISSAL, run
from constitution.text_mn import lookup, ordinal_to_int, parse

ARTS = parse()


def test_parses_all_71_articles_from_mongolian():
    assert len(ARTS) == 71
    assert "19¹" in ARTS and "70" in ARTS


def test_ordinals():
    assert ordinal_to_int("Гучин гурав") == 33
    assert ordinal_to_int("Дал") == 70
    assert ordinal_to_int("Арван ес") == 19


def test_model_covers_every_article():
    assert {a.number for a in ARTICLES} == set(ARTS)


def test_every_provision_resolves_to_mongolian_text():
    for _, p in all_provisions():
        pid = p.pid.replace(".b", "").replace(".c", "")
        assert lookup(ARTS, pid), p.pid


def test_all_quotes_are_verbatim():
    # q() raises if a quote is not literally in the provision
    fs = checks.run_all()
    assert fs and all(f.severity in checks.SEV_ORDER for f in fs)


def test_amendment_needs_95_of_126():
    row = next(r for r in checks.majority_capture_table() if r["pid"] == "69.1")
    assert TOTAL_SEATS == 126 and row["seats_needed"] == 95


def test_veto_override_below_law_threshold():
    assert any(f.rule == "THRESHOLD_INVERSION" for f in checks.run_all())


def test_2025_crisis_hits_undefined_transition():
    final, trace = run(PM_DISMISSAL, ["motion_by_quarter", "debate_after_3_days", "vote_majority_total", "president_veto"])
    assert final.startswith("UNDEFINED") and "president_veto" in final


def test_dismissal_with_new_pm_is_defined():
    final, _ = run(PM_DISMISSAL, ["motion_by_quarter", "debate_after_3_days", "vote_majority_total", "new_pm_appointed"])
    assert final == "NEW_PM"


def test_president_emergency_decree_lapses():
    r = stress.s2_president_emergency_final_year()
    assert r.verdict == "pass"


def test_96_seats_can_amend_alone():
    assert stress.s1_supermajority_extends_term(96).verdict == "fail"
    assert stress.s1_supermajority_extends_term(90).verdict == "partial"


def test_machines_have_known_starts():
    for m in MACHINES:
        assert any(s == m.start for s, _ in m.transitions), m.name


def test_law_parser_and_guard(tmp_path, monkeypatch):
    from constitution import laws
    fx = "1 дүгээр зүйл. Зорилго\n1.1.Энэ хуулийн зорилго\nнь туршилт мөн.\n2 дугаар зүйл. Нэр\n2.1.Хоёр."
    a = laws.parse_law(fx)
    assert a[1].sections["1.1"] == "Энэ хуулийн зорилго нь туршилт мөн." and set(a) == {1, 2}
    (tmp_path / "900.txt").write_text(fx, encoding="utf-8")
    monkeypatch.setattr(laws, "DIR", tmp_path)
    assert "туршилт" in laws.q_law("900", 1, "нь туршилт")
    import pytest
    with pytest.raises(ValueError):
        laws.q_law("900", 1, "байхгүй үг")


def test_delegation_index_nonempty():
    from constitution.laws import delegation_index
    assert len(delegation_index()) > 20


def test_delegation_index_item_pids():
    from constitution.laws import delegation_index
    from constitution.text_mn import parse, lookup
    arts, idx = parse(), dict()
    for pid, s in delegation_index():
        idx.setdefault(pid, s)
        assert pid.count(".") >= 1, pid                       # never a bare article number
        txt = lookup(arts, pid)
        assert s.rstrip(";.") in txt or s in txt, (pid, s)     # label resolves to text containing the sentence
    assert "17.1.3" in idx and any(k.startswith("16.") for k in idx)


def test_text_21_1_matches_total_seats():
    from constitution.checks import q
    assert TOTAL_SEATS == 126 and q("21.1", "нэг зуун хорин зургаан гишүүнтэй байна")


def test_statute_closures_verbatim_and_applied():
    import pytest
    from constitution import statutes
    from constitution.checks import run_all
    if not statutes.available():
        pytest.skip("statute texts not downloaded (scripts/ingest_archive.py)")
    for c in statutes.CLOSURES:
        c.evidence()                                    # raises if any phrase is not literally in that section
    fs = run_all()
    hit = [f for f in fs if f.title.startswith(("[ХУУЛИАР", "[ХУУЛЬД"))]
    assert len(hit) == len(statutes.CLOSURES)           # each closure matched exactly one finding
    assert all(f.severity != "critical" for f in hit if "ХЭСЭГЧЛЭН" in f.title)
    assert {"STATUTE_THRESHOLD", "STATUTE_CONFLICT", "VETO_WINDOW_SET_BY_HURAL"} <= {f.rule for f in fs}


def test_closure_steps_severity_down():
    from constitution.statutes import Closure, apply
    from constitution.model import Finding
    f = Finding("X", "high", "bug", ("1",), "abc", "")
    c = Closure("X", ("abc",), "partial", (), "gap")
    import constitution.statutes as s
    old, s.CLOSURES = s.CLOSURES, [c]
    try:
        apply([f])
    finally:
        s.CLOSURES = old
    assert f.severity == "medium" and f.title.startswith("[ХУУЛИАР ХЭСЭГЧЛЭН")


def test_law_parser_three_level_items():
    from constitution.laws import parse_law
    a = parse_law("46 дугаар зүйл. Х\n46.1.Эх:\n46.1.1.нэг;\n46.1.2.хоёр.\n46.2.Дараах.")
    assert a[46].sections == {"46.1": "Эх:", "46.1.1": "нэг;", "46.1.2": "хоёр.", "46.2": "Дараах."}


def test_statute_machine_layer():
    import pytest
    from constitution import statute_machines as sm
    from constitution.procedures import VETO, TSETS, run
    if not sm.available():
        pytest.skip("statute texts not downloaded")
    assert sm.verify() >= 20                                   # every statute edge/deadline/note quoted verbatim
    assert run(VETO, ["president_vetoes", "override_fails"])[0].startswith("UNDEFINED")
    assert run(sm.layered(VETO), ["president_vetoes", "override_fails"])[0] == "IN_FORCE"
    assert run(sm.layered(TSETS), ["tsets_accepts_case", "conclusion_issued", "hural_rejects", "no_two_thirds"])[0] == "RESOLVED"
    lv = sm.layered(VETO)
    assert lv.transitions[("LAW_PASSED", "president_vetoes")].deadline_days == 5
    assert VETO.transitions[("LAW_PASSED", "president_vetoes")].deadline_days is None   # constitution layer untouched


def test_stress_with_laws():
    from constitution import stress, statute_machines as sm
    rs = stress.run_all()
    if sm.available():
        assert {r.n for r in rs if r.verdict_laws} == {1, 4, 5, 7}
        assert any("⚖3.6" in x for x in stress.s5_tsets_vs_majority().trace_laws)
