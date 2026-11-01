# ITPEC FE 2025 оны 4-р сар — Subject A тайлбар

Эх материал: [асуултын PDF](./questions.pdf), [албан ёсны хариу](./answers.pdf), [ITPEC Past Exam](https://www.itpec.org/pastexamqa/fe.html).

## Хариуны хүснэгт

`1a 2a 3b 4c 5d 6d 7a 8c 9c 10c 11c 12c 13d 14a 15c 16c 17c 18c 19b 20d`

`21a 22c 23a 24b 25c 26c 27a 28b 29b 30d 31b 32b 33c 34b 35c 36c 37d 38b 39d 40b`

`41a 42a 43b 44d 45c 46d 47c 48c 49a 50d 51b 52d 53b 54b 55c 56a 57b 58b 59d 60b`

2024 оноос хуучны AM шалгалтыг **Subject A** гэж нэрлэдэг болсон. 60 асуултыг 90 минутанд бодно. Доорх тайлбар асуултыг бүтнээр хуулалгүй, зөв хариунд хүрэх гол томьёо, ялгах ойлголтыг Q1-Q60 дарааллаар үзүүлнэ.

## 1-8. Тооллын систем, алгоритм, CPU

### Q1 - Хариу: a

Дээд 4 битийг үлдээхийн тулд `11110000`-тай AND хийнэ. Маскын 1 байгаа байрлалын bit хэвээр үлдэж, 0 байгаа доод дөрвөн байрлал бүгд 0 болно.

### Q2 - Хариу: a (`10111.011₂`)

Бүхэл хэсэг `23 = 16+4+2+1 = 10111₂`. Бутархай хэсэг `0.375=0.25+0.125=0.011₂`. Иймээс `23.375 = 10111.011₂`.

### Q3 - Хариу: b (Machine learning)

Өгөгдлөөс дүрэм, хэв маягийг автоматаар сурч, өмнө хараагүй өгөгдөлд ангилал эсвэл таамаг гаргах нь machine learning-ийн үндсэн шинж.

### Q4 - Хариу: c

Line-following robot нь sensor-оор шугам аль талд байгааг мэдэрнэ. Дараа нь баруун, зүүн моторын хурдыг зөрүүлж шугам руугаа эргэнэ. Зураг дахь энэ feedback-тэй тохирох нь c.

### Q5 - Хариу: d

Tree traversal бүрийг өгөгдсөн модон дээр дарааллаар нь бичиж харьцуулна. Сүүлчийн хоёр node ижил гарах нөхцөлийг зөвхөн d хангана.

### Q6 - Хариу: d (Depth-first search)

DFS нь нэг салааг цааш явах боломжгүй болтол гүн явж, дараа нь өмнөх node руу буцдаг. Энэ stack маягийн дарааллыг үзүүлсэн сонголт d.

### Q7 - Хариу: a

Элемент бүрийн hash address-ийг олж, collision гарвал асуултад өгсөн дараагийн байрлал хайх дүрмийг хэрэглэнэ. Сонголтуудыг дарааллаар simulate хийхэд зөв хүснэгт үүсгэх insertion order нь a.

### Q8 - Хариу: c (`200 MIPS`)

Нэг instruction 4 clock хэрэглэдэг. Тэгэхээр нэг секундэд гүйцэтгэх instruction:

```text
800 MHz / 4 = 200 million instructions/s = 200 MIPS
```
## 9-18. Компьютерийн бүтэц, OS, logic, security

### Q9 - Хариу: c (Stack pointer)

Stack pointer нь stack-ийн оройд байгаа элементийн address-ийг хадгалдаг. Push, pop хийх бүрт энэ register өөрчлөгдөнө.

### Q10 - Хариу: c (`ойролцоогоор 0.83`)

Cache hit үед хурдан хугацаа, miss үед main memory хүртэлх удаан хугацааг жигнэсэн дунджаар бичнэ. Асуултын хоёр системийн average access time-ийг тэнцүүлж hit ratio-г бодоход ойролцоогоор `0.83`.

### Q11 - Хариу: c (PaaS)

PaaS provider нь hardware-аас гадна OS, runtime, middleware зэрэг platform-ийг ажиллуулж шинэчилнэ. Хэрэглэгч өөрийн application болон data-г хариуцна.

### Q12 - Хариу: c (`0.18`)

Хоёр 0.9 availability-тэй component parallel байвал `1-(1-0.9)²=0.99`. Series байвал хоёулаа ажиллах ёстой тул `0.9²=0.81`. Зөрүү `0.99-0.81=0.18`.

### Q13 - Хариу: d (`24684`)

Page size 4096 учраас `8300=2×4096+108`; page number 2, offset 108. Page 2 нь frame 6-д map хийсэн тул physical address `6×4096+108=24684`.

### Q14 - Хариу: a (`2.75`)

Process бүрийн arrival, priority, burst time-ийг timeline дээр байрлуулна. Илүү өндөр priority ирэхэд одоогийн process таслагдана. Timeline-аас waiting time бүрийг олж дундажлахад `2.75`.

### Q15 - Хариу: c (`ойролцоогоор 24 ms`)

Нэг pixel 3 byte бөгөөд нийт byte `1024×768×3`. Нэг byte-д 10 ns гэвэл `1024×768×3×10 ns = 23.59 ms`, ойролцоогоор 24 ms.

### Q16 - Хариу: c (Actuator)

Sensor физик орчноос мэдээлэл авдаг бол actuator цахилгаан control signal-ийг хөдөлгөөн, даралт зэрэг физик үйлдэл болгоно.

### Q17 - Хариу: c

Logic gate бүрийн гаралтыг дундаас нь тэмдэглээд Boolean дүрмээр хялбарчилна. NOT, AND, OR-ийн дарааллыг зөв тооцсон илэрхийлэл нь c.

### Q18 - Хариу: c (Confidentiality)

Зөвхөн эрх олгосон хэрэглэгчид мэдээлэл унших access right өгөх нь unauthorized disclosure-оос хамгаална. Энэ нь CIA triad-ийн confidentiality.
## 19-26. Өгөгдлийн сан ба сүлжээ

### Q19 - Хариу: b (Conceptual schema)

Conceptual schema нь entity, attribute, relationship зэрэг database-ийн логик бүтцийг тодорхойлно. Physical file, index зэрэг хадгалалтын нарийн зүйл орохгүй.

### Q20 - Хариу: d

UML association-ийн хоёр үзүүр дээрх `1`, `0..*` зэрэг multiplicity-г тухайн үзүүрийн class-ийн нэг object нөгөө талаас хэдтэй холбогдохоор нь уншина. Диаграмтай зөв таарах нь d.

### Q21 - Хариу: a

Product бүрийн нийлбэрийг олохын тулд `GROUP BY product` хийнэ. Aggregate үр дүнг шүүхдээ `WHERE` биш `HAVING SUM(...) >= 5000` хэрэглэнэ.

### Q22 - Хариу: c

Table зэрэг том granularity-тай lock цөөн lock object шаарддаг ч олон record-ийг зэрэг түгжинэ. Иймээс transaction-уудын зэрэг ажиллах боломж багасаж, wait нэмэгдэнэ.

### Q23 - Хариу: a (Router)

Router нь IP packet-ийн destination IP address-ийг routing table-тай харьцуулж дараагийн hop эсвэл гарах interface-ийг сонгоно.

### Q24 - Хариу: b (Network layer)

IP addressing болон routing нь OSI model-ийн 3-р layer буюу network layer-ийн үндсэн үүрэг.

### Q25 - Хариу: c (ARP)

ARP нь нэг LAN дотор мэдэгдэж байгаа IPv4 address-д тохирох MAC address-ийг broadcast request-ээр олно.

### Q26 - Хариу: c

Эхлээд `ping` ашиглан destination хүрч байгаа эсэхийг шалгана. Хүрэхгүй бол `traceroute` ашиглаж packet аль router буюу hop хүртэл явж байгааг олно.
## 27-33. Мэдээллийн аюулгүй байдал

### Q27 - Хариу: a (DNS cache poisoning)

DNS cache-д жинхэнэ domain-д халдагчийн IP-г хуурамчаар хадгална. Дараа нь хэрэглэгч зөв domain бичсэн ч attacker-ийн server рүү чиглэнэ.

### Q28 - Хариу: b

Application зөвхөн мэдээлэл reference буюу унших шаардлагатай. Least privilege-ийн дагуу read-only permission хангалттай бөгөөд update/delete эрх өгөх хэрэггүй.

### Q29 - Хариу: b (SaaS)

SaaS хэрэглэгч бэлэн application ашигладаг. Тиймээс өөрөө application хөгжүүлэх, storage, log, platform-ийн нарийн design болон maintenance хийх ажил багасна.

### Q30 - Хариу: d

IC card ба PIN-ийг нэг багц эсвэл нэг сувгаар явуулбал замдаа алдагдахад хоёулаа attacker-т очно. Тусдаа сувгаар хүргэвэл энэ эрсдэл багасна.
### Q31 - Хариу: b (Hash)

Файлын анхны hash-ийг найдвартай хадгалж, дараа нь дахин тооцсон hash-тай харьцуулна. Нэг bit өөрчлөгдсөн ч hash ихэвчлэн өөр болох тул integrity шалгаж чадна.

### Q32 - Хариу: b (WAF)

WAF нь HTTP/HTTPS request-ийн URL, header, body-г application layer дээр шалгаж SQL injection, XSS зэрэг web attack pattern-ийг хаана.

### Q33 - Хариу: c (SPF)

Хүлээн авагч нь sender domain-ийн DNS SPF record-оос зөвшөөрөгдсөн mail server IP-уудыг авч, бодит илгээгч IP тэнд байгаа эсэхийг шалгана.
## 34-45. Software engineering, project, service

### Q34 - Хариу: b (Microservices)

Application-ийг тодорхой business capability хариуцсан жижиг, сул холбоостой service-үүдэд хуваана. Service бүрийг тусад нь хөгжүүлж deploy хийж болно.

### Q35 - Хариу: c (Generalization)

Sports car нь automobile-ийн тусгай төрөл, өөрөөр “is-a” холбоо. UML-д ийм inheritance холбоог generalization тэмдэглэгээгээр үзүүлнэ.

### Q36 - Хариу: c (Static analysis)

Static analysis нь program-ийг ажиллуулахгүйгээр source code, control flow, coding rule-ийг шинжилж боломжит bug болон vulnerability олно.

### Q37 - Хариу: d

Multiple-condition coverage-д decision доторх atomic condition бүрийн true/false хослолуудыг test case-аар хамруулах шаардлагатай. Сонголтуудаас шаардлагатай бүх хослолыг d өгнө.

### Q38 - Хариу: b (Integration test)

Unit тус бүрийг тусад нь шалгасны дараа module-уудыг холбоход interface, data exchange, call sequence зөв ажиллаж байгаа эсэхийг integration test шалгана.

### Q39 - Хариу: d (Reverse engineering)

Бэлэн source эсвэл executable system-ийг шинжилж design, specification, architecture зэрэг дээд түвшний мэдээллийг сэргээх үйл явц.

### Q40 - Хариу: b (Sprint)

Scrum-ийн sprint нь тогтмол хугацаатай iteration. Sprint эхэлсний дараа хугацааг дур мэдэн сунгахгүй; төгсгөлд working increment гаргана.

### Q41 - Хариу: a (Earned value)

EV буюу earned value нь тухайн мөч хүртэл бодитоор дууссан ажлыг анхны төсөвт үнээр хэмжсэн дүн. Actual cost биш.

### Q42 - Хариу: a (COCOMO)

COCOMO нь software size, project type зэрэг үзүүлэлтээс person-month effort болон development duration-ийг estimation formula-аар гаргана.

### Q43 - Хариу: b (`2.1 цаг`)

Сарын service time `14×30=420` цаг. Зөвшөөрөх unavailable хувь 0.5% тул `420×0.005=2.1` цаг.

### Q44 - Хариу: d (`RTO < MTD`)

MTD нь business тэсэж болох хамгийн урт тасалдал. RTO нь системийг сэргээх зорилтот хугацаа учраас MTD-д хүрэхээс өмнө буюу `RTO<MTD` байх ёстой.

### Q45 - Хариу: c

Confidential document-д classification, хэн үзэх эрхтэй, хэрхэн хадгалах, дамжуулах, хугацаа дуусахад яаж устгах дүрэм хэрэгтэй. Эдгээрийг хамарсан сонголт c.
## 46-60. Бизнес, менежмент, үйлдвэрлэл

### Q46 - Хариу: d (IT portfolio)

IT project, asset, investment-үүдийг тус тусад нь биш risk, return, strategic value-аар нь нэг portfolio болгон тэнцвэржүүлж удирдана.

### Q47 - Хариу: c (UML)

UML нь system-ийн static structure, behavior, interaction-ийг class, sequence, use case зэрэг өөр diagram-аар стандарт тэмдэглэгээ ашиглан дүрсэлнэ.

### Q48 - Хариу: c (Hybrid cloud)

Private cloud-ийн control болон public cloud-ийн өргөтгөх чадварыг холбоотойгоор хамт ашиглах загвар. Workload эсвэл data хоёр орчны хооронд шилжиж болно.

### Q49 - Хариу: a (Green procurement)

Үнэ, чанараас гадна үйлдвэрлэл, ашиглалт, хаягдлын байгаль орчны нөлөөг харгалзан бүтээгдэхүүн болон нийлүүлэгч сонгоно.

### Q50 - Хариу: d (Growth stage)

Product life cycle-ийн growth үед зах зээл хурдан тэлж, sales өснө. Competitor нэмэгдэх тул distribution channel болон promotion-ийг өргөжүүлдэг.

### Q51 - Хариу: b (Cost-plus pricing)

Нэгжийн эсвэл нийт cost дээр зорьсон profit margin нэмж selling price тогтооно.

### Q52 - Хариу: d (SCM)

Supplier, manufacturer, distributor, retailer, customer хүртэлх material, information, money flow-ийг бүхэлд нь оновчилно.

### Q53 - Хариу: b (Product innovation)

Шинэ эсвэл мэдэгдэхүйц сайжруулсан бүтээгдэхүүн гаргах нь product innovation. Үйлдвэрлэх аргыг сайжруулахыг process innovation гэдэг.

### Q54 - Хариу: b (MRP)

Master production schedule болон bill of materials-аас ямар component хэдийд, хэдэн ширхэг хэрэгтэйг тооцож purchase/production order төлөвлөнө.

### Q55 - Хариу: c (Affiliate marketing)

Affiliate өөрийн referral link-ээр customer оруулна. Purchase зэрэг тодорхой үр дүн гарсан үед advertiser commission төлнө.

### Q56 - Хариу: a

Smart meter нь хэрэглээг хэмжиж хоёр талын communication хийж чадна. Харин auxiliary power өөрөө үүсгэх нь түүний үндсэн function биш.

### Q57 - Хариу: b (Facilitator)

Facilitator нь өөрөө шийдвэр тулгахгүй. Хэлэлцүүлгийг төвийг сахиж удирдан, бүх оролцогчийн санал гаргах нөхцөлийг бүрдүүлнэ.

### Q58 - Хариу: b (Fishbone diagram)

Fishbone буюу cause-and-effect diagram-ийн толгой хэсэгт судалж буй problem/effect A байрлана. Том ба жижиг салаанд боломжит cause B-үүдийг ангилна.

### Q59 - Хариу: d (Process mining)

Information system-ийн timestamp-тай event log-ийг ашиглан бодит process ямар замаар явдаг, хаана bottleneck эсвэл deviation байгааг олно.

### Q60 - Хариу: b (`20,000`)

Straight-line depreciation:

```text
(acquisition cost − residual value) / useful life
=(126,000 − 6,000) / 6
=20,000
```

## Давтах гол сэдэв

- Бит, хоёртын тоо, paging, CPU ба cache-ийн тооцоо
- Өгөгдлийн сан, SQL, transaction, network protocol
- Security control, hash, WAF, SPF
- Software engineering, test, Scrum, project management
- Business strategy, accounting, SCM, MRP
