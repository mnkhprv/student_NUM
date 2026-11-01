"""Core types for modelling the Constitution of Mongolia (1992, consolidated)."""
from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum
from fractions import Fraction
from typing import Optional


class Kind(str, Enum):
    RIGHT = "right"              # эрхтэй / эрх чөлөөтэй
    DUTY = "duty"                # үүрэгтэй / ... хангана (bearer is named)
    PROHIBITION = "prohibition"  # хориглоно / ... үл болно / ... болохгүй
    POWER = "power"              # бүрэн эрх
    PROCEDURE = "procedure"      # step of a state procedure
    DECLARATION = "declaration"  # descriptive "-на/-нэ", "... мөн"
    DELEGATION = "delegation"    # "... хуулиар тогтооно"


class Base(str, Enum):
    TOTAL = "total"        # нийт гишүүний
    PRESENT = "present"    # хуралдаанд оролцсон гишүүний
    VOTERS = "voters"      # сонгуулийн эрх бүхий иргэд
    UNDEFINED = "undefined"


@dataclass(frozen=True)
class Threshold:
    fraction: Optional[Fraction]   # None = not stated numerically
    base: Base
    wording: str = ""

    def seats_needed(self, total_seats: int, present: Optional[int] = None) -> Optional[int]:
        """Minimum yes-votes. For PRESENT base, `present` defaults to the quorum."""
        if self.fraction is None:
            return None
        if self.base is Base.TOTAL:
            pool = total_seats
        elif self.base is Base.PRESENT:
            pool = present if present is not None else total_seats // 2 + 1
        else:
            return None
        need = self.fraction * pool
        # "not less than" -> ceiling; "majority" (1/2) -> strictly more than half
        if self.fraction == Fraction(1, 2):
            return pool // 2 + 1
        return -(-need.numerator // need.denominator)


MAJORITY_TOTAL = Threshold(Fraction(1, 2), Base.TOTAL, "нийт гишүүний олонхи")
MAJORITY_PRESENT = Threshold(Fraction(1, 2), Base.PRESENT, "оролцсон гишүүдийн олонхи")
TWO_THIRDS_TOTAL = Threshold(Fraction(2, 3), Base.TOTAL, "нийт гишүүний гуравны хоёр")
TWO_THIRDS_PRESENT = Threshold(Fraction(2, 3), Base.PRESENT, "оролцсон нийт гишүүний гуравны хоёр")
THREE_QUARTERS_TOTAL = Threshold(Fraction(3, 4), Base.TOTAL, "нийт гишүүний дөрөвний гурав")
QUARTER_TOTAL = Threshold(Fraction(1, 4), Base.TOTAL, "нийт гишүүний дөрөвний нэг")
UNDEFINED_SUPERMAJORITY = Threshold(None, Base.PRESENT, "дийлэнх олонхи (тоо заагаагүй)")


@dataclass
class Provision:
    pid: str                       # e.g. "33.1.1"
    kind: Kind
    actor: str                     # duty bearer / power holder ("" = none named)
    summary: str                   # short Mongolian paraphrase
    delegates: bool = False        # sends content to ordinary law
    limits: Optional[str] = None   # substantive limits on the delegation, if any
    deadline_days: Optional[float] = None
    threshold: Optional[Threshold] = None
    terms: tuple[str, ...] = ()    # key terms used (checked against glossary)
    amended: tuple[int, ...] = ()
    remedy: Optional[str] = None   # who enforces / what happens on breach

    @property
    def article(self) -> str:
        return self.pid.split(".")[0]


@dataclass
class Article:
    number: str            # "19" or "19¹"
    chapter: int
    title: str
    provisions: list[Provision] = field(default_factory=list)


@dataclass
class Finding:
    rule: str          # rule id, e.g. "UNDEFINED_TRANSITION"
    severity: str      # "critical" | "high" | "medium" | "low"
    category: str      # "bug" (logic/procedure defect) | "design" (weak but coherent) | "text" (drafting)
    articles: tuple[str, ...]
    title: str
    detail: str
    evidence: str = ""  # [TEXT: ...] / [CASE: ...]
    fix: str = ""       # proposed clause (Mongolian)

    def key(self) -> tuple:
        return (self.rule, self.articles, self.title)
