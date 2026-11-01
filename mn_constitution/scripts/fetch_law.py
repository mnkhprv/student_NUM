"""Save a law's text:  python3 scripts/fetch_law.py <key> <lawId>
Needs network access to legalinfo.mn (blocked in the dev sandbox). If the page is JS-rendered the
result will be a shell, not text: then copy the text from the site into constitution/text/laws/<key>.txt.
Also set law_id + verified in registry.json."""
import re, sys, urllib.request, datetime, html
from pathlib import Path

key, lid = sys.argv[1], sys.argv[2]
url = f"https://legalinfo.mn/mn/detail?lawId={lid}"
raw = urllib.request.urlopen(urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"}), timeout=30).read().decode("utf-8", "replace")
text = html.unescape(re.sub(r"<[^>]+>", "\n", re.sub(r"(?s)<(script|style).*?</\1>", "", raw)))
text = "\n".join(l.strip() for l in text.splitlines() if l.strip())
if len(text) < 2000 or "зүйл" not in text:
    sys.exit("fetched page has no law text (likely JS-rendered); paste it manually")
out = Path(__file__).resolve().parent.parent / "constitution/text/laws" / f"{key}.txt"
out.write_text(f"Эх сурвалж: {url} (татсан {datetime.date.today()})\n{text}\n", encoding="utf-8")
print("wrote", out)
