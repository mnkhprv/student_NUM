from pathlib import Path

from docx import Document
from docx.enum.section import WD_SECTION
from docx.enum.table import WD_ALIGN_VERTICAL, WD_TABLE_ALIGNMENT
from docx.enum.text import WD_ALIGN_PARAGRAPH, WD_BREAK, WD_LINE_SPACING
from docx.oxml import OxmlElement
from docx.oxml.ns import qn
from docx.shared import Cm, Pt, RGBColor


BASE = Path(__file__).resolve().parent
SOURCE = BASE / "os_shell.c"
MAKEFILE = BASE / "Makefile"
OUTPUT = BASE / "lab1_os_report.docx"

BLUE = "0E4F6C"
LIGHT_BLUE = "EAF3F7"
MID_BLUE = "BDD5E1"
GRAY = "666666"
WHITE = "FFFFFF"


def set_cell_shading(cell, fill):
    tc_pr = cell._tc.get_or_add_tcPr()
    shd = tc_pr.find(qn("w:shd"))
    if shd is None:
        shd = OxmlElement("w:shd")
        tc_pr.append(shd)
    shd.set(qn("w:fill"), fill)


def set_cell_margins(cell, top=90, start=110, bottom=90, end=110):
    tc = cell._tc
    tc_pr = tc.get_or_add_tcPr()
    tc_mar = tc_pr.first_child_found_in("w:tcMar")
    if tc_mar is None:
        tc_mar = OxmlElement("w:tcMar")
        tc_pr.append(tc_mar)
    for margin, value in (("top", top), ("start", start), ("bottom", bottom), ("end", end)):
        node = tc_mar.find(qn(f"w:{margin}"))
        if node is None:
            node = OxmlElement(f"w:{margin}")
            tc_mar.append(node)
        node.set(qn("w:w"), str(value))
        node.set(qn("w:type"), "dxa")


def set_repeat_table_header(row):
    tr_pr = row._tr.get_or_add_trPr()
    tbl_header = OxmlElement("w:tblHeader")
    tbl_header.set(qn("w:val"), "true")
    tr_pr.append(tbl_header)


def set_run_font(run, name="Times New Roman", size=11, bold=None, italic=None, color=None):
    run.font.name = name
    run._element.get_or_add_rPr().rFonts.set(qn("w:ascii"), name)
    run._element.get_or_add_rPr().rFonts.set(qn("w:hAnsi"), name)
    run._element.get_or_add_rPr().rFonts.set(qn("w:eastAsia"), name)
    run.font.size = Pt(size)
    if bold is not None:
        run.bold = bold
    if italic is not None:
        run.italic = italic
    if color:
        run.font.color.rgb = RGBColor.from_string(color)


def add_page_number(paragraph):
    paragraph.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = paragraph.add_run()
    fld_begin = OxmlElement("w:fldChar")
    fld_begin.set(qn("w:fldCharType"), "begin")
    instr = OxmlElement("w:instrText")
    instr.set(qn("xml:space"), "preserve")
    instr.text = " PAGE "
    fld_end = OxmlElement("w:fldChar")
    fld_end.set(qn("w:fldCharType"), "end")
    run._r.extend([fld_begin, instr, fld_end])
    set_run_font(run, size=9)


def add_toc(paragraph):
    run = paragraph.add_run()
    begin = OxmlElement("w:fldChar")
    begin.set(qn("w:fldCharType"), "begin")
    begin.set(qn("w:dirty"), "true")
    instr = OxmlElement("w:instrText")
    instr.set(qn("xml:space"), "preserve")
    instr.text = ' TOC \\o "1-3" \\h \\z \\u '
    separate = OxmlElement("w:fldChar")
    separate.set(qn("w:fldCharType"), "separate")
    placeholder = OxmlElement("w:t")
    placeholder.text = "Гарчгийг нээх үед шинэчилнэ."
    end = OxmlElement("w:fldChar")
    end.set(qn("w:fldCharType"), "end")
    run._r.extend([begin, instr, separate, placeholder, end])
    set_run_font(run, size=11)


def add_bottom_cover_line(doc, left_text, right_text):
    table = doc.add_table(rows=1, cols=2)
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = False
    table.columns[0].width = Cm(8)
    table.columns[1].width = Cm(8)
    for cell in table.rows[0].cells:
        set_cell_margins(cell, 0, 0, 0, 0)
    p = table.cell(0, 0).paragraphs[0]
    p.alignment = WD_ALIGN_PARAGRAPH.LEFT
    set_run_font(p.add_run(left_text), size=10.5)
    p = table.cell(0, 1).paragraphs[0]
    p.alignment = WD_ALIGN_PARAGRAPH.RIGHT
    set_run_font(p.add_run(right_text), size=10.5)


def add_centered(doc, text, size=12, bold=False, italic=False, color=None, before=0, after=0):
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.space_before = Pt(before)
    p.paragraph_format.space_after = Pt(after)
    set_run_font(p.add_run(text), size=size, bold=bold, italic=italic, color=color)
    return p


def add_body(doc, text, bold_prefix=None):
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.JUSTIFY
    p.paragraph_format.first_line_indent = Cm(0.75)
    p.paragraph_format.line_spacing_rule = WD_LINE_SPACING.ONE_POINT_FIVE
    p.paragraph_format.space_after = Pt(6)
    if bold_prefix and text.startswith(bold_prefix):
        set_run_font(p.add_run(bold_prefix), bold=True)
        set_run_font(p.add_run(text[len(bold_prefix):]))
    else:
        set_run_font(p.add_run(text))
    return p


def add_bullet(doc, text, level=0):
    p = doc.add_paragraph(style="List Bullet" if level == 0 else "List Bullet 2")
    p.paragraph_format.left_indent = Cm(0.7 + level * 0.5)
    p.paragraph_format.space_after = Pt(3)
    p.paragraph_format.line_spacing = 1.15
    set_run_font(p.add_run(text), size=11)
    return p


def add_numbered(doc, text):
    p = doc.add_paragraph(style="List Number")
    p.paragraph_format.left_indent = Cm(0.7)
    p.paragraph_format.space_after = Pt(3)
    set_run_font(p.add_run(text), size=11)
    return p


def add_heading(doc, text, level=1, page_break=False):
    if page_break:
        doc.add_page_break()
    p = doc.add_paragraph(style=f"Heading {level}")
    p.paragraph_format.keep_with_next = True
    p.paragraph_format.space_before = Pt(10 if level == 1 else 7)
    p.paragraph_format.space_after = Pt(6)
    run = p.add_run(text)
    set_run_font(run, size=18 if level == 1 else (14 if level == 2 else 12), bold=(level == 1), color=BLUE)
    return p


def add_table(doc, headers, rows, widths=None, font_size=10):
    table = doc.add_table(rows=1, cols=len(headers))
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = False
    table.style = "Table Grid"
    header = table.rows[0]
    set_repeat_table_header(header)
    for idx, text in enumerate(headers):
        cell = header.cells[idx]
        set_cell_shading(cell, BLUE)
        set_cell_margins(cell)
        cell.vertical_alignment = WD_ALIGN_VERTICAL.CENTER
        p = cell.paragraphs[0]
        p.alignment = WD_ALIGN_PARAGRAPH.CENTER
        set_run_font(p.add_run(text), size=font_size, bold=True, color=WHITE)
        if widths:
            cell.width = Cm(widths[idx])
    for row_index, values in enumerate(rows):
        cells = table.add_row().cells
        for idx, value in enumerate(values):
            cell = cells[idx]
            set_cell_margins(cell)
            cell.vertical_alignment = WD_ALIGN_VERTICAL.CENTER
            if row_index % 2 == 0:
                set_cell_shading(cell, LIGHT_BLUE)
            p = cell.paragraphs[0]
            p.alignment = WD_ALIGN_PARAGRAPH.LEFT
            p.paragraph_format.space_after = Pt(0)
            set_run_font(p.add_run(str(value)), size=font_size)
            if widths:
                cell.width = Cm(widths[idx])
    doc.add_paragraph().paragraph_format.space_after = Pt(2)
    return table


def add_code_block(doc, text, size=8.2):
    table = doc.add_table(rows=1, cols=1)
    table.style = "Table Grid"
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    cell = table.cell(0, 0)
    set_cell_shading(cell, "F3F5F6")
    set_cell_margins(cell, 90, 120, 90, 120)
    p = cell.paragraphs[0]
    p.paragraph_format.space_after = Pt(0)
    p.paragraph_format.line_spacing = 1.0
    run = p.add_run(text)
    set_run_font(run, name="Liberation Mono", size=size)
    return table


def add_caption(doc, text):
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.space_before = Pt(4)
    p.paragraph_format.space_after = Pt(7)
    set_run_font(p.add_run(text), size=9.5, italic=True, color=GRAY)


def add_cover_one(doc):
    add_centered(doc, "МОНГОЛ УЛСЫН ИХ СУРГУУЛЬ", 13, True, before=12)
    add_centered(doc, "МЭДЭЭЛЛИЙН ТЕХНОЛОГИ, ЭЛЕКТРОНИКИЙН СУРГУУЛЬ", 12, True, before=8)
    add_centered(doc, "МЭДЭЭЛЭЛ, КОМПЬЮТЕРИЙН УХААНЫ ТЭНХИМ", 12, True, before=5)
    add_centered(doc, "Оюутны нэр: ______________________________", 11, before=78)
    add_centered(doc, "C ХЭЛ ДЭЭРХ ЭНГИЙН КОМАНДЫН МӨРИЙН ИНТЕРФЕЙС", 22, False, color="111111", before=44)
    add_centered(doc, "Үйлдлийн системийн онол", 12, before=7)
    add_centered(doc, "Лабораторийн ажил 1", 12, before=7)
    add_centered(doc, "Улаанбаатар хот", 11, before=132)
    add_bottom_cover_line(doc, "Хувилбар 1", "2026 оны 9 сар")
    doc.add_page_break()


def add_cover_two(doc):
    add_centered(doc, "МОНГОЛ УЛСЫН ИХ СУРГУУЛЬ", 13, True, before=12)
    add_centered(doc, "МЭДЭЭЛЛИЙН ТЕХНОЛОГИ, ЭЛЕКТРОНИКИЙН СУРГУУЛЬ", 12, True, before=8)
    add_centered(doc, "МЭДЭЭЛЭЛ, КОМПЬЮТЕРИЙН УХААНЫ ТЭНХИМ", 12, True, before=5)
    add_centered(doc, "C ХЭЛ ДЭЭРХ ЭНГИЙН КОМАНДЫН МӨРИЙН ИНТЕРФЕЙС", 22, before=82)
    add_centered(doc, "Үйлдлийн системийн онол", 12, before=7)
    add_centered(doc, "Лабораторийн ажил 1", 12, before=7)

    table = doc.add_table(rows=2, cols=3)
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = False
    labels = [("Удирдсан:", "________________________", "________________"),
              ("Гүйцэтгэсэн:", "________________________", "Оюутны код: __________")]
    for row, values in zip(table.rows, labels):
        for idx, value in enumerate(values):
            set_cell_margins(row.cells[idx], 40, 50, 40, 50)
            p = row.cells[idx].paragraphs[0]
            p.alignment = WD_ALIGN_PARAGRAPH.LEFT
            set_run_font(p.add_run(value), size=10.5)
    table.rows[0].cells[0].width = Cm(3.0)
    table.rows[0].cells[1].width = Cm(6.0)
    table.rows[0].cells[2].width = Cm(6.5)
    doc.add_paragraph().paragraph_format.space_after = Pt(150)
    add_centered(doc, "Улаанбаатар хот", 11)
    add_centered(doc, "2026 оны 9 сар", 11, before=5)
    doc.add_page_break()


def build_document():
    doc = Document()
    section = doc.sections[0]
    section.page_width = Cm(21)
    section.page_height = Cm(29.7)
    section.top_margin = Cm(2.0)
    section.bottom_margin = Cm(1.8)
    section.left_margin = Cm(2.5)
    section.right_margin = Cm(2.0)
    section.different_first_page_header_footer = True

    normal = doc.styles["Normal"]
    normal.font.name = "Times New Roman"
    normal._element.rPr.rFonts.set(qn("w:ascii"), "Times New Roman")
    normal._element.rPr.rFonts.set(qn("w:hAnsi"), "Times New Roman")
    normal._element.rPr.rFonts.set(qn("w:eastAsia"), "Times New Roman")
    normal.font.size = Pt(11)

    for style_name, size in (("Title", 22), ("Heading 1", 18), ("Heading 2", 14), ("Heading 3", 12)):
        style = doc.styles[style_name]
        style.font.name = "Times New Roman"
        style._element.rPr.rFonts.set(qn("w:ascii"), "Times New Roman")
        style._element.rPr.rFonts.set(qn("w:hAnsi"), "Times New Roman")
        style._element.rPr.rFonts.set(qn("w:eastAsia"), "Times New Roman")
        style.font.size = Pt(size)
        style.font.color.rgb = RGBColor.from_string(BLUE)

    settings = doc.settings._element
    update_fields = OxmlElement("w:updateFields")
    update_fields.set(qn("w:val"), "true")
    settings.append(update_fields)

    header = section.header
    p = header.paragraphs[0]
    p.alignment = WD_ALIGN_PARAGRAPH.RIGHT
    set_run_font(p.add_run("Үйлдлийн системийн онол - Лабораторийн ажил 1"), size=9, italic=True, color=GRAY)
    footer = section.footer
    add_page_number(footer.paragraphs[0])

    add_cover_one(doc)
    add_cover_two(doc)

    add_heading(doc, "ГАРЧИГ", 1)
    toc_p = doc.add_paragraph()
    toc_p.paragraph_format.line_spacing = 1.15
    add_toc(toc_p)
    doc.add_page_break()

    add_heading(doc, "ТОВЧИЛСОН ҮГСИЙН ЖАГСААЛТ", 1)
    add_table(doc, ["Товчлол", "Тайлбар"], [
        ("CLI", "Command Line Interface - командын мөрийн интерфейс"),
        ("OS", "Operating System - үйлдлийн систем"),
        ("POSIX", "Portable Operating System Interface"),
        ("API", "Application Programming Interface"),
        ("EOF", "End of File - оролтын төгсгөл"),
        ("CWD", "Current Working Directory - одоогийн ажлын директор"),
        ("GCC", "GNU Compiler Collection"),
    ], widths=[3.2, 12.8], font_size=10.5)

    add_heading(doc, "НЭР ТОМЬЁОНЫ ТАЙЛБАР", 1, page_break=True)
    add_table(doc, ["Нэр томьёо", "Тайлбар"], [
        ("Shell", "Хэрэглэгчийн командыг уншиж, тайлбарлан тохирох үйлдлийг гүйцэтгэдэг програм."),
        ("Команд", "Тодорхой үйлдэл хийхийг програмд заасан түлхүүр үг."),
        ("Аргумент", "Командтай хамт өгөгдөх файл, директор эсвэл текстийн утга."),
        ("Файл дескриптор", "Үйлдлийн системд нээлттэй файл эсвэл урсгалыг таних бүхэл тоон утга."),
        ("Директор", "Файл болон дэд директоруудыг зохион байгуулан хадгалдаг бүтэц."),
        ("Системийн дуудлага", "Программ үйлдлийн системийн цөмийн үйлчилгээг ашиглах хүсэлт."),
        ("Prompt", "Программ команд хүлээж байгааг илэрхийлэх `os>` тэмдэглэгээ."),
    ], widths=[4.2, 11.8], font_size=10.3)

    add_heading(doc, "1. СУДАЛГААНЫ ЕРӨНХИЙ ҮНДЭСЛЭЛ", 1, page_break=True)
    add_heading(doc, "1.1 Судалгааны үндэслэл", 2)
    add_body(doc, "Командын мөрийн интерфейс нь хэрэглэгчийн бичсэн командыг уншиж, задлан шинжилж, файл болон директорын үйлдлийг гүйцэтгэдэг. Энэ лабораторийн ажил нь бэлэн shell командыг дуудахгүйгээр C хэлний сан болон POSIX функцүүдийг ашиглан энгийн shell програм зохиох дадлага юм.")
    add_body(doc, "Файл үүсгэх, мэдээлэл нэмэх, нэр өөрчлөх, устгах, директор солих зэрэг үйлдэл нь үйлдлийн системийн файл системтэй хэрхэн ажилладгийг ойлгоход тохиромжтой жишээ болно.")
    add_heading(doc, "1.2 Ажлын зорилго, зорилтууд", 2)
    add_body(doc, "Ажлын зорилго нь хэрэглэгчийн командыг уншиж, тохирох C/POSIX функцтэй холбон ажиллуулах жижиг командын мөрийн програм боловсруулахад оршино.")
    for item in [
        "Команд болон аргументыг мөрөөс зөв салгах.",
        "dir, create, input, rename, del, cd командуудыг хэрэгжүүлэх.",
        "Үйлдлийн системийн shell командыг system() болон popen()-оор шууд дуудахгүй байх.",
        "Буруу аргумент, байхгүй файл, давхар файл зэрэг энгийн алдааг мэдээлэх.",
        "Программыг GCC ашиглан хөрвүүлж, үндсэн үйлдлүүдийг турших.",
    ]:
        add_bullet(doc, item)
    add_heading(doc, "1.3 Судалгааны объект, предмет", 2)
    add_body(doc, "Судалгааны объект нь командын мөрийн интерфейсийн ажиллагаа. Судалгааны предмет нь команд задлалт, файл системийн үйлдэл, одоогийн ажлын директор болон алдаа боловсруулах арга юм.")
    add_heading(doc, "1.4 Судалгааны арга зүй", 2)
    add_body(doc, "Даалгаврын шаардлагыг задлан шинжилж, команд бүрийг тусдаа функцээр хэрэгжүүлсэн. Дараа нь програмыг анхааруулгатайгаар хөрвүүлж, зөв болон буруу оролтын туршилтаар үр дүнг шалгав.")

    add_heading(doc, "2. SHELL ПРОГРАМЫН ОНОЛ БА ШААРДЛАГА", 1, page_break=True)
    add_heading(doc, "2.1 Shell болон CLI-ийн ойлголт", 2)
    add_body(doc, "Shell нь хэрэглэгч ба үйлдлийн системийн хооронд командын түвшний харилцаа үүсгэдэг. Энэ ажлын os_shell програм нь жинхэнэ системийн shell-ийн бүх боломжийг агуулахгүй боловч унших, задлах, гүйцэтгэх үндсэн мөчлөгийг харуулна.")
    add_heading(doc, "2.2 Даалгаврын үндсэн шаардлага", 2)
    add_table(doc, ["№", "Команд", "Үйлдэл", "Жишээ"], [
        ("1", "dir", "Одоогийн директорын агуулгыг харуулах", "dir"),
        ("2", "create", "Шинэ хоосон файл үүсгэх", "create text.txt"),
        ("3", "input", "Файлд текст мөр нэмэх", "input text.txt sample data"),
        ("4", "rename", "Файлын нэр өөрчлөх", "rename text.txt file.txt"),
        ("5", "del", "Файл устгах", "del file.txt"),
        ("6", "cd", "Ажлын директорыг өөрчлөх", "cd .."),
    ], widths=[1.0, 2.5, 7.5, 5.0], font_size=9.5)
    add_body(doc, "Нэмэлтээр pwd, help, exit команд оруулсан. Эдгээр нь одоогийн замыг харах, тусламж авах, программыг зөв дуусгахад ашиглагдана.")
    add_heading(doc, "2.3 Ашигласан орчин", 2)
    add_table(doc, ["Хэсэг", "Сонголт"], [
        ("Үйлдлийн систем", "Linux"),
        ("Програмчлалын хэл", "C11"),
        ("Хөрвүүлэгч", "GCC"),
        ("Сан/интерфейс", "C стандарт сан, POSIX"),
        ("Хөрвүүлэх сонголт", "-Wall -Wextra -std=c11"),
        ("Файлын бүтэц", "os_shell.c, Makefile"),
    ], widths=[5.0, 11.0], font_size=10)
    add_heading(doc, "2.4 Ашигласан функцүүд", 2)
    add_table(doc, ["Функц", "Зориулалт"], [
        ("fgets(), strtok(), strcmp()", "Оролт унших, токен салгах, команд таних"),
        ("opendir(), readdir(), closedir()", "Директор нээх, бичлэгүүдийг унших, хаах"),
        ("stat()", "Бичлэг директор мөн эсэхийг шалгах"),
        ("fopen(), fprintf(), fclose()", "Файл үүсгэх болон текст нэмэх"),
        ("rename(), unlink()", "Нэр өөрчлөх болон файл устгах"),
        ("chdir(), getcwd()", "Ажлын директорыг солих болон харах"),
        ("perror()", "Системээс ирсэн алдааны тайлбарыг хэвлэх"),
    ], widths=[6.0, 10.0], font_size=9.6)

    add_heading(doc, "3. ПРОГРАММЫН ШИНЖИЛГЭЭ, ЗАГВАРЧЛАЛ", 1, page_break=True)
    add_body(doc, "Программыг үндсэн давталт, команд задлагч болон файл системийн үйлдлийн функцүүд гэсэн гурван хэсгээр авч үзэв.")
    add_heading(doc, "3.1 Ерөнхий бүтэц", 2)
    add_code_block(doc,
        "+------------------+\n"
        "| Хэрэглэгчийн мөр  |\n"
        "+--------+---------+\n"
        "         | fgets()\n"
        "         v\n"
        "+------------------+\n"
        "| Команд ба аргумент|\n"
        "| strtok()         |\n"
        "+--------+---------+\n"
        "         | strcmp()\n"
        "         v\n"
        "+---------------------------+\n"
        "| Тохирох command_* функц   |\n"
        "+-------------+-------------+\n"
        "              |\n"
        "              v\n"
        "   Үр дүн эсвэл алдааны мэдээлэл",
        size=9.2)
    add_caption(doc, "Зураг 1. os_shell програмын ерөнхий өгөгдлийн урсгал")
    add_heading(doc, "3.2 Үндсэн алгоритм", 2)
    for item in [
        "Программ эхлэхэд тусламжийн богино мэдээлэл хэвлэнэ.",
        "os> prompt харуулж, fgets() функцээр нэг мөр уншина.",
        "Мөрийн төгсгөлийн шинэ мөрийг авч, strtok() функцээр команд ба аргументыг салгана.",
        "strcmp() ашиглан командын нэрийг шалгаж, тохирох command_* функцийг дуудна.",
        "Үр дүн эсвэл алдааны мэдээллийг хэвлээд дараагийн командыг хүлээнэ.",
        "exit эсвэл EOF орж ирэхэд давталтыг дуусгана.",
    ]:
        add_numbered(doc, item)
    add_heading(doc, "3.3 Функцийн зохион байгуулалт", 2)
    add_table(doc, ["Функц", "Оролт", "Гаралт/нөлөө"], [
        ("remove_newline", "Оролтын мөр", "Төгсгөлийн \\n тэмдэгтийг арилгана"),
        ("skip_spaces", "Текстийн заагч", "Эхний хоосон зайг алгассан заагч"),
        ("command_dir", "Оролтгүй", "Директорын жагсаалт"),
        ("command_create", "Файлын нэр", "Шинэ файл"),
        ("command_input", "Файлын нэр, өгөгдөл", "Файлд нэмэгдсэн мөр"),
        ("command_rename", "Хуучин ба шинэ нэр", "Нэр өөрчлөгдөнө"),
        ("command_delete", "Файлын нэр", "Файл устна"),
        ("command_cd", "Директорын зам", "CWD өөрчлөгдөнө"),
        ("command_pwd", "Оролтгүй", "Одоогийн зам"),
        ("print_help", "Оролтгүй", "Командын заавар"),
    ], widths=[4.5, 5.0, 6.5], font_size=9.3)

    add_heading(doc, "4. ХЭРЭГЖҮҮЛЭЛТ", 1, page_break=True)
    add_heading(doc, "4.1 Команд унших ба задлах", 2)
    add_body(doc, "main() функц дотор while давталт ажиллана. fgets() нэг мөрийг line массивт уншиж, strtok() эхний токеныг команд болгон салгана. input командын үлдсэн хэсгийг бүхэлд нь өгөгдөл болгон ашигладаг тул нэгээс олон үг бичих боломжтой.")
    add_code_block(doc,
        'remove_newline(line);\n'
        'command = strtok(line, " \\t");\n'
        'if (command == NULL) {\n'
        '    continue;\n'
        '}')
    add_caption(doc, "Код 1. Оролтын мөрөөс команд салгах хэсэг")
    add_heading(doc, "4.2 Файл болон директорын командууд", 2)
    add_body(doc, "dir команд opendir() болон readdir()-ээр одоогийн директорын бичлэг бүрийг уншина. stat() функцээр директор эсэхийг тодорхойлж, дэд директорт [DIR] тэмдэглэгээ тавина.")
    add_body(doc, "create команд fopen(filename, \"wx\") горим ашигладаг. x тэмдэг нь файл өмнө нь байвал дарж бичихээс хамгаална. input команд a горимоор мөр нэмнэ. rename(), unlink(), chdir() функцүүд нь нэр өөрчлөх, файл устгах, директор солих үйлдлийг шууд гүйцэтгэнэ.")
    add_heading(doc, "4.3 Алдаа боловсруулах", 2)
    add_bullet(doc, "Шаардлагатай аргумент дутуу бол командын зөв хэрэглээг хэвлэнэ.")
    add_bullet(doc, "Файл өмнө нь байвал create команд давхар үүсгэхгүй.")
    add_bullet(doc, "Системийн функц амжилтгүй бол perror() бодит шалтгааныг харуулна.")
    add_bullet(doc, "del команд unlink() ашигладаг тул директорыг файл мэт устгахгүй.")
    add_heading(doc, "4.4 Хөрвүүлэх ба ажиллуулах", 2)
    add_body(doc, "Лабораторийн хавтсанд дараах командыг ажиллуулна.")
    add_code_block(doc, "make\n./os_shell")
    add_body(doc, "Программыг exit командаар дуусгана. Хөрвүүлсэн executable файлыг цэвэрлэхдээ make clean ашиглана.")

    add_heading(doc, "5. ТУРШИЛТ БА ҮР ДҮН", 1, page_break=True)
    add_heading(doc, "5.1 Туршилтын арга", 2)
    add_body(doc, "Программыг GCC-ийн -Wall -Wextra анхааруулгатайгаар хөрвүүлэв. Дараа нь түр файл ашиглан команд бүрийн хэвийн ажиллагаа болон зарим алдааны нөхцөлийг шалгав.")
    add_heading(doc, "5.2 Туршилтын үр дүн", 2)
    add_table(doc, ["№", "Туршилт", "Хүлээгдсэн үр дүн", "Төлөв"], [
        ("1", "help", "Командын жагсаалт харагдана", "Амжилттай"),
        ("2", "create text.txt", "Хоосон файл үүснэ", "Амжилттай"),
        ("3", "input text.txt sample data", "Файлд мөр нэмэгдэнэ", "Амжилттай"),
        ("4", "rename text.txt file.txt", "Нэр өөрчлөгдөнө", "Амжилттай"),
        ("5", "dir", "file.txt жагсаалтад харагдана", "Амжилттай"),
        ("6", "pwd", "Одоогийн зам хэвлэгдэнэ", "Амжилттай"),
        ("7", "cd ..", "Ажлын директор солигдоно", "Амжилттай"),
        ("8", "del file.txt", "Файл устна", "Амжилттай"),
        ("9", "create давхар файл", "Давхар файл үүсэхгүй", "Амжилттай"),
        ("10", "үл мэдэгдэх команд", "Unknown command мэдээлэл", "Амжилттай"),
    ], widths=[0.8, 4.0, 7.2, 4.0], font_size=8.9)
    add_heading(doc, "5.3 Ажиллагааны жишээ", 2)
    add_code_block(doc,
        "os> create text.txt\n"
        "Created: text.txt\n"
        "os> input text.txt sample data\n"
        "Data written to: text.txt\n"
        "os> rename text.txt file.txt\n"
        "Renamed: text.txt -> file.txt\n"
        "os> del file.txt\n"
        "Deleted: file.txt\n"
        "os> exit",
        size=8.8)
    add_caption(doc, "Зураг 2. Үндсэн командуудын туршилтын жишээ")
    add_heading(doc, "5.4 Хязгаарлалт ба сайжруулах боломж", 2)
    add_body(doc, "Одоогийн хувилбар нь нэг мөрөөр нэг команд ажиллуулна. Файлын нэр эсвэл замд хоосон зай байвал хашилтыг тусгайлан боловсруулахгүй. Мөн pipe, redirect, background process зэрэг жинхэнэ shell-ийн боломжууд ороогүй.")
    add_body(doc, "Цаашид давхар хашилттай аргумент, командын түүх, автоматаар гүйцээх, файл хуулах болон зөөх команд нэмж болно.")

    add_heading(doc, "ДҮГНЭЛТ", 1, page_break=True)
    add_body(doc, "Энэ лабораторийн ажлаар командын мөрийн програм хэрэглэгчийн мөрийг уншиж, команд ба аргументыг салгаад тохирох функцтэй холбодгийг ойлголоо. Файл болон директортой ажиллах зургаан үндсэн командыг C хэл, POSIX функцээр хэрэгжүүлж, үйлдлийн системийн бэлэн командыг код дотор шууд дуудаагүй.")
    add_body(doc, "Туршилтаар файл үүсгэх, өгөгдөл нэмэх, нэр өөрчлөх, жагсаах, устгах, директор солих үйлдлүүд зөв ажилласан. Мөн аргумент дутуу, файл байхгүй, файл давхардсан нөхцөлд ойлгомжтой алдааны мэдээлэл харуулдаг болсон.")

    add_heading(doc, "НОМ ЗҮЙ", 1)
    refs = [
        "Kerrisk, M. (2010). The Linux Programming Interface. No Starch Press.",
        "IEEE and The Open Group. POSIX.1-2017 системийн интерфейсийн тайлбар.",
        "GNU Project. The GNU C Library Reference Manual.",
        "Үйлдлийн системийн онол хичээлийн лабораторийн ажил 1-ийн удирдамж.",
    ]
    for ref in refs:
        add_numbered(doc, ref)

    add_heading(doc, "ХАВСРАЛТ А. os_shell.c ЭХ КОД", 1, page_break=True)
    add_body(doc, "Программын бүтэн эх кодыг мөрийн дугаартайгаар хавсаргав.")
    source_lines = SOURCE.read_text(encoding="utf-8").splitlines()
    numbered_source = "\n".join(f"{idx:>3}  {line}" for idx, line in enumerate(source_lines, 1))
    add_code_block(doc, numbered_source, size=7.1)

    add_heading(doc, "ХАВСРАЛТ Б. MAKEFILE", 1, page_break=True)
    add_body(doc, "Makefile нь программыг нэг командаар хөрвүүлэх болон executable файлыг цэвэрлэх дүрэмтэй.")
    make_lines = MAKEFILE.read_text(encoding="utf-8").splitlines()
    numbered_make = "\n".join(f"{idx:>2}  {line}" for idx, line in enumerate(make_lines, 1))
    add_code_block(doc, numbered_make, size=8.5)

    props = doc.core_properties
    props.title = "Лабораторийн ажил 1 - C хэл дээрх энгийн командын мөрийн интерфейс"
    props.subject = "Үйлдлийн системийн онол"
    props.author = "МУИС-ийн оюутан"
    props.comments = "os_shell.c лабораторийн тайлан"

    doc.save(OUTPUT)
    print(OUTPUT)


if __name__ == "__main__":
    build_document()
