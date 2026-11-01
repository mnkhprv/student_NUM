from pathlib import Path
import subprocess

from docx import Document
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.oxml.ns import qn
from docx.shared import Cm, Pt
from PIL import Image, ImageDraw, ImageFont


BASE = Path("/home/lunatic/Desktop/2026fall/operatingSystemsTheory/lab3")
DOCX = BASE / "Lab03_23B1NUM0114.docx"
IMG_DIR = BASE / "terminal_screenshots"
IMG_DIR.mkdir(exist_ok=True)


def run_capture(command, seconds=2):
    proc = subprocess.run(
        ["bash", "-lc", f"stdbuf -o0 timeout {seconds} {command}"],
        cwd=BASE,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    lines = []
    for line in proc.stdout.splitlines():
        if "Failed to create stream fd" in line:
            continue
        lines.append(line.rstrip())
    return "\n".join(lines).strip()


def load_font(size):
    candidates = [
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationMono-Regular.ttf",
    ]
    for path in candidates:
        if Path(path).exists():
            return ImageFont.truetype(path, size)
    return ImageFont.load_default()


def terminal_image(title, command, output, out_path, max_lines=38):
    font = load_font(24)
    small_font = load_font(20)
    prompt = f"$ {command}"
    lines = [prompt] + output.splitlines()
    if len(lines) > max_lines:
        lines = lines[: max_lines - 1] + ["..."]

    char_w = 14
    line_h = 32
    pad_x = 34
    pad_y = 74
    content_width = max(len(line) for line in lines) * char_w + pad_x * 2
    width = max(1180, min(1600, content_width))
    height = pad_y + len(lines) * line_h + 30

    img = Image.new("RGB", (width, height), "#16181d")
    draw = ImageDraw.Draw(img)
    draw.rounded_rectangle([0, 0, width - 1, height - 1], radius=18, fill="#16181d", outline="#30343b", width=2)
    draw.rounded_rectangle([0, 0, width - 1, 54], radius=18, fill="#242832")
    draw.rectangle([0, 32, width - 1, 54], fill="#242832")
    for i, color in enumerate(["#ff5f57", "#ffbd2e", "#28c840"]):
        draw.ellipse([26 + i * 34, 18, 44 + i * 34, 36], fill=color)
    draw.text((width // 2, 14), title, anchor="ma", fill="#d7dae0", font=small_font)

    y = pad_y
    for index, line in enumerate(lines):
        fill = "#9cdcfe" if index == 0 else "#e6edf3"
        draw.text((pad_x, y), line, fill=fill, font=font)
        y += line_h
    img.save(out_path)


def set_run_font(run, name="Times New Roman", size=12, bold=None):
    run.font.name = name
    run._element.rPr.rFonts.set(qn("w:eastAsia"), name)
    run.font.size = Pt(size)
    if bold is not None:
        run.bold = bold


def add_heading(doc, text, level=1):
    p = doc.add_heading(text, level=level)
    for run in p.runs:
        set_run_font(run, size=14 if level == 1 else 13, bold=True)
    return p


def add_caption(doc, text):
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    r = p.add_run(text)
    set_run_font(r, size=12)


def remove_existing_appendix_b(doc):
    body = doc._body._element
    children = list(body)
    start_index = None
    for idx, child in enumerate(children):
        text = "".join(node.text or "" for node in child.iter() if node.tag == qn("w:t"))
        if text.strip().startswith("Хавсралт Б. Терминалын гаралтын зураг"):
            start_index = idx
            break
    if start_index is None:
        return
    sect_pr = children[-1] if children and children[-1].tag == qn("w:sectPr") else None
    for child in children[start_index:]:
        if child is not sect_pr:
            body.remove(child)
    if sect_pr is not None and sect_pr not in list(body):
        body.append(sect_pr)


items = [
    ("lab3_terminal.png", "Lab3 нэгдсэн програм", "./lab3", "./lab3", 44),
    ("process1_terminal.png", "Process1 массив эрэмбэлэх", "./process1", "./process1", 24),
    ("process2_terminal.png", "Process2 матриц нэмэх", "./process2", "./process2", 30),
    ("process3_terminal.png", "Process3 тэмдэгтийн давтамж", "./process3", "./process3", 30),
]

images = []
for filename, title, command, shell_command, max_lines in items:
    output = run_capture(shell_command)
    image_path = IMG_DIR / filename
    terminal_image(title, command, output, image_path, max_lines=max_lines)
    images.append((image_path, title))

doc = Document(str(DOCX))
remove_existing_appendix_b(doc)
doc.add_page_break()
add_heading(doc, "Хавсралт Б. Терминалын гаралтын зураг", 1)

for idx, (image_path, title) in enumerate(images, 1):
    if idx > 1:
        doc.add_page_break()
    add_caption(doc, f"Зураг {idx}. {title} ажилласан terminal гаралт")
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = p.add_run()
    run.add_picture(str(image_path), width=Cm(16))

doc.save(DOCX)
print(DOCX)
