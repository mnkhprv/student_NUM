# ITPEC FE 2025 оны 10-р сар — Subject A тайлбар

Эх материал: [асуултын PDF](./questions.pdf), [албан ёсны хариу](./answers.pdf), [ITPEC Past Exam](https://www.itpec.org/pastexamqa/fe.html).

## Хариуны хүснэгт

`1d 2c 3d 4a 5c 6b 7d 8a 9b 10c 11b 12d 13c 14c 15b 16b 17a 18d 19a 20d`

`21a 22d 23c 24d 25b 26c 27a 28d 29c 30b 31c 32b 33c 34d 35d 36b 37d 38a 39a 40c`

`41a 42b 43c 44a 45d 46a 47d 48b 49a 50d 51d 52b 53c 54b 55d 56d 57a 58b 59a 60c`

2024 оноос хуучны AM шалгалтыг **Subject A** гэж нэрлэдэг болсон. 60 асуултыг 90 минутанд бодно. Доорх тайлбар зөв хариуг цээжлүүлэхээс илүү, ашиглах томьёо болон сонголтыг ялгах үндэслэлийг Q1-Q60 дарааллаар үзүүлнэ.

## 1-9. Тоо, алгоритм, өгөгдлийн бүтэц, hardware

### Q1 - Хариу: d (`14.0`)

Sign bit 0 тул эерэг. Exponent `10000010₂=130`, жин `2^(130−127)=8`. Fraction `.110…₂=0.75`, тэгэхээр mantissa `1+0.75=1.75`. Эцсийн утга `8×1.75=14`.

### Q2 - Хариу: c

Зүүн тийш 3 bit shift хийх нь 8-аар үржүүлнэ: `n<<3=8n`. Үүн дээр анхны n-ийг нэмбэл `8n+n=9n`.

### Q3 - Хариу: d (`1/7`)

Гурван найзыг нэг block гэж үзвэл block болон бусад 4 хүн нийт 5 зүйл: `5!` байрлал. Найзууд block дотроо `3!` байрлана. Нийт боломж `7!`, иймээс `5!×3!/7!=1/7`.

### Q4 - Хариу: a (`0001000110`)

S1 initial state-ээс эхлээд input `0011001110`-ийн bit бүрээр тухайн arc-ыг дагана. Arc-ийн `x/y` тэмдэглэгээний y бүрийг бичихэд `0001000110` гарна.

### Q5 - Хариу: c

G-г A ба K-ийн хооронд оруулна. A-ийн next 300-аас 400 болж, K-ийн previous 100-аас 400 болно. Бусад хуучин pointer өөрчлөгдөхгүй, тиймээс a ба f.

### Q6 - Хариу: b (`2 удаа`)

Euclidean algorithm:

```text
56 mod 48 = 8
48 mod 8 = 0
```

Flowchart-ийн A хэсгийг хоёр iteration-д дайрна.

### Q7 - Хариу: d (Overriding)

Subclass нь superclass-д байсан method-той яг ижил нэр, parameter type буюу signature-тай method-ийг өөр behavior-тэй дахин тодорхойлж байна.

### Q8 - Хариу: a (`2 ms`)

0-5 ms-ийн timeline дээр A нь B-ээс өндөр priority тул давхцвал B-г тасална. Interrupt process-уудын бодитоор ажилласан хэсгийг нийлүүлэхэд 3 ms; үлдсэн `5-3=2 ms`-ийг main process ашиглана.

### Q9 - Хариу: b (`25.725 ms`)

```text
seek             = 5 ms
average rotation = (60/6000)/2 = 5 ms
transfer         = (16/1024) s = 15.625 ms
controller       = 0.1 ms
нийт              = 25.725 ms
```
## 10-17. Компьютерийн бүтэц, system, logic, multimedia

### Q10 - Хариу: c (3D printer)

3D printer нь digital 3D model-оос fused filament fabrication зэрэг аргаар материалыг давхарлан бодит биет үүсгэнэ.

### Q11 - Хариу: b (Edge computing)

Sensor эсвэл device-ээс гарсан data-г алсын cloud руу бүгдийг явуулахаас өмнө эх үүсвэрт ойр server дээр боловсруулна. Ингэснээр latency багасаж real-time response сайжирна.

### Q12 - Хариу: d

Server заавал ажиллах тул `a`. Гурван client-ээс ядаж нэг ажиллах магадлал `1-(1-b)^3`; хоёр printer-ээс ядаж нэг ажиллах магадлал `1-(1-c)^2`. Эдгээрийг үржүүлнэ.

### Q13 - Хариу: c (`20 ms`)

FCFS дараалал A,B,C,D,E. Turnaround time нь cumulative burst time: `10,16,18,26,30`. Дундаж `(10+16+18+26+30)/5=20`.

### Q14 - Хариу: c (`579`)

Folding and adding method-д key-г хэсгүүд болгон тасалж нэмнэ. `123456 → 123+456=579`, тэгэхээр record address 579.

### Q15 - Хариу: b (Page 2)

Эхний `{1,2,3,2,1}` дараа 4 ирэхэд хамгийн удаан хэрэглээгүй 3 хасагдана. Memory `{1,2,4}`. Дараа 5 ирэх үед 2 хамгийн удаан хэрэглэгдээгүй тул солигдоно.

### Q16 - Хариу: b

Gate бүрийн output-ийг завсрын хувьсагчаар бичиж, bubble нь NOT гэдгийг тооцно. De Morgan-ийн дүрмээр хялбарчлахад b илэрхийлэл гарна.

### Q17 - Хариу: a (Anti-aliasing)

Налуу болон муруй ирмэгийн шаталсан pixel-үүдэд завсрын өнгө, brightness хэрэглэж харагдах ирмэгийг жигд болгоно.
## 18-26. Өгөгдлийн сан ба сүлжээ

### Q18 - Хариу: d

Relational model-д attribute-ийн дараалал утгагүй. Column-уудын байрлалыг сольсон ч нэр болон tuple дахь харгалзах утгууд зөв байвал relation хэвээр.

### Q19 - Хариу: a

`OrderCode→CustomerCode`, мөн `CustomerCode→CustomerAddress`. Иймээс transitivity-гаар `OrderCode→CustomerAddress`. Энэ chain-ийг зөв үзүүлсэн нь a.

### Q20 - Хариу: d (Distributed database)

Нэг логик database-ийн өөр өөр хэсгийг олон location-д хадгалж, query болон transaction processing-ийг тэдгээр node-д хуваарилна.

### Q21 - Хариу: a

Subquery нь New York location-той department ID-уудыг гаргана. Main query `department_id IN (...)` ашиглан эдгээр department-д ажилладаг employee-үүдийг сонгоно.

### Q22 - Хариу: d (Isolation)

Зэрэг ажиллаж буй transaction бүр бусад transaction-ийн дуусаагүй intermediate өөрчлөлтийг харахгүй, дангаараа ажиллаж байгаа мэт үр дүн гаргана.

### Q23 - Хариу: c (QoS)

QoS нь voice, video зэрэг delay-sensitive traffic-д priority, bandwidth өгч latency, jitter, packet loss-ийг удирдана.

### Q24 - Хариу: d (`FF:FF:FF:FF:FF:FF`)

PC5 PC4-ийн MAC address-ийг мэдэхгүй учраас ARP request-ийг LAN дахь бүх төхөөрөмжид broadcast MAC-аар илгээнэ. PC4 өөрийн MAC-тай reply өгнө.

### Q25 - Хариу: b (Gateway)

Gateway нь transport layer болон түүнээс дээших ялгаатай protocol, data format, application system хооронд conversion хийж чадна.

### Q26 - Хариу: c (MIME)

MIME нь email header болон body-г өргөтгөж content type, encoding-ийг зааснаар audio, image, binary attachment дамжуулах боломж олгоно.
## 27-33. Мэдээллийн аюулгүй байдал

### Q27 - Хариу: a (Baiting)

“Шалгалтын асуулт, хариу” гэсэн сонирхол татах шошготой malware USB зориуд үлдээсэн. Хохирогч шагнал мэт зүйлд татагдаж өөрөө залгадаг social engineering аргыг baiting гэдэг.

### Q28 - Хариу: d (Y-ийн public key)

Y message hash-ийг өөрийн private key-ээр sign хийсэн. X нь Y-ийн public key ашиглаж signature-г verify хийснээр илгээгч Y мөн, message өөрчлөгдөөгүйг шалгана.

### Q29 - Хариу: c

Хуурамч record Company B-ийн DNS cache-д байна. Тиймээс B-ийн DNS-г ашигладаг ажилтан Company A-ийн FQDN асуухад attacker-ийн server X-ийн IP авна.

### Q30 - Хариу: b (Opportunity)

Fraud triangle нь pressure, opportunity, rationalization. Хяналт сул, system эсвэл дүрэм fraud хийхэд амар болгосон орчныг opportunity гэдэг.
### Q31 - Хариу: c (IDS)

Intrusion Detection System нь network traffic эсвэл server event-ийг хянаж халдлагын шинж илэрвэл administrator-т alert өгнө. IDS ихэвчлэн илрүүлдэг; автоматаар block хийх нь IPS-ийн үүрэг.

### Q32 - Хариу: b (Port scanning)

Attacker preliminary reconnaissance үед target host дээр ямар port нээлттэй, ямар service/version ажиллаж байгааг хайж дараагийн exploit-оо сонгоно.

### Q33 - Хариу: c

WAF request-ийн HTTP агуулгыг унших ёстой. A, B дээр traffic HTTPS-ээр encrypted; SSL accelerator-ийн дараах C цэгт decrypted HTTP болсон тул WAF байрлуулах зөв газар.
## 34-47. Software engineering, project, service, audit

### Q34 - Хариу: d (Use case diagram)

Use case diagram нь external actor системээс ямар goal биелүүлэх, ямар service ашиглахыг дүрсэлнэ. Дотоод algorithm эсвэл message timeline харуулахгүй.

### Q35 - Хариу: d

Software architecture design үед requirement-ийг top-level structure болгон хувиргаж component-ууд, тэдгээрийн responsibility ба interface-ийг тодорхойлно.

### Q36 - Хариу: b

State transition test нь тухайн system ямар internal state-д байхад ямар event ирвэл хаашаа шилжиж, ямар output өгөхийг specification-тэй харьцуулна.

### Q37 - Хариу: d (Acceptance test)

Эцсийн user эсвэл customer software өөрийн business need, requirement, acceptance criteria-г хангаж байгаа эсэхийг батална.

### Q38 - Хариу: a (`$64,000`)

```text
Potential defects = 2,000×0.04 = 80
First-year discovered = 80×0.20 = 16
Major = 16×0.20 = 3.2
Cost = 3.2×20,000 = 64,000 dollars
```

Эхний жил зөвхөн major defect засна.

### Q39 - Хариу: a (Refactoring)

Program-ийн external specification, user-д харагдах behavior-ийг өөрчлөхгүйгээр internal structure-г цэвэрлэж readability, maintainability-г сайжруулна.

### Q40 - Хариу: c

Patent cross-licensing-д компаниуд тодорхой technology/product field дэх patent-уудаа бие биедээ ашиглуулах license харилцан олгоно.

### Q41 - Хариу: a (A–C–E–H)

Arrow diagram дахь start-аас finish хүртэлх боломжит зам бүрийн activity duration-ийг нэмнэ. Хамгийн урт, нийт float буюу slack 0 зам нь A–C–E–H.

### Q42 - Хариу: b (`$75,000`)

PERT three-point estimate:

```text
(optimistic + 4×most likely + pessimistic) / 6
=(50,000 + 4×70,000 + 120,000) / 6
=75,000
```

### Q43 - Хариу: c (`4.8 цаг`)

Service time нэг өдөр `23-7=16` цаг, сард `16×30=480` цаг. Availability 99% гэдэг нь downtime хамгийн ихдээ 1%: `480×0.01=4.8` цаг.

### Q44 - Хариу: a

Problem record-д root cause investigation хийдэг бөгөөд түүнийг үүсгэсэн incident record-ууд руу cross-reference хадгална. Нэг problem олон incident-тэй холбоотой байж болно.

### Q45 - Хариу: d

System design user requirement-ийг зөв тусгасан эсэхэд user department-ийн оролцоо шаардлагатай. Тиймээс user department design document review-д оролцсон эсэхийг audit хийнэ.

### Q46 - Хариу: a (Economic feasibility)

Proposed system-ийн lifetime benefit болон lifetime cost-ийг мөнгөн дүнгээр харьцуулж ашигтай эсэхийг шалгах нь economic feasibility.

### Q47 - Хариу: d

Outsourced service-ийн хүссэн quality level-ийг гэрээгээр тохирч, availability, response time зэрэг хэмжих KPI/index хэрэглэвэл provider-ийн performance-ийг хянаж сайжруулна.
## 48-60. Бизнес, менежмент, үйлдвэрлэл

### Q48 - Хариу: b (DFD)

Data Flow Diagram нь external entity, process, data store хооронд data ямар чиглэлээр урсаж байгааг харуулна. Class-ийн structure эсвэл user goal дүрслэхгүй.

### Q49 - Хариу: a (Benchmarking)

Өөрийн product, service, process-ийн performance-ийг competitor эсвэл industry leader-тэй чанарын болон тоон үзүүлэлтээр харьцуулж gap, сайжруулах арга олно.

### Q50 - Хариу: d (Relationship marketing)

Нэг удаагийн борлуулалтаас илүү customer-тай урт хугацааны итгэлцэл, холбоо хадгалж customer lifetime value болон тогтвортой sales өсгөх зорилготой.

### Q51 - Хариу: d (ERP)

Finance, HR, sales, production зэрэг company-wide resource болон process-ийг нэгтгэн төлөвлөж, хянаж management efficiency сайжруулна.

### Q52 - Хариу: b (Process innovation)

Product өөрийг нь бус, manufacturing procedure-г шинээр зохион байгуулж quality, cost, speed-ийг сайжруулсан тул process innovation.

### Q53 - Хариу: c (Temperature sensor)

IoT-ийн data collection шатанд sensor equipment-ийн temperature зэрэг физик утгыг хэмжин digital data болгоно. Wireless нь transmission, analysis tool нь analysis шат.

### Q54 - Хариу: b (RFID)

RFID нь radio wave ашигладаг тул barcode шиг шууд харах шугам шаардахгүй, package-ийн гаднаас tag-ийн мэдээллийг уншиж чадна.

### Q55 - Хариу: d (Sharing economy)

Хувь хүмүүсийн ашиглаагүй машин, өрөө, багаж зэрэг asset-ийг platform-аар бусдад түр ашиглуулах, хуваалцах механизм.

### Q56 - Хариу: d (Green IT)

Web conference ашигласнаар уулзалтад зорчих хэрэгцээ, шатахуун, CO₂ emission багасна. Энэ нь IT ашиглан environmental load бууруулсан жишээ.

### Q57 - Хариу: a (CIO)

CIO нь business strategy-г дэмжих information strategy гаргаж, company-wide information resource ба IT investment-ийн үр өгөөжийг оновчилно.

### Q58 - Хариу: b

Acceptance number C ихсэхэд илүү олон defective sample байсан ч lot pass болно. Иймээс ижил percent defective дээр acceptance probability өснө: C=2 муруй хамгийн дээр, C=0 хамгийн доор.

### Q59 - Хариу: a (Balance sheet)

Balance sheet нь тодорхой нэг өдрийн assets, liabilities, equity/net assets-ийг харуулдаг. Income statement нь хугацааны revenue ба expense-ийг харуулна.

### Q60 - Хариу: c

Shrink-wrap license-ийн нөхцөл package дээр байдаг бөгөөд package-ийг нээсэн үйлдлээр хэрэглэгч нөхцөлийг зөвшөөрч license agreement байгуулагдсан гэж үзнэ.

## Давтах гол сэдэв

- IEEE 754, probability, scheduling, HDD, paging
- SQL, transaction, network, DNS, security
- UML, testing, refactoring, project estimation
- ERP, IoT, RFID, accounting, business strategy
