"""Replay events through a machine.

  python3 -m constitution.trace                         # list machines
  python3 -m constitution.trace veto                    # transitions, undefined events, stalls
  python3 -m constitution.trace veto president_vetoes override_fails
  add --statutes to any of these to use constitution + statute (⚖ = defined only by ordinary law)
"""
import sys

from .procedures import MACHINES, run, stall_points, undefined_transitions


def fmt(t):
    from .statute_machines import cite
    return f"[{cite(t)}]"


def main(a):
    layered = "--statutes" in a
    a = [x for x in a if x != "--statutes"]
    by = {m.name: m for m in MACHINES}
    if not a:
        print("\n".join(f"{m.name:14} {m.title}" for m in MACHINES)); return
    m = by[a[0]]
    notes = {}
    if layered:
        from .statute_machines import layered as lay, state_notes
        m, notes = lay(m), state_notes(m)
    if len(a) == 1:
        print(f"{m.title}\nstart={m.start}")
        for (s, e), t in m.transitions.items():
            print(f"  {s} --{e}--> {t.to} {fmt(t)}")
        for s, n in notes.items():
            print(f"  note {s}: {n}")
        print("UNDEFINED:")
        for s, e in undefined_transitions(m):
            print(f"  {s} / {e}: {m.note.get((s, e), '')}")
        print("STALL:", [k for k, _ in stall_points(m)]); return
    state, trace = m.start, [m.start]
    for e in a[1:]:
        t = m.transitions.get((state, e))
        if t is None:
            trace.append(f"UNDEFINED({e})"); state = f"UNDEFINED:{state}:{e}"; break
        state = t.to
        trace.append(f"--{e} {fmt(t)}--> {state}" + (f"   ({notes[state]})" if state in notes else ""))
    print("\n".join(trace)); print("=>", state)


main(sys.argv[1:])
