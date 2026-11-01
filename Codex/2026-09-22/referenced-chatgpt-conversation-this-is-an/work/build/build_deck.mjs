import fs from "node:fs/promises";
import path from "node:path";
import { pathToFileURL } from "node:url";
import { Presentation, PresentationFile } from "@oai/artifact-tool";

const workspaceDir = "/home/lunatic/Documents/Codex/2026-09-22/referenced-chatgpt-conversation-this-is-an";
const SKILL_DIR = "/home/lunatic/.codex/plugins/cache/openai-primary-runtime/presentations/26.905.11957/skills/presentations";
const RUNTIME_PYTHON = "/home/lunatic/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3";
const buildDir = path.join(workspaceDir, "work/build");
const finalPath = path.join(workspaceDir, "outputs/Monkhpurev_Internship_Defense_BurenScore.pptx");

const {
  finalizePresentation,
  makeNativeBulletParagraphs,
} = await import(pathToFileURL(path.join(SKILL_DIR, "container_tools/artifact_tool_utils.mjs")).href);

await fs.mkdir(buildDir, { recursive: true });
await fs.mkdir(path.dirname(finalPath), { recursive: true });

const FONT = "Noto Sans";
const MONO = "Noto Sans Mono";
const C = {
  navy: "#10182E",
  navy2: "#1C2942",
  green: "#00A376",
  mint: "#DDF7EE",
  pale: "#F5F7FA",
  white: "#FFFFFF",
  text: "#172033",
  muted: "#5E6B80",
  line: "#DCE3EA",
  amber: "#F59E0B",
  amberPale: "#FFF4D6",
  blue: "#247BA0",
  red: "#D45555",
};

const asset = (name) => path.join(workspaceDir, name);
const imgCompany = await fs.readFile(asset("work/source/screenshot_1.png"));
const imgMetrics = await fs.readFile(asset("work/source/screenshot_3.png"));
const imgCalculator = await fs.readFile(asset("work/extracted/report-001.png"));
const imgUpload = await fs.readFile(asset("work/extracted/report-002.png"));

const p = Presentation.create({ slideSize: { width: 1280, height: 720 } });

function addText(slide, text, x, y, w, h, opts = {}) {
  const s = slide.shapes.add({
    geometry: "textbox",
    position: { left: x, top: y, width: w, height: h },
    fill: opts.fill ?? "none",
    line: opts.line ?? { fill: "none", width: 0 },
    borderRadius: opts.borderRadius,
  });
  s.text = text;
  s.text.style = {
    typeface: opts.typeface ?? FONT,
    fontSize: opts.fontSize ?? 24,
    bold: opts.bold ?? false,
    italic: opts.italic ?? false,
    color: opts.color ?? C.text,
    alignment: opts.alignment ?? "left",
    verticalAlignment: opts.verticalAlignment ?? "top",
    autoFit: opts.autoFit ?? "none",
    wrap: "square",
    insets: opts.insets ?? { left: 0, right: 0, top: 0, bottom: 0 },
  };
  return s;
}

function addRect(slide, x, y, w, h, fill, opts = {}) {
  return slide.shapes.add({
    geometry: opts.geometry ?? "roundRect",
    position: { left: x, top: y, width: w, height: h },
    fill,
    line: opts.line ?? { style: "solid", fill: opts.lineColor ?? fill, width: opts.lineWidth ?? 1 },
    borderRadius: opts.borderRadius ?? "rounded-xl",
    shadow: opts.shadow,
  });
}

function addPill(slide, text, x, y, w, fill = C.mint, color = C.green) {
  const s = addRect(slide, x, y, w, 32, fill, { borderRadius: "rounded-full", lineColor: fill });
  s.text = text;
  s.text.style = {
    typeface: FONT, fontSize: 14, bold: true, color,
    alignment: "center", verticalAlignment: "middle", autoFit: "none",
    insets: { left: 8, right: 8, top: 1, bottom: 1 },
  };
  return s;
}

function addTitle(slide, title, section, number, dark = false) {
  const titleColor = dark ? C.white : C.navy;
  const mutedColor = dark ? "#BFC9D8" : C.muted;
  addText(slide, section.toUpperCase(), 64, 36, 420, 24, { fontSize: 13, bold: true, color: dark ? "#5FE0BB" : C.green });
  addText(slide, title, 64, 65, 1080, 62, { fontSize: 36, bold: true, color: titleColor });
  addText(slide, String(number).padStart(2, "0"), 1170, 42, 46, 24, { fontSize: 15, bold: true, color: mutedColor, alignment: "right" });
}

function addFooter(slide, source, number, dark = false) {
  const color = dark ? "#AAB5C7" : "#78859A";
  addText(slide, source, 64, 678, 1040, 16, { fontSize: 10.5, color });
  addText(slide, `${number}/12`, 1145, 678, 70, 16, { fontSize: 10.5, color, alignment: "right" });
}

function addBullets(slide, items, x, y, w, h, opts = {}) {
  const s = addText(slide, "", x, y, w, h, { fontSize: opts.fontSize ?? 22, color: opts.color ?? C.text });
  s.text = makeNativeBulletParagraphs(items, {
    marginLeftPoints: opts.marginLeftPoints ?? 18,
    hangingPoints: opts.hangingPoints ?? 9,
    spaceAfterPoints: opts.spaceAfterPoints ?? 9,
  });
  s.text.style = {
    typeface: FONT,
    fontSize: opts.fontSize ?? 22,
    color: opts.color ?? C.text,
    autoFit: "none",
    verticalAlignment: "top",
    insets: { left: 0, right: 0, top: 0, bottom: 0 },
  };
  return s;
}

function addImageCard(slide, bytes, x, y, w, h, opts = {}) {
  addRect(slide, x - 8, y - 8, w + 16, h + 16, C.white, {
    lineColor: C.line, shadow: "shadow-md", borderRadius: "rounded-2xl",
  });
  return slide.images.add({
    blob: bytes,
    contentType: "image/png",
    alt: opts.alt ?? "Тайлангийн дүрслэл",
    fit: opts.fit ?? "cover",
    crop: opts.crop,
    geometry: "roundRect",
    borderRadius: "rounded-xl",
    position: { left: x, top: y, width: w, height: h },
  });
}

function setNotes(slide, text) {
  slide.speakerNotes.textFrame.setText(text);
  slide.speakerNotes.setVisible(true);
}

// 1. Cover
{
  const s = p.slides.add();
  s.background.fill = C.navy;
  addRect(s, 64, 88, 8, 452, C.green, { geometry: "rect", borderRadius: 0, lineColor: C.green });
  addPill(s, "ҮЙЛДВЭРЛЭЛИЙН ДАДЛАГЫН ХАМГААЛАЛТ", 96, 88, 330, "#183B39", "#5FE0BB");
  addText(s, "BurenScore лавлагаа\nболовсруулах урсгал", 96, 154, 920, 150, { fontSize: 52, bold: true, color: C.white });
  addText(s, "InnoScore платформын ЗМС модульд хийсэн фүлл-стак хөгжүүлэлт", 99, 330, 900, 46, { fontSize: 24, color: "#D7DFEA" });
  addText(s, "Наранбаатарын Мөнхпүрэв  ·  23B1NUM0114", 99, 500, 620, 30, { fontSize: 20, bold: true, color: C.white });
  addText(s, "AIM Innovestment  ·  Технологийн алба  ·  2026.06.02–06.29", 99, 544, 760, 24, { fontSize: 16, color: "#AAB5C7" });
  addText(s, "МУИС · МТЭС · Программ хангамж", 99, 634, 560, 20, { fontSize: 13, color: "#8794A8" });
  addText(s, "01", 1158, 635, 58, 24, { fontSize: 16, bold: true, color: "#5FE0BB", alignment: "right" });
  setNotes(s, `[20 секунд]\nСайн байна уу. Намайг Наранбаатарын Мөнхпүрэв гэдэг. Би AIM Innovestment-ийн Технологийн албанд 2026 оны 6 дугаар сарын 2-ноос 29-ний хооронд фүлл-стак хөгжүүлэгчийн чиглэлээр дадлага хийсэн. Өнөөдөр InnoScore платформын Зээлийн мэдээллийн сангийн модульд BurenScore цогц лавлагаа боловсруулах шинэ урсгал нэмэхэд оруулсан хувь нэмрээ танилцуулна.\n\nЭх сурвалж: Үйлдвэрлэлийн дадлагын тайлан, нүүр хуудас болон Удиртгал.`);
}

// 2. Context and objective
{
  const s = p.slides.add();
  s.background.fill = C.pale;
  addTitle(s, "Дадлагын орчин ба зорилго", "Суурь нөхцөл", 2);
  addPill(s, "4 ДОЛОО ХОНОГ", 64, 148, 150);
  addText(s, "AIM Innovestment", 64, 200, 470, 34, { fontSize: 26, bold: true, color: C.navy });
  addText(s, "Технологийн алба · Фүлл-стак хөгжүүлэгч", 64, 242, 480, 28, { fontSize: 18, color: C.muted });
  addBullets(s, [
    "Бодит кодын сангийн бэкэнд–фронтэнд урсгалыг ойлгох",
    "Өмнөх SainScore шийдлийг судалж, шинэ форматыг өргөтгөх",
    "Өөрчлөлтийг локал болон стэйжинг орчинд шалгах",
  ], 64, 304, 500, 220, { fontSize: 21, spaceAfterPoints: 10 });
  addRect(s, 64, 550, 500, 74, C.white, { lineColor: C.line, borderRadius: "rounded-xl" });
  addText(s, "Үндсэн зорилго", 84, 566, 130, 20, { fontSize: 13, bold: true, color: C.green });
  addText(s, "BurenScore цогц лавлагааг ЗМС-ийн өмнөх урсгалтай зөв холбох", 84, 591, 455, 26, { fontSize: 18, bold: true, color: C.navy });
  addImageCard(s, imgCompany, 650, 190, 566, 300, {
    alt: "InnoScore-ийн санхүүгийн шинжилгээний танилцуулгын зураг",
    fit: "contain",
  });
  addRect(s, 650, 525, 566, 96, C.mint, { lineColor: "#B5EAD9", borderRadius: "rounded-xl" });
  addText(s, "Платформын чиглэл", 674, 543, 190, 22, { fontSize: 14, bold: true, color: C.green });
  addText(s, "Орлого тодорхойлох, эрсдэлийг үнэлэх, зээлийн шийдвэрийг дэмжих", 674, 573, 510, 36, { fontSize: 17, bold: true, color: C.navy });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 1–4; хэрэглэгчийн өгсөн InnoScore танилцуулгын зураг", 2);
  setNotes(s, `[45 секунд]\nДадлагаа AIM Innovestment-ийн Технологийн албанд, CTO Г. Балжиннямын удирдлага дор хийсэн. Ажлын чиглэл фүлл-стак хөгжүүлэлт байсан бөгөөд InnoScore-ийн ЗМС модуль дээр төвлөрсөн. Дадлагын зорилго нь шинэ системийг анхнаас нь бүтээх бус, үйлдвэрлэлийн орчинд ашиглагдаж байсан кодын санг ойлгож, өмнөх шийдлийг хариуцлагатай өргөтгөх байв. Миний гол даалгавар BurenScore цогц лавлагааны өгөгдлийг уншиж, хадгалж, хэрэглэгчийн дэлгэцэд зөв харуулах урсгал нэмэх байсан.\n\nЭх сурвалж: Үйлдвэрлэлийн дадлагын тайлан, Удиртгал, х. 1–2; Байгууллагын танилцуулга, х. 3–4.`);
}

// 3. Problem and scope
{
  const s = p.slides.add();
  s.background.fill = C.white;
  addTitle(s, "Асуудал ба ажлын хил", "Даалгаврын тодорхойлолт", 3);
  const xs = [64, 430, 796];
  const headers = ["Өмнөх төлөв", "Шинэ асуудал", "Миний оролцоо"];
  const nums = ["01", "02", "03"];
  const body = [
    "SainScore парсер болон ЗМС-ийн үндсэн урсгал өмнө нь ажиллаж байсан.",
    "BurenScore нь гарчиг, хэсгийн дараалал, хүснэгтийн байрлалаар ялгаатай байв.",
    "Таних дүрэм, тусдаа парсер, өгөгдлийн холбоос болон UI өөрчлөлт хийсэн.",
  ];
  for (let i = 0; i < 3; i++) {
    addText(s, nums[i], xs[i], 170, 70, 48, { fontSize: 34, bold: true, color: i === 2 ? C.green : "#A5B0C0" });
    addText(s, headers[i], xs[i], 228, 300, 32, { fontSize: 25, bold: true, color: C.navy });
    addText(s, body[i], xs[i], 278, 300, 118, { fontSize: 19, color: C.muted });
    if (i < 2) {
      s.shapes.add({ geometry: "line", position: { left: xs[i] + 318, top: 180, width: 0, height: 230 }, fill: "none", line: { style: "solid", fill: C.line, width: 1.2 } });
    }
  }
  addRect(s, 64, 445, 1098, 140, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  addText(s, "Хамрах хүрээний зааг", 88, 465, 260, 24, { fontSize: 15, bold: true, color: "#5FE0BB" });
  addText(s, "Платформыг бүхэлд нь болон ЗМС модулийг анхнаас нь бүтээгээгүй.\nӨмнөх системийн зохион байгуулалтыг судалж, BurenScore боловсруулах замыг холбосон.", 88, 500, 1010, 66, { fontSize: 20, bold: false, color: C.white });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 1–2, 12, 18", 3);
  setNotes(s, `[50 секунд]\nЭнд ажлын хилээ тодруулъя. Дадлага эхлэх үед SainScore лавлагааны парсер болон ЗМС-ийн үндсэн урсгал аль хэдийн ажиллаж байсан. Харин BurenScore цогц лавлагаа нь өөр гарчиг, өөр хэсгийн дараалал, олон хуудсанд үргэлжлэх хүснэгттэй тул өмнөх парсерээр шууд боловсруулах боломжгүй байлаа. Миний оролцоо нь форматыг таних дүрэм тогтоох, тусдаа парсер хөгжүүлэх, хадгалалтын холбоос болон фронтэнд харуулах хэсэгт шаардлагатай өөрчлөлт хийхэд төвлөрсөн. Иймээс дараагийн слайдуудад зөвхөн өөрийн хийсэн болон хамтран гүйцэтгэсэн хэсгийг ялгаж тайлбарлана.\n\nЭх сурвалж: Дадлагын тайлан, х. 1–2, 12, 18.`);
}

// 4. Format study
{
  const s = p.slides.add();
  s.background.fill = C.pale;
  addTitle(s, "Форматын судалгаа ба таних дүрэм", "PDF форматын ялгаа", 4);
  addText(s, "Судалсан хувилбар", 64, 156, 340, 26, { fontSize: 15, bold: true, color: C.muted });
  const rows = [
    ["BurenScore цогц", "Дадлагын парсераар дэмжсэн", C.green],
    ["BurenScore орлогын төлөв", "Нэмэлт шалгалт шаардлагатай", C.amber],
    ["BurenScore e-Mongolia", "Дадлагын дараа нэмэгдсэн", C.blue],
    ["BurenScore KUB", "Дэмжигдээгүй", C.red],
    ["SainScore хувилбарууд", "Өмнөх парсераар дэмжсэн", C.muted],
  ];
  rows.forEach((r, i) => {
    const y = 194 + i * 67;
    addRect(s, 64, y, 548, 54, C.white, { lineColor: C.line, borderRadius: "rounded-lg" });
    addRect(s, 78, y + 17, 10, 20, r[2], { geometry: "rect", borderRadius: 0, lineColor: r[2] });
    addText(s, r[0], 104, y + 10, 236, 34, { fontSize: 18, bold: true, color: C.navy, verticalAlignment: "middle" });
    addText(s, r[1], 342, y + 10, 248, 34, { fontSize: 15, color: C.muted, alignment: "right", verticalAlignment: "middle" });
  });
  addText(s, "BurenScore цогц лавлагааны гурван тэмдэг", 680, 156, 520, 26, { fontSize: 15, bold: true, color: C.muted });
  addRect(s, 680, 194, 536, 265, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  addText(s, "1  БҮРЭН ОНООНЫ ЦОГЦ ЛАВЛАГАА\n\n2  Зээлийн мэдээллийн лавлагаа\n\n3  Лавлагааны хүчинтэй хугацаа", 710, 226, 476, 190, { fontSize: 19, typeface: MONO, color: C.white });
  addRect(s, 680, 490, 536, 104, C.mint, { lineColor: "#B5EAD9", borderRadius: "rounded-xl" });
  addText(s, "Олон тэмдгийг хамтад нь шалгаснаар ижил зориулалттай боловч өөр бүтэцтэй PDF-д буруу парсер сонгох эрсдэл буурсан.", 706, 512, 488, 64, { fontSize: 18, bold: true, color: C.navy });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 6–8", 4);
  setNotes(s, `[55 секунд]\nЭхлээд BurenScore болон SainScore-ийн жишээ файлуудыг харьцуулсан. Ижил зориулалттай лавлагаанууд харагдах байдлаараа төстэй боловч PDF доторх текстийн байрлал, баганын тоо, мөр тасрах хэлбэр нь ялгаатай байсан. BurenScore-ийн цогц, орлогын төлөв, e-Mongolia, KUB хувилбаруудыг болон SainScore-ийн хэд хэдэн форматыг судалсан. Цогц лавлагааг зөвхөн нэг ерөнхий үгээр танихын оронд эхний хуудсан дээрх гурван тодорхой тэмдгийг зэрэг шалгасан. Энэ нь KUB болон e-Mongolia зэрэг өөр хувилбарт буруу парсер ажиллах эрсдэлийг багасгасан.\n\nЭх сурвалж: Дадлагын тайлан, Зээлийн лавлагааны форматын судалгаа, х. 6–8.`);
}

// 5. Processing flow
{
  const s = p.slides.add();
  s.background.fill = C.white;
  addTitle(s, "Зээлийн лавлагаа боловсруулах урсгал", "Архитектурын холбоос", 5);
  const labels = ["PDF файл", "Тэмдэг шалгах", "Парсер сонгох", "Хэсэг задлах", "Өгөгдөл хадгалах", "ЗМС дэлгэц"];
  const sub = ["Эхний хуудас", "3 үндсэн шинж", "Factory", "Цэвэрлэгээ", "ORM + API", "React хүснэгт"];
  const boxes = [];
  labels.forEach((t, i) => {
    const x = 58 + i * 204;
    const b = addRect(s, x, 200, 166, 126, i === 2 ? C.mint : C.pale, { lineColor: i === 2 ? "#9DDFC9" : C.line, borderRadius: "rounded-xl" });
    addText(s, String(i + 1).padStart(2, "0"), x + 16, 214, 40, 18, { fontSize: 12, bold: true, color: i === 2 ? C.green : "#8894A6" });
    addText(s, t, x + 14, 240, 138, 48, { fontSize: 16, bold: true, color: C.navy, alignment: "center", verticalAlignment: "middle" });
    addText(s, sub[i], x + 14, 294, 138, 18, { fontSize: 12.5, color: C.muted, alignment: "center" });
    boxes.push(b);
    if (i > 0) {
      s.shapes.connect(boxes[i - 1], b, { kind: "straight", fromSide: "right", toSide: "left", line: { style: "solid", fill: C.green, width: 2 }, tail: { type: "triangle", width: "sm", length: "sm" } });
    }
  });
  addRect(s, 64, 382, 1152, 190, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  addText(s, "Технологийн үүрэг", 88, 405, 210, 24, { fontSize: 15, bold: true, color: "#5FE0BB" });
  const tech = [
    ["pdfplumber", "текст, хүснэгт, хуудасны хэсэг"],
    ["Django / DRF", "API урсгал ба сарын төлөлт"],
    ["Django ORM", "харилцагч–лавлагаа–зээлийн мөр"],
    ["React / Next.js", "хүснэгтийн төлөв ба файл оруулах"],
  ];
  tech.forEach((r, i) => {
    const x = 88 + i * 276;
    addText(s, r[0], x, 454, 246, 26, { fontSize: 19, bold: true, color: C.white });
    addText(s, r[1], x, 492, 244, 54, { fontSize: 15, color: "#BFC9D8" });
  });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 11–13", 5);
  setNotes(s, `[50 секунд]\nШийдлийн ерөнхий урсгал зургаан үе шаттай. Систем PDF-ийн эхний хуудсыг уншаад формат таних тэмдгүүдийг шалгана. Дараа нь factory тохирох парсерийг сонгож, тухайн парсер шаардлагатай хэсэг болон хүснэгтийг задлан цэвэрлэнэ. Гарсан өгөгдлийг ORM холбоосоор хадгалж, API-аар фронтэнд дамжуулан ЗМС хүснэгтэд харуулна. Энд нэг технологийг бүх ажилд ашиглаагүй. pdfplumber PDF бүтэцтэй, Django ба DRF серверийн урсгалтай, ORM өгөгдлийн холбоостой, React ба Next.js хэрэглэгчийн төлөвтэй ажилласан.\n\nЭх сурвалж: Дадлагын тайлан, Ашигласан технологи х. 11; Хийсэн ажлын дэлгэрэнгүй х. 12–13.`);
}

// 6. Parser implementation
{
  const s = p.slides.add();
  s.background.fill = C.pale;
  addTitle(s, "BurenScore парсерийн хэрэгжүүлэлт", "Олон хуудаст PDF", 6);
  addText(s, "1. Хэсгийг тогтоох", 64, 166, 500, 32, { fontSize: 24, bold: true, color: C.navy });
  addText(s, "Хүснэгтийн эхлэл, төгсгөлийн текстийг хайж шаардлагатай хуудасны хэсгийг сонгов.", 64, 210, 500, 70, { fontSize: 19, color: C.muted });
  addText(s, "2. Мөрийг цэвэрлэх", 64, 314, 500, 32, { fontSize: 24, bold: true, color: C.navy });
  addBullets(s, ["None утгыг нэг хэлбэрт оруулах", "Шинэ мөрийг зайгаар солих", "Дугаартай бодит мөрийг ялгах"], 64, 356, 500, 150, { fontSize: 18, spaceAfterPoints: 7 });
  addRect(s, 622, 168, 594, 352, C.white, { lineColor: C.line, borderRadius: "rounded-xl", shadow: "shadow-sm" });
  addText(s, "Задалсан мэдээллийн төлөв", 652, 194, 520, 26, { fontSize: 16, bold: true, color: C.muted });
  addText(s, "НЭЭЛТТЭЙ", 652, 246, 175, 26, { fontSize: 15, bold: true, color: C.green });
  addText(s, "type = 1", 652, 278, 175, 32, { fontSize: 26, bold: true, typeface: MONO, color: C.navy });
  addText(s, "Сарын төлөлтийн тооцоонд\nсонгож болно", 652, 326, 210, 58, { fontSize: 17, color: C.muted });
  addText(s, "ХААГДСАН", 936, 246, 175, 26, { fontSize: 15, bold: true, color: C.red });
  addText(s, "type = 0", 936, 278, 175, 32, { fontSize: 26, bold: true, typeface: MONO, color: C.navy });
  addText(s, "Тооцоонд оруулах\nсонголт идэвхгүй", 936, 326, 210, 58, { fontSize: 17, color: C.muted });
  s.shapes.add({ geometry: "line", position: { left: 894, top: 238, width: 0, height: 184 }, fill: "none", line: { style: "solid", fill: C.line, width: 1.2 } });
  addRect(s, 64, 554, 1152, 74, C.amberPale, { lineColor: "#F4D38A", borderRadius: "rounded-xl" });
  addText(s, "Үлдсэн эрсдэл", 84, 572, 150, 22, { fontSize: 14, bold: true, color: "#A66A00" });
  addText(s, "Баганын байрлал хэт зөрсөн PDF-д алдаатай мөрийг тэмдэглээд дараагийн мөрөө үргэлжлүүлэх хамгаалалт шаардлагатай.", 235, 569, 950, 42, { fontSize: 17, color: C.navy });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 13, 18", 6);
  setNotes(s, `[55 секунд]\nПарсерийн гол хүндрэл нь хүснэгт олон хуудсанд үргэлжилдэг, толгой мөр зарим хуудсанд давтагддаг, мөн нэг нүдний утга хэд хэдэн мөрт хуваагддаг байсан. Иймээс зөвхөн тогтмол координатад найдалгүй хэсгийн эхлэл, төгсгөлийн текстийг олж, шаардлагатай хэсгүүдийг нэгтгэсэн. Дараа нь хоосон утга, шинэ мөр, дугаарын хэлбэрийг цэвэрлэсэн. Нээлттэй зээлийг type нэг, хаагдсаныг type тэг гэж ялгасан нь фронтэнд төлөв харуулах болон хаагдсан мөрийг сарын төлөлтөөс хасах суурь болсон. Гэхдээ бүх тогтворгүй PDF тохиолдлыг бүрэн шийдсэн гэж дүгнээгүй.\n\nЭх сурвалж: Дадлагын тайлан, х. 13, 18.`);
}

// 7. Data relationships
{
  const s = p.slides.add();
  s.background.fill = C.white;
  addTitle(s, "Өгөгдлийн холбоос ба хамтран зээлдэгч", "Бизнесийн дүрэм", 7);
  const customer = addRect(s, 80, 182, 238, 78, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  customer.text = "Сонгосон харилцагч";
  customer.text.style = { typeface: FONT, fontSize: 20, bold: true, color: C.white, alignment: "center", verticalAlignment: "middle", autoFit: "none" };
  const match = addRect(s, 424, 182, 262, 78, C.mint, { lineColor: "#9DDFC9", borderRadius: "rounded-xl" });
  match.text = "PDF регистр таарч байна уу?";
  match.text.style = { typeface: FONT, fontSize: 19, bold: true, color: C.navy, alignment: "center", verticalAlignment: "middle", autoFit: "none" };
  const primary = addRect(s, 816, 142, 330, 78, C.pale, { lineColor: C.line, borderRadius: "rounded-xl" });
  primary.text = "Үндсэн зээлдэгчийн лавлагаа";
  primary.text.style = { typeface: FONT, fontSize: 19, bold: true, color: C.navy, alignment: "center", verticalAlignment: "middle", autoFit: "none" };
  const co = addRect(s, 816, 286, 330, 78, C.pale, { lineColor: C.line, borderRadius: "rounded-xl" });
  co.text = "Хамтран зээлдэгчийн тусдаа лавлагаа";
  co.text.style = { typeface: FONT, fontSize: 18, bold: true, color: C.navy, alignment: "center", verticalAlignment: "middle", autoFit: "none" };
  s.shapes.connect(customer, match, { kind: "straight", fromSide: "right", toSide: "left", line: { style: "solid", fill: C.green, width: 2 }, tail: { type: "triangle", width: "sm", length: "sm" } });
  s.shapes.connect(match, primary, { kind: "elbow", fromSide: "right", toSide: "left", line: { style: "solid", fill: C.green, width: 2 }, tail: { type: "triangle", width: "sm", length: "sm" } });
  s.shapes.connect(match, co, { kind: "elbow", fromSide: "right", toSide: "left", line: { style: "solid", fill: C.amber, width: 2 }, tail: { type: "triangle", width: "sm", length: "sm" } });
  addPill(s, "ТИЙМ", 704, 140, 86, C.mint, C.green);
  addPill(s, "ҮГҮЙ", 704, 285, 86, C.amberPale, "#A66A00");
  addRect(s, 80, 438, 1066, 152, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  addText(s, "Хадгалалтын шатлал", 104, 460, 190, 22, { fontSize: 14, bold: true, color: "#5FE0BB" });
  addText(s, "Customer", 104, 506, 170, 30, { fontSize: 23, bold: true, typeface: MONO, color: C.white });
  addText(s, "1 : N", 298, 510, 80, 24, { fontSize: 16, bold: true, color: "#91A0B6", alignment: "center" });
  addText(s, "CreditReference", 402, 506, 238, 30, { fontSize: 23, bold: true, typeface: MONO, color: C.white });
  addText(s, "1 : N", 670, 510, 80, 24, { fontSize: 16, bold: true, color: "#91A0B6", alignment: "center" });
  addText(s, "LoanRow", 782, 506, 170, 30, { fontSize: 23, bold: true, typeface: MONO, color: C.white });
  addText(s, "Нэг лавлагаанд олон зээлийн мөр", 936, 505, 184, 42, { fontSize: 15, color: "#BFC9D8", alignment: "right" });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 14–15", 7);
  setNotes(s, `[55 секунд]\nЭнэ хэсэгт техникийн шийдлээс өмнө бизнесийн дүрмийг зөв ойлгох шаардлага гарсан. Сонгосон харилцагчийн дэлгэц дээр өөр регистртэй PDF орж ирвэл түүнийг үндсэн хүний мэдээлэлтэй нэгтгэж болохгүй. CTO-оос дүрмийг тодруулсны дараа хүсэлтээр сонгосон customer_id болон PDF дэх регистрийг харьцуулсан. Таарвал үндсэн зээлдэгчийн лавлагаа, таарахгүй бол хамтран зээлдэгчийн тусдаа холбоос үүсгэнэ. Өгөгдөл Customer, CreditReference, LoanRow гэсэн шатлалтай бөгөөд нэг лавлагаанд олон зээлийн мөр харьяална.\n\nЭх сурвалж: Дадлагын тайлан, Өгөгдлийн холбоос ба хамтран зээлдэгч, х. 14–15.`);
}

// 8. Monthly payment
{
  const s = p.slides.add();
  s.background.fill = C.pale;
  addTitle(s, "Сарын төлөлтийн боловсруулалт", "Бэкэнд ба фронтэнд", 8);
  addRect(s, 64, 160, 452, 370, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  addText(s, "Тэнцүү нийт төлбөрийн арга", 92, 190, 360, 26, { fontSize: 16, bold: true, color: "#5FE0BB" });
  addText(s, "A = iP / [1 − (1 + i)⁻ⁿ]", 92, 246, 360, 52, { fontSize: 31, bold: true, color: C.white, typeface: "Noto Sans" });
  addText(s, "P · үндсэн үлдэгдэл\ni · сарын хүү\nn · үлдсэн сарын тоо", 92, 326, 300, 96, { fontSize: 18, color: "#D7DFEA" });
  addRect(s, 92, 448, 390, 54, "#183B39", { lineColor: "#183B39", borderRadius: "rounded-lg" });
  addText(s, "Хүү = 0 үед:  P / n", 110, 461, 350, 26, { fontSize: 18, bold: true, color: "#5FE0BB", typeface: MONO });
  addImageCard(s, imgCalculator, 570, 160, 646, 370, {
    alt: "Сарын төлөлтийн тооцоолуурын нууцалсан харагдац",
    fit: "cover",
    crop: { left: 0, top: 0, right: 0, bottom: 0 },
  });
  addText(s, "Фронтэнд", 64, 570, 180, 24, { fontSize: 18, bold: true, color: C.green });
  addText(s, "Сонголтын үр дүнг шууд урьдчилан харуулна", 64, 600, 470, 28, { fontSize: 17, color: C.muted });
  addText(s, "Бэкэнд", 630, 570, 180, 24, { fontSize: 18, bold: true, color: C.green });
  addText(s, "Хадгалагдах утгыг дахин тооцож нэг зарчмаар баталгаажуулна", 630, 600, 540, 44, { fontSize: 17, color: C.muted });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 15–16; Зураг 4.4", 8);
  setNotes(s, `[55 секунд]\nЗМС хүснэгтээс сонгосон бусад зээлийн сарын төлбөрийг хадгалахдаа зөвхөн фронтэнд тооцоонд найдахгүй, бэкэнд талд нэг зарчмаар дахин тооцох шаардлагатай болсон. Сонгосон нээлттэй мөр бүрийн үндсэн үлдэгдэл, жилийн хүү, үлдсэн хугацааг ашигласан. Хүү тэг үед энгийн хуваалт, бусад үед тэнцүү нийт төлбөрийн томьёо хэрэглэсэн. Фронтэнд тооцоо хэрэглэгчийн сонголтыг шууд харуулдаг бол бэкэнд тооцоо хадгалагдах утгыг тогтвортой тодорхойлно. Хаагдсан зээл тооцоонд орохгүй.\n\nЭх сурвалж: Дадлагын тайлан, Сарын төлөлтийн боловсруулалт, х. 15–16; Зураг 4.4.`);
}

// 9. Upload and table UI
{
  const s = p.slides.add();
  s.background.fill = C.white;
  addTitle(s, "Олон файл оруулах ба ЗМС интерфейс", "Хэрэглэгчийн урсгал", 9);
  addImageCard(s, imgUpload, 64, 168, 540, 320, {
    alt: "Олон PDF лавлагаа сонгох цонх",
    fit: "contain",
  });
  addText(s, "Файл сонголтын нөхцөл", 664, 168, 500, 32, { fontSize: 25, bold: true, color: C.navy });
  addBullets(s, [
    "Нэг удаад 1–10 PDF файл",
    "Файл тус бүр 2 MB-аас ихгүй",
    "Сонгосон файлын жагсаалтыг харуулах",
    "Үндсэн ба хамтран зээлдэгчийн лавлагааг хамтад нь оруулах",
  ], 664, 220, 520, 220, { fontSize: 20, spaceAfterPoints: 9 });
  addRect(s, 664, 465, 520, 118, C.amberPale, { lineColor: "#F4D38A", borderRadius: "rounded-xl" });
  addText(s, "Хамгаалалтын зааг", 688, 486, 180, 22, { fontSize: 14, bold: true, color: "#A66A00" });
  addText(s, "Фронтэнд өргөтгөл шалгах нь хангалтгүй. MIME төрөл, PDF бүтэц, хэмжээг сервер талд давхар шалгах шаардлагатай.", 688, 518, 470, 48, { fontSize: 17, color: C.navy });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 16–17; Зураг 4.5", 9);
  setNotes(s, `[45 секунд]\nДадлагын сүүлийн долоо хоногт үндсэн болон хамтран зээлдэгчийн олон лавлагааг нэг удаа сонгох урсгал дээр ажилласан. Фронтэнд нэгээс арван PDF сонгох, файл тус бүр хоёр мегабайтаас ихгүй эсэхийг шалгах, сонгосон файлуудын жагсаалтыг харуулах нөхцөл нэмсэн. ЗМС хүснэгтэд нээлттэй болон хаагдсан төлөвийг ялгаж, хаагдсан мөрийн хүү болон тооцоонд оруулах удирдлагыг идэвхгүй болгосон. Фронтэнд шалгалт хэрэглэгчийн алдааг багасгадаг ч серверийн бүрэн хамгаалалт биш тул MIME төрөл, PDF бүтэц, хэмжээг бэкэнд давхар шалгах шаардлагатай.\n\nЭх сурвалж: Дадлагын тайлан, х. 16–17; Зураг 4.5.`);
}

// 10. Verification
{
  const s = p.slides.add();
  s.background.fill = C.pale;
  addTitle(s, "Шалгалт ба бодит үр дүн", "Локал + стэйжинг", 10);
  const checks = [
    ["Формат таних", "Цогц лавлагаанд BurenScore парсер сонгогдсон"],
    ["Зээлийн төлөв", "Нээлттэй, хаагдсан мөрүүд ялгарсан"],
    ["Сарын төлөлт", "Сонгосон нээлттэй мөрөөр дахин тооцогдсон"],
    ["Олон лавлагаа", "Лавлагаа ба зээлдэгчээр тусдаа бүлэглэгдсэн"],
  ];
  checks.forEach((r, i) => {
    const y = 166 + i * 84;
    addText(s, "✓", 68, y + 8, 42, 42, { fontSize: 30, bold: true, color: C.green, alignment: "center" });
    addText(s, r[0], 128, y + 6, 245, 28, { fontSize: 20, bold: true, color: C.navy });
    addText(s, r[1], 388, y + 6, 520, 48, { fontSize: 17, color: C.muted });
    addPill(s, "ЛОКАЛ", 935, y + 4, 92, C.white, C.green);
    addPill(s, "СТЭЙЖИНГ", 1038, y + 4, 122, C.white, C.green);
    s.shapes.add({ geometry: "line", position: { left: 128, top: y + 66, width: 1032, height: 0 }, fill: "none", line: { style: "solid", fill: C.line, width: 1 } });
  });
  addRect(s, 64, 516, 1096, 118, C.navy, { lineColor: C.navy, borderRadius: "rounded-xl" });
  addText(s, "Тайлагнаагүй зүйл", 88, 536, 180, 22, { fontSize: 14, bold: true, color: "#5FE0BB" });
  addText(s, "Продакшн нэвтрүүлэлт, автомат тестийн бүрэн хамрах хүрээ\nХурдны хэмжилт, тестийн тоон статистик", 88, 568, 1028, 50, { fontSize: 17, bold: false, color: C.white });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 17–18, 21", 10);
  setNotes(s, `[50 секунд]\nӨөрчлөлт бүрийг эхлээд локал орчинд жишээ BurenScore файлаар шалгасан. Дараа нь стэйжинг орчинд фронтэнд–бэкэнд холболт, файл оруулах, парсер сонголт, бүлэглэлт болон хадгалалтыг давтан ажигласан. Үр дүнд цогц лавлагаанд зөв парсер сонгогдож, зээлийн төлөв ялгарч, сонгосон нээлттэй мөрийн сарын төлөлт дахин тооцогдож, олон лавлагаа тусдаа бүлгээр харагдсан. Гэхдээ энэ шалгалтыг продакшн нэвтрүүлэлт, бүх тохиолдлыг хамарсан автомат тест, эсвэл хурдны хэмжилт гэж тайлагнаагүй.\n\nЭх сурвалж: Дадлагын тайлан, х. 17–18; Шалгалт ба баталгаажуулалт, х. 21.`);
}

// 11. Evidence boundaries and learning
{
  const s = p.slides.add();
  s.background.fill = C.white;
  addTitle(s, "Нотолгооны хүрээ ба эзэмшсэн чадвар", "Үр дүнг зөв тайлбарлах", 11);
  addImageCard(s, imgMetrics, 64, 170, 560, 330, {
    alt: "InnoScore-ийн компанийн нийтэлсэн 95 хувь, 10 дахин, 40 хувийн үзүүлэлт",
    fit: "contain",
    crop: { left: 0, top: 0.15, right: 0.34, bottom: 0.10 },
  });
  addPill(s, "КОМПАНИЙН НИЙТЭЛСЭН", 86, 190, 224, C.amberPale, "#A66A00");
  addRect(s, 64, 526, 560, 94, C.amberPale, { lineColor: "#F4D38A", borderRadius: "rounded-xl" });
  addText(s, "95% · 10x · +40%", 88, 545, 220, 32, { fontSize: 24, bold: true, color: "#A66A00" });
  addText(s, "Миний дадлагын хугацаанд бие даан хэмжсэн эсвэл баталгаажуулсан үр дүн биш.", 310, 545, 288, 52, { fontSize: 16, color: C.navy });
  addText(s, "Эзэмшсэн чадвар", 688, 170, 470, 32, { fontSize: 25, bold: true, color: C.navy });
  addBullets(s, [
    "Өмнөх кодын шийдвэрийг уншиж ойлгох",
    "PDF-ийн харагдах ба уншигдах бүтцийн зөрүүг боловсруулах",
    "Бизнесийн дүрмийг өгөгдлийн холбоост буулгах",
    "Бэкэнд–фронтэнд урсгалыг нэг даалгавраар холбох",
    "Нууц мэдээлэлтэй хариуцлагатай ажиллах",
  ], 688, 224, 500, 272, { fontSize: 19, spaceAfterPoints: 8 });
  addRect(s, 688, 526, 500, 94, C.mint, { lineColor: "#B5EAD9", borderRadius: "rounded-xl" });
  addText(s, "Дадлагын бодит нотолгоо", 712, 544, 230, 20, { fontSize: 14, bold: true, color: C.green });
  addText(s, "Локал ба стэйжинг орчинд ажигласан ажиллагаа, кодын өөрчлөлт, тайлангийн баримт.", 712, 572, 446, 36, { fontSize: 17, color: C.navy });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, х. 4, 22; хэрэглэгчийн өгсөн InnoScore үзүүлэлтийн зураг", 11);
  setNotes(s, `[50 секунд]\nҮр дүнг хоёр өөр эх сурвалжаар ялгаж тайлбарлах нь чухал. Слайдын зүүн талд байгаа 95 хувийн нарийвчлал, 10 дахин хурдасгал, 40 хувийн бүтээмжийн өсөлт нь InnoScore-ийн компанийн нийтэлсэн бүтээгдэхүүний үзүүлэлт. Би дадлагын дөрвөн долоо хоногт эдгээрийг бие даан хэмжиж баталгаажуулаагүй. Харин миний ажлын нотолгоо нь тайланд тэмдэглэсэн кодын өөрчлөлт, локал болон стэйжинг орчинд ажигласан ажиллагаа юм. Энэ ажлаар өмнөх кодыг ойлгох, PDF-ийн тогтворгүй бүтэц боловсруулах, бизнесийн дүрмийг өгөгдлийн загварт буулгах, нууц мэдээлэлтэй ажиллах чадвараа хөгжүүлсэн.\n\nЭх сурвалж: Дадлагын тайлан, х. 4, 22; InnoScore-ийн хэрэглэгчийн өгсөн танилцуулгын зураг.`);
}

// 12. Conclusion
{
  const s = p.slides.add();
  s.background.fill = C.navy;
  addTitle(s, "Дүгнэлт", "Хамгаалалтын төгсгөл", 12, true);
  const items = [
    ["Формат", "BurenScore цогц лавлагааг гурван тэмдгээр таних зам нэмсэн"],
    ["Боловсруулалт", "Олон хуудаст хүснэгт, нээлттэй ба хаагдсан зээлийг задласан"],
    ["Холбоос", "Үндсэн болон хамтран зээлдэгч, олон лавлагааг тусад нь холбосон"],
    ["Хэрэглээ", "Сарын төлөлт, ЗМС хүснэгт, олон файл оруулах урсгалд өөрчлөлт хийсэн"],
  ];
  items.forEach((r, i) => {
    const y = 166 + i * 92;
    addText(s, String(i + 1).padStart(2, "0"), 72, y, 58, 38, { fontSize: 27, bold: true, color: "#5FE0BB" });
    addText(s, r[0], 150, y + 2, 190, 28, { fontSize: 21, bold: true, color: C.white });
    addText(s, r[1], 350, y + 2, 790, 52, { fontSize: 18, color: "#C9D2DF" });
  });
  addRect(s, 64, 566, 1152, 64, "#183B39", { lineColor: "#183B39", borderRadius: "rounded-xl" });
  addText(s, "Асуулт, хариулт", 86, 580, 1088, 34, { fontSize: 26, bold: true, color: C.white, alignment: "center" });
  addFooter(s, "Эх сурвалж: Дадлагын тайлан, Дүгнэлт, х. 23", 12, true);
  setNotes(s, `[30 секунд]\nДүгнэж хэлбэл, өмнө ашиглагдаж байсан ЗМС урсгалыг эвдэхгүйгээр BurenScore цогц лавлагааг таних, задлах, хадгалах, дэлгэцэд харуулах шинэ зам нэмэхэд оролцлоо. Ажлын хүрээнд олон хуудаст PDF, зээлийн төлөв, хамтран зээлдэгч, сарын төлөлт болон олон файл оруулах асуудлыг бэкэнд ба фронтэнд талаас нь холбон шийдсэн. Хийсэн өөрчлөлтийг локал болон стэйжинг орчинд шалгасан бөгөөд тайлагнаагүй үр дүнг хэтрүүлэн дүгнээгүй. Анхаарал тавьсанд баярлалаа. Асуултад хариулъя.\n\nЭх сурвалж: Үйлдвэрлэлийн дадлагын тайлан, Дүгнэлт, х. 23.`);
}

const stagingDir = path.join(workspaceDir, ".codex-finalizer");
await fs.mkdir(stagingDir, { recursive: true });
const candidatePath = path.join(stagingDir, "internship-defense-candidate.pptx");
await (await PresentationFile.exportPptx(p)).save(candidatePath);

const requirements = {
  explicitTotalSlideCount: 12,
  requiredNativeTableOwnerSlides: [],
  requiredNativeChartOwnerSlides: [],
};

const result = await finalizePresentation({
  ...requirements,
  workspaceDir,
  candidatePath,
  finalPath,
  pythonExecutable: RUNTIME_PYTHON,
  integrityValidatorPath: path.join(SKILL_DIR, "container_tools/inspect_presentation_package_integrity.py"),
  layoutValidatorPath: path.join(SKILL_DIR, "container_tools/inspect_presentation_layout_geometry.py"),
  layoutArgs: [
    "--expected-slide-size-emu", "12192000,6858000",
    "--validate-bullet-geometry",
    "--validate-heading-fit",
  ],
  requiredNativeTableOwnerSlides: [],
  fontPolicy: {
    basis: "design",
    families: [FONT, MONO],
  },
  verifyArtifactToolImport: true,
  receiptPath: path.join(stagingDir, "Monkhpurev_Internship_Defense_BurenScore.validation.json"),
});

console.log(JSON.stringify({ finalPath, result }, null, 2));
