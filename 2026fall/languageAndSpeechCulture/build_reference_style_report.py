from pathlib import Path
import re

from docx import Document
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.oxml import OxmlElement
from docx.oxml.ns import qn
from docx.shared import Cm, Pt


INPUT = Path("/home/lunatic/.codex/attachments/e09f73ce-a583-4b1e-bccf-4cf47d3e7ef3/Pasted text.txt")
OUT = Path("languageAndSpeechCulture/humuunleg_ug_final_report.docx")


def parse_rows():
    lines = [line.strip() for line in INPUT.read_text(encoding="utf-8").splitlines() if line.strip()]
    rows = []
    i = 0
    while i < len(lines):
        if re.fullmatch(r"\d+", lines[i]):
            n = int(lines[i])
            category = re.sub(r"^\d+\.\s*", "", lines[i + 1])
            example = lines[i + 2].strip("«»")
            source = lines[i + 3]
            reason = lines[i + 4]
            rows.append((n, category, example, source, reason))
            i += 5
        else:
            i += 1
    return rows


def font_run(run, size=12, bold=False, italic=False):
    run.font.name = "Times New Roman"
    run._element.rPr.rFonts.set(qn("w:eastAsia"), "Times New Roman")
    run.font.size = Pt(size)
    run.bold = bold
    run.italic = italic


def set_style_font(style, size=12, bold=False, italic=False):
    style.font.name = "Times New Roman"
    style._element.rPr.rFonts.set(qn("w:eastAsia"), "Times New Roman")
    style.font.size = Pt(size)
    style.font.bold = bold
    style.font.italic = italic


def add_page_number(paragraph):
    paragraph.alignment = WD_ALIGN_PARAGRAPH.CENTER
    fld_begin = OxmlElement("w:fldChar")
    fld_begin.set(qn("w:fldCharType"), "begin")
    instr = OxmlElement("w:instrText")
    instr.set(qn("xml:space"), "preserve")
    instr.text = "PAGE"
    fld_end = OxmlElement("w:fldChar")
    fld_end.set(qn("w:fldCharType"), "end")
    run = paragraph.add_run()
    run._r.append(fld_begin)
    run._r.append(instr)
    run._r.append(fld_end)
    font_run(run)


def define_styles(doc):
    styles = doc.styles
    set_style_font(styles["Normal"], 12)
    set_style_font(styles["Title"], 12, bold=True)
    set_style_font(styles["Heading 1"], 12, bold=True)

    for name in ("Question", "Answer", "Basis"):
        if name not in styles:
            styles.add_style(name, 1)
    set_style_font(styles["Question"], 12, bold=True)
    set_style_font(styles["Answer"], 12)
    set_style_font(styles["Basis"], 12, italic=True)


def add_paragraph(doc, text, style="Normal", align=None, first_indent=False, space_after=4):
    p = doc.add_paragraph(style=style)
    if align is not None:
        p.alignment = align
    p.paragraph_format.line_spacing = 1.15
    p.paragraph_format.space_after = Pt(space_after)
    if first_indent:
        p.paragraph_format.first_line_indent = Cm(1)
    run = p.add_run(text)
    if style == "Question":
        font_run(run, bold=True)
    elif style == "Basis":
        font_run(run, italic=True)
    elif style in ("Title", "Heading 1"):
        font_run(run, bold=True)
    else:
        font_run(run)
    return p


def build():
    rows = parse_rows()
    doc = Document()
    define_styles(doc)

    section = doc.sections[0]
    section.top_margin = Cm(2.0)
    section.bottom_margin = Cm(1.8)
    section.left_margin = Cm(2.0)
    section.right_margin = Cm(2.0)
    add_page_number(section.footer.paragraphs[0])

    add_paragraph(
        doc,
        "Д.Бадамдоржийн «Хүмүүнлэг үг»-ийн 15 ангиллын жишээ ба тайлбар",
        style="Normal",
        align=WD_ALIGN_PARAGRAPH.CENTER,
        space_after=8,
    ).runs[0].bold = True
    info = add_paragraph(
        doc,
        "Оюутны нэр  Н. Мөнхпүрэв Анги: Программ хангамж SiSi ID: 23B1NUM0114",
        align=WD_ALIGN_PARAGRAPH.CENTER,
        space_after=10,
    )
    for r in info.runs:
        r.italic = True

    add_paragraph(
        doc,
        "Энэхүү даалгаварт Д.Бадамдоржийн «Хүмүүнлэг үг»-ийн 15 ангиллыг Лекц 5-ын хүрээнд авч, өгөгдсөн гурван номоос нийт 45 жишээ сонгон тайлбарлав. Жишээ бүрийг тухайн ангиллын утгатай нь холбон, монгол хэлний хүндлэл, эерүүлэл, ерөөл, талархал зэрэг харилцааны соёлын талаас авч үзэв.",
        first_indent=True,
    )

    current_category = None
    for n, category, example, source, reason in rows:
        if category != current_category:
            current_category = category
            add_paragraph(doc, category, style="Normal", space_after=5).runs[0].bold = True
        add_paragraph(doc, f"{n}. «{example}»", style="Question", space_after=2)
        add_paragraph(doc, reason, style="Answer", first_indent=True, space_after=1)
        add_paragraph(doc, f"Эх сурвалж: {source}.", style="Basis", first_indent=True, space_after=5)

    add_paragraph(doc, "Дүгнэлт", style="Normal", space_after=5).runs[0].bold = True
    add_paragraph(
        doc,
        "Эдгээр жишээнээс харахад хүмүүнлэг үг нь зөвхөн эелдэг хэллэг бус, харин монгол хэлний хүндлэл, цээр, ерөөл, уучлал, талархал, элбэрэл зэрэг харилцааны соёлыг илэрхийлдэг. Гурван номын жишээ нь өөр өөр цаг үе, орчинтой боловч хүнийг зөөлөн, хүндэтгэлтэйгээр хэлэх нийтлэг шинжийг харуулж байна.",
        first_indent=True,
    )

    add_paragraph(doc, "Ашигласан эх сурвалж", style="Normal", space_after=5).runs[0].bold = True
    for source in [
        "• Д. Оюунчимэг. Оройн ганц мод.",
        "• Ф. М. Достоевский. Цагаан шөнө.",
        "• Ц. Дамдинсүрэн хөрвүүлсэн. Монголын нууц товчоо.",
        "• Хэл ярианы соёл. Лекц 5.",
    ]:
        add_paragraph(doc, source, space_after=2)

    OUT.parent.mkdir(parents=True, exist_ok=True)
    doc.save(OUT)
    print(OUT)


if __name__ == "__main__":
    build()
