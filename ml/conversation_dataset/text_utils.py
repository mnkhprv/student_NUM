"""Shared text cleanup used by both dataset-building scripts."""
import re

NOISE_PATTERNS = [
    re.compile(r"^.+ sent an attachment\.$"),
    re.compile(r"^Liked a message$"),
    re.compile(r"^.+ liked a message$"),
    re.compile(r"^.+ set the .+ theme\.$"),
    re.compile(r"^You are now connected on Messenger\.?$"),
    re.compile(r"^You're now friends with .+\.?$"),
    re.compile(r"^You can now message and call each other.*$"),
    re.compile(r"^This account was created before.*$"),
    re.compile(r"^.+ changed the group photo\.?$"),
    re.compile(r"^.+ (added|removed|left the group|joined the (group|call))\.?$"),
    re.compile(r"^.+ changed the chat colou?r to .+\.?$"),
    re.compile(r"^.+ changed the nickname for .+\.?$"),
    re.compile(r"^.+ named the group .+\.?$"),
    re.compile(r"^.+ removed .+ from the group\.?$"),
    # calls
    re.compile(r"^(You |.+ )?missed (a|an) (video |audio )?(call|chat).*$", re.IGNORECASE),
    re.compile(r"^.+ missed your (video )?call\.?$", re.IGNORECASE),
    re.compile(r"^(The )?(Audio|Video) call (started|ended)\.?$", re.IGNORECASE),
    re.compile(r"^(You started|.+ started) (a video chat|an audio call)\.?$"),
    re.compile(r"^(Video chat|Audio call) ended\.?$"),
    re.compile(r"^.+ joined the (video |audio )?call\.?$", re.IGNORECASE),
    # reactions/unsend (both passive and active phrasing)
    re.compile(r"^Reacted .+ to your message\s*$"),
    re.compile(r"^.+ reacted .+ to (your|the) message\s*$", re.IGNORECASE),
    re.compile(r"^User unsent a message$"),
    re.compile(r"^.+ unsent a message$"),
    # stories / marketplace / nicknames / quick reaction
    re.compile(r"^.+ shared a story\.?$", re.IGNORECASE),
    re.compile(r"^.+ removed the item from Marketplace\.?$", re.IGNORECASE),
    re.compile(r"^.+ changed the (theme|price for .+)\.?$", re.IGNORECASE),
    re.compile(r"^.+ set (your|the) nickname( for .+)? to .+\.?$", re.IGNORECASE),
    re.compile(r"^.+ set the quick reaction to .+\.?$", re.IGNORECASE),
    # generic Messenger-bot / business-page auto flow
    re.compile(r"^Get [Ss]tarted$"),
    re.compile(r"^Sent a doodle\. Update your app to view\.( Update)?$"),
]

# Exact/near-exact canned phrases that only show up in business-page /
# customer-service threads (found by looking for long messages repeated
# verbatim across multiple otherwise-unrelated conversations — real people
# don't say the same long sentence to several different friends, but
# Messenger's auto-replies and ad-opener banners do). If any of these shows
# up in a thread, the whole thread is a business/bot conversation, not a
# real person — drop the thread entirely, not just the matching line.
BUSINESS_THREAD_SIGNALS = [
    re.compile(r"^You opened this chat through an ad\..*$"),
    re.compile(r"^Hi Munkhpurev! Please let us know how we can help you\.$"),
    re.compile(r"^Hi, thanks for contacting us\. We've received your message.*$", re.IGNORECASE),
    re.compile(r"^We've let .+ know you're waiting for a response\.$"),
    re.compile(r"^Tand uur asuuj todruulah zuil baina uu\?$", re.IGNORECASE),
]


def is_business_signal(content):
    return any(p.match(content) for p in BUSINESS_THREAD_SIGNALS)


def fix_mojibake(text):
    try:
        return text.encode("latin1").decode("utf-8")
    except (UnicodeDecodeError, UnicodeEncodeError):
        return text


def is_noise(content):
    return any(p.match(content) for p in NOISE_PATTERNS)


# Mongolian Cyrillic -> Latin, using the informal romanization conventions
# already present in this corpus (h for х, sh for ш, ch for ч, yu/ya for ю/я,
# rounded vowels о/у/ө/ү collapsed toward o/u the way casual typers do).
_CYRILLIC_TO_LATIN = {
    "а": "a", "б": "b", "в": "v", "г": "g", "д": "d", "е": "e", "ё": "yo",
    "ж": "j", "з": "z", "и": "i", "й": "i", "к": "k", "л": "l", "м": "m",
    "н": "n", "о": "o", "ө": "u", "п": "p", "р": "r", "с": "s", "т": "t",
    "у": "u", "ү": "u", "ф": "f", "х": "h", "ц": "c", "ч": "ch", "ш": "sh",
    "щ": "sh", "ъ": "", "ы": "i", "ь": "", "э": "e", "ю": "yu", "я": "ya",
    "ѳ": "u",  # Cyrillic Fita, sometimes used as a stand-in glyph for ө
}
# Capitalized variants: capitalize only the first output letter, so е.g.
# 'Ч' (start of a sentence/name) becomes 'Ch', not 'CH'.
_CYRILLIC_TO_LATIN.update({
    k.upper(): (v[0].upper() + v[1:] if v else v)
    for k, v in _CYRILLIC_TO_LATIN.items()
})

_CYRILLIC_RE = re.compile("[" + "".join(_CYRILLIC_TO_LATIN) + "]")


def transliterate(text):
    """Convert any Mongolian Cyrillic characters in text to Latin. Leaves
    already-Latin text, emoji, digits, and punctuation untouched."""
    return _CYRILLIC_RE.sub(lambda m: _CYRILLIC_TO_LATIN[m.group(0)], text)


def merge_consecutive(rows, gap_ms=2 * 60 * 1000):
    """Collapse consecutive same-sender (ts, sender, content) rows sent
    within gap_ms of each other into one turn, so the conversation
    alternates cleanly speaker A / speaker B / speaker A / ... instead of
    runs of several same-sender lines in a row."""
    merged = []
    for ts, sender, content in rows:
        if (merged
                and merged[-1][1] == sender
                and ts - merged[-1][0] <= gap_ms):
            prev_ts, prev_sender, prev_content = merged[-1]
            merged[-1] = (ts, prev_sender, prev_content + "\n" + content)
        else:
            merged.append((ts, sender, content))
    return merged


def force_alternate(rows):
    """Merge ANY consecutive same-sender rows, regardless of time gap, so
    the conversation strictly zigzags A / B / A / B / ... with no
    exceptions (unlike merge_consecutive, which only merges bursts sent
    close together in time and leaves later same-speaker turns separate)."""
    merged = []
    for ts, sender, content in rows:
        if merged and merged[-1][1] == sender:
            prev_ts, prev_sender, prev_content = merged[-1]
            merged[-1] = (ts, prev_sender, prev_content + "\n" + content)
        else:
            merged.append((ts, sender, content))
    return merged
