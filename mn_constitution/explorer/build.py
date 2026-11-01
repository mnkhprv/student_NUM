"""Inject out/report.json into the explorer template -> out/explorer.html"""
import json
from pathlib import Path

root = Path(__file__).resolve().parent.parent
data = json.loads((root / "out" / "report.json").read_text(encoding="utf-8"))
payload = json.dumps(data, ensure_ascii=False).replace("</", "<\\/")
html = (root / "explorer" / "template.html").read_text(encoding="utf-8").replace("__DATA__", payload)
(root / "out" / "explorer.html").write_text(html, encoding="utf-8")
print(f"out/explorer.html {len(html.encode()) // 1024} KB")
