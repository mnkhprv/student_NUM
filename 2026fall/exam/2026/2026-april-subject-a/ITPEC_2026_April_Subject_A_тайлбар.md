# ITPEC FE 2026 оны 4-р сарын Subject A - 60 асуултын тайлбар

2024 оноос хуучны AM шалгалтыг **Subject A** гэж нэрлэдэг болсон. Энэ шалгалт 60 асуулттай, 90 минут үргэлжилнэ. Нэг асуултад дунджаар 1 минут 30 секунд ногдоно.

Доорх Q1-Q60 тайлбарын эх сурвалжийг асуултын дугаартай нь `(2026S, FE, Subject-A, Qn)` гэж ойлгоно. Асуултуудыг бүтнээр нь хуулалгүй, гол санааг Монгол хэлээр тайлбарласан.

## 1-8. Математик, алгоритм, өгөгдлийн бүтэц

### Q1 - Хариу: c

Prefix notation-д operator нь operand-уудаасаа өмнө бичигдэнэ. `(a-b)/(c+d)` нь `/ - a b + c d`, дараа нь `e` зэрэгт дэвшүүлэхээр `^ / - a b + c d e` болно.

### Q2 - Хариу: b (`668.25`)

Octal `1234.2₈`-ийг аравтын тоонд шилжүүлбэл `1×8³ + 2×8² + 3×8¹ + 4×8⁰ + 2×8⁻¹`. Энэ нь `512+128+24+4+0.25 = 668.25`.

### Q3 - Хариу: a (Utilization)

Queueing theory-д mean arrival rate-ийг `λ`, mean service rate-ийг `μ` гэвэл `λ/μ` нь server utilization буюу ашиглалтын хувь.

### Q4 - Хариу: c (`123-456-7890`)

`^\d{2,4}-\d+-\d{3,4}$` гэдэг нь эхэнд 2-4 цифр, дараа нь `-`, нэгээс олон цифр, дахин `-`, төгсгөлд 3-4 цифр байна гэсэн үг. Зөвхөн c энэ бүх нөхцөлийг хангана.

### Q5 - Хариу: c

Postfix notation-д operator operand-уудын ард орно. `a+(b×c)+(d×e)` нь `a b c × + d e × +`.

### Q6 - Хариу: d

BST-д 11-ийг оруулах зам: `11<14` тул зүүн, `11>7` тул баруун, `11<12` тул зүүн, `11>10` тул 10-ын баруун талд орно.

### Q7 - Хариу: b (`3`)

Энэ нь Euclidean GCD алгоритм. `231 mod 15=6`, `15 mod 6=3`, `6 mod 3=0`, тэгэхээр хамгийн их ерөнхий хуваагч нь 3.

### Q8 - Хариу: c

Constructor нь object үүсэх үед дуудагдаж initial state, field-үүдийг тохируулдаг. Бүх хэлэнд ердийн method шиг яг адил inherited болдоггүй.

## 9-18. Компьютерийн бүтэц, OS, логик хэлхээ

### Q9 - Хариу: c (Instruction register)

Main memory-оос fetch хийсэн instruction эхлээд instruction register-д орж, дараа нь instruction decoder руу дамжина. Program counter нь дараагийн instruction-ийн address-ийг хадгалдаг.

### Q10 - Хариу: d

Cache miss гэдэг нь хэрэгтэй data cache-д байхгүй гэсэн үг. Тэгэхээр CPU data-г main memory-оос авч cache-д оруулна.

### Q11 - Хариу: b (`128 MB/s`)

Нэг bus cycle-д 4 clock хэрэгтэй тул `64 MHz / 4 = 16 сая transfer/s`. Нэг transfer нь `64 bit = 8 byte`, иймээс `16 сая × 8 = 128 MB/s`.

### Q12 - Хариу: b (RAID 1)

Хоёр ижил disk-тэй үед RAID 1 нь нэг өгөгдлийг хоёр disk дээр mirror хийдэг. Нэг disk эвдэрсэн ч нөгөө disk-ээс ажиллана.

### Q13 - Хариу: b

Зөв дараалал: одоогийн system performance-ийг ойлгох `(iii)`, шинэ ажлын requirement авах `(iv)`, хэрэгтэй configuration санал болгох `(ii)`, саналаа үнэлж review хийх `(i)`.

### Q14 - Хариу: d (`97%`)

Нэг job I/O хүлээж байх магадлал 0.3. Гурвуулаа зэрэг хүлээх магадлал `0.3³=0.027`. CPU idle 2.7%, utilization `100-2.7=97.3%`, бүхэл хувиар 97%.

### Q15 - Хариу: c (`11.5 ms`)

Round Robin, quantum=5 үед дуусах хугацаа: P1=5, P3=14, P4=27, P2=30. Бүгд 0-д ирсэн тул waiting time нь `completion-burst`: P1=0, P2=17, P3=10, P4=19. Дундаж `(0+17+10+19)/4=11.5 ms`.

### Q16 - Хариу: d (Linker)

Compiler тус тусын source module-ийг object module болгоно. Linker эдгээр module болон library-г холбож executable file үүсгэнэ.

### Q17 - Хариу: b (NAND)

Зөвхөн A=1, B=1 үед output 0, бусад бүх үед 1 гаргадаг gate бол NAND.

### Q18 - Хариу: a (`73940`)

Weighted sum: `7×1 + 3×2 + 9×3 + 4×4 = 56`. `56 mod 11 = 1`, `11-1=10`, үр дүнгийн сүүлийн цифр 0 тул check digit 0. Иймээс `73940`.

## 19-27. Өгөгдлийн сан ба сүлжээ

### Q19 - Хариу: b

Relational model-ийн relation нь database implementation дээр table болдог. Attribute нь column, tuple нь row-той дүйцнэ.

### Q20 - Хариу: d

3NF-д орохын тулд table эхлээд 2NF байх ба non-key attribute өөр non-key attribute-аас дамжин хамаарсан transitive dependency байх ёсгүй.

### Q21 - Хариу: d (`PTY, QTY, STY`)

Y нь ямар ч functional dependency-ийн баруун талд байхгүй тул key бүр Y-г агуулна. `PTY`, `QTY`, `STY` тус бүрээр dependency-үүдийг ашиглан P,Q,R,S,T,Y бүгдийг гаргаж болно. Аль нэг attribute-ийг хасвал бүх attribute гарахгүй.

### Q22 - Хариу: d

SQL `LIKE 'A%'` гэдэг нь A үсгээр эхэлж, ард нь 0 буюу олон тэмдэгттэй нэрсийг сонгоно. `%A` бол A-гаар төгссөн нэр.

### Q23 - Хариу: d

DBMS log нь update-ийн өмнөх болон дараах утгыг бичдэг. Failure гарвал undo/redo хийж database-ийг consistency-тэй төлөвт сэргээнэ.

### Q24 - Хариу: b (NAT)

NAT нь private IP болон global IP хооронд address translation хийж, дотоод төхөөрөмжүүдийг Internet-д холбодог.

### Q25 - Хариу: c (Flow control)

Flow control нь receiver боловсруулах чадвараасаа их data авахгүй байхаар sender-ийн илгээх хэмжээг удирдана. Congestion control нь network-ийн нийт ачаалалтай холбоотой.

### Q26 - Хариу: b (DNS)

DNS нь domain/host name-ийг IP address-тэй холбоно. IP автоматаар олгох нь DHCP, private/global хөрвүүлэх нь NAT.

### Q27 - Хариу: b (LTE)

LTE нь mobile device болон data terminal-д зориулсан өргөн зурвасын cellular communication standard. IEEE 802.11 бол Wi-Fi, NFC нь маш ойрын зайд ажиллана.

## 28-34. Мэдээллийн аюулгүй байдал

### Q28 - Хариу: c

Multi-factor authentication нь өөр төрлийн factor хослуулна. Password нь “мэддэг зүйл”, smartphone app-ийн one-time code нь “эзэмшдэг зүйл”, тиймээс хоёр factor болно.

### Q29 - Хариу: d (Integrity)

Information asset үнэн зөв, бүрэн бүтэн байх шинж нь integrity. Confidentiality нь зөвшөөрөлгүй уншихаас, availability нь хэрэгтэй үед ашиглах боломжийг хамгаална.

### Q30 - Хариу: b

Trojan horse нь хэрэгтэй, хууль ёсны program мэт харагдавч дотроо malicious ажиллагаа агуулсан software.

### Q31 - Хариу: b

Ransomware нь компьютер эсвэл file-д хандах боломжийг хааж, тайлахын тулд мөнгө нэхдэг malware.

### Q32 - Хариу: b (Risk avoidance)

Компани эрсдэл үүсгэх social media plugin-ийг бүтээгдэхүүнээс бүрэн хассан. Эрсдэлтэй ажиллагааг хийхгүй байх нь risk avoidance.

### Q33 - Хариу: a (CSIRT)

CSIRT нь security incident-ийн мэдээлэл хүлээн авч, шалгаж, хариу арга хэмжээ зохион байгуулдаг байгууллага эсвэл баг.

### Q34 - Хариу: c

`'1'='1'` үргэлж true тул SELECT бүх account мөрийг авна. Дараах `DROP TABLE accounts` нь хүснэгтийг бүхэлд нь устгана. Энэ бол SQL injection-ийн ноцтой жишээ.

## 35-45. Software engineering, project, service, audit

### Q35 - Хариу: d (Use case diagram)

Use case diagram нь actor-ууд, system-ийн function/use case-ууд болон тэдгээрийн холбоог ерөнхий зураг хэлбэрээр харуулна.

### Q36 - Хариу: a (Adapter)

Adapter pattern нь interface нь таарахгүй хоёр class-ийг хооронд нь ажиллуулах хөрвүүлэгч давхарга өгдөг.

### Q37 - Хариу: b (Encapsulation)

Encapsulation нь data болон түүн дээр ажиллах method-уудыг нэг object-д багцалж, дотоод implementation-ийг гаднаас нууна.

### Q38 - Хариу: a (Adaptive maintenance)

OS, DBMS зэрэг ажиллах орчин өөрчлөгдөхөд system-ийг тааруулан өөрчлөхийг adaptive maintenance гэдэг. Bug засах нь corrective maintenance.

### Q39 - Хариу: a (Agile)

Жижиг cross-functional team, байнга өөрчлөгдөх requirement, ойр ойрхон user feedback гэсэн нөхцөлд Agile хамгийн тохиромжтой.

### Q40 - Хариу: c (Optimizing)

CMMI maturity level-ийн хамгийн өндөр буюу 5-р түвшин нь Optimizing. Энэ түвшинд process-ийг хэмжилт, feedback ашиглан тасралтгүй сайжруулна.

### Q41 - Хариу: d (Scope)

Project-ийн objective, deliverable, requirement, boundary-г тодорхойлох болон эдгээрийн өөрчлөлтийг удирдах нь scope management.

### Q42 - Хариу: d (`66 person-month`)

Development effort: `500 FP / 10 FP = 50 person-month`. Installation ба education 10 нэмээд 60. Project management нь үүний 10% буюу 6 тул нийт `66 person-month`.

### Q43 - Хариу: b

Mission-critical system эвдэрвэл компани, хэрэглэгч эсвэл нийгэмд маш их нөлөө үзүүлнэ. Тиймээс өндөр availability, reliability шаарддаг.

### Q44 - Хариу: c

Trend analysis нь resource usage-ийн хугацааны дарааллыг судалж, ирээдүйн хэрэглээ хэрхэн өөрчлөгдөхийг таамаглана.

### Q45 - Хариу: c

Availability нь system хэрэгтэй үед ажиллаж байх чанар. Downtime-г заасан SLA-ийн түвшнийг хэмжиж, хадгалах нь availability-ийн audit check болно.

## 46-60. Бизнес, менежмент, үйлдвэрлэл

### Q46 - Хариу: d (BPR)

Business Process Reengineering нь үнэ цэнэ бүтээх process-уудыг үндсээр нь дахин зохион байгуулж, productivity, cost, service, quality-д том ахиц гаргах арга.

### Q47 - Хариу: c (In-basket)

In-basket training-д суралцагч бодит ажлын орчныг дуурайсан олон document, request, task-ийг хязгаарлагдсан хугацаанд эрэмбэлж шийддэг.

### Q48 - Хариу: c (RFP)

Захиалагч procurement-ийн system, requirement, condition-ийг тодорхойлж vendor-оос proposal хүсэж байгаа шат нь Request for Proposal. Өмнөх мэдээлэл хүсэх шат нь RFI.

### Q49 - Хариу: c (Synergy effect)

Хоёр компанийн customer, technology, cost saving-ийг нийлүүлснээр тус тусдаа бий болгохоос их үнэ цэнэ гарч байна. Үүнийг `1+1>2` буюу synergy effect гэдэг.

### Q50 - Хариу: b (Franchising)

Independent owner нь компанийн brand, стандарт, support-ийг ашиглаж royalty төлөхийн зэрэгцээ өөрийн store-д хөрөнгө оруулж удирдаж байгаа нь franchise.

### Q51 - Хариу: b

BSC-ийн internal business process perspective нь үйлдвэрлэлийн process-ийн efficiency-г хэмжинэ. Manufacturing days буурах нь productivity сайжирсны KPI.

### Q52 - Хариу: a (`$340,000`)

- a: `200,000 + 4×3×10,000 + 1×2×10,000 = 340,000`
- b: `350,000`
- c: `10×3×10,000 + 3×2×10,000 = 360,000`
- d: `10×6×6,000 + 2×2×10,000 = 400,000`

Хамгийн бага зардал нь a.

### Q53 - Хариу: a (Smart grid)

Smart grid нь communication, information technology ашиглан power generation, хэрэглээг уялдуулж, renewable energy ашиглалт, тогтвортой supply, demand adjustment-ийг сайжруулдаг.

### Q54 - Хариу: b

Robot-д бүх хөдөлгөөнийг нэг бүрчлэн programчлахын оронд өөрөө data-аас суралцаж ажиллагаагаа сайжруулж байгаа нь machine learning.

### Q55 - Хариу: b

Олон image-ээс pedestrian болон vehicle-ийн ялгааг сурч таних нь deep learning-ийн computer vision хэрэглээ. Бусад сонголт нь энгийн sensor, control эсвэл update ажиллагаа.

### Q56 - Хариу: a (TQM)

Total Quality Management нь customer-ийн expectation-ийг хангах буюу давах чанартай product, service бүтээхэд бүх байгууллагыг оролцуулдаг.

### Q57 - Хариу: c (Work sharing)

Нэг ажилтны цагийг багасгаж ажлыг олон хүнд хувааснаар одоогийн ажлын байрыг хадгалж, шинэ employment opportunity бий болгохыг work sharing гэдэг.

### Q58 - Хариу: b (Monte Carlo Analysis)

Input-уудыг бодит хүрээнд санамсаргүй өөрчилж, мянга мянган simulation ажиллуулаад possible outcome-ийн probability distribution гаргах нь Monte Carlo analysis.

### Q59 - Хариу: b (`18,200 units`)

Fixed cost: `130,000+10,000=140,000`. Нэгжийн contribution margin: `17-3-4=10`. Хүссэн profit-ийг нэмбэл `(140,000+42,000)/10 = 18,200` нэгж.

### Q60 - Хариу: d (ISO)

WTO-ийн гишүүн олон улсын government agency-д ашиглагдах бүтээгдэхүүнд international ISO standard тохиромжтой. ANSI, BSI, FCC нь тухайн улсын эсвэл байгууллагын стандарт.

## Цээжлэх гол томьёо

- Queue utilization: `λ / μ`
- Bus transfer rate: `bus cycles/s × bytes/transfer`
- CPU utilization with n independent jobs: `1 - (I/O wait probability)^n`
- Waiting time: `completion time - arrival time - burst time`
- Function Point effort: `FP / productivity`
- Target-profit quantity: `(fixed cost + target profit) / contribution margin`
- Contribution margin: `selling price - variable cost`

## Давтах зөвлөмж

Эх PDF-ээс эхлээд хариуг харалгүй бод. Дараа нь тайлбараа шалгаад, яагаад бусад гурван сонголт буруу болохыг өөрийн үгээр хэл. Q2, Q7, Q11, Q14, Q15, Q18, Q21, Q42, Q52, Q59-ийг цаасан дээр дахин бодвол тооцооны хэсэг сайн тогтоно.
