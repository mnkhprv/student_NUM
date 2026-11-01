# ITPEC FE 2025 оны 10-р сар — Subject B тайлбар

Эх материал: [асуултын PDF](./questions.pdf), [албан ёсны хариу](./answers.pdf), [ITPEC Past Exam](https://www.itpec.org/pastexamqa/fe.html).

## Хариу

`1a 2c 3b 4g 5c 6e 7a 8b 9c 10d 11a 12e 13h 14d 15f 16c 17f 18d 19a 20c`

Энэ шалгалт 20 асуулттай, 100 минут үргэлжилнэ. Q1-Q16 нь algorithm/programming, Q17-Q20 нь information security. Доорх хэсэгт зөв сонголтоос гадна variable хэрхэн өөрчлөгдөх болон буруу сонголтыг яагаад хасахыг тайлбарлав.

## Q1. Тэгш элементүүдийн нийлбэр

**Хариу: a.**

Тэгш тооны үлдэгдэл 2-т хуваахад 0 байдаг. Иймээс `array[i] mod 2 = 0` үед л `s`-д нэмнэ. `i` нь k-ээс m хүртэл өсөх ёстой учраас давталт бүрт `i ← i+1`.

## Q2. Mode олох

**Хариу: c.**

Гадаад loop-ийн `arr[i]`-тай дотоод loop-ийн бүх `arr[j]`-г харьцуулна. Тэнцүү бүрт `c` нэмэгдэнэ. `c` нь өмнөх хамгийн их давтамж `m_c`-ээс их үед шинэ mode утга болон давтамжийг хадгална.

## Q3. Target sum-тай subarray

**Хариу: b.**

Эхлэл `start` бүрийн хувьд төгсгөл `end` нь `start`-аас N хүртэл явна. Тасралтгүй элементүүдийг хуримтлуулах тул `sum ← sum+arr[end]`. Бүх тоо эерэг учраас sum target-аас их бол тухайн эхлэлийн loop-ийг шууд зогсоож болно.

## Q4. Цифрийн дараалал урвуулах

**Хариу: g.**

```text
rm   ← temp mod 10
rev  ← rev×10 + rm
temp ← integer part of (temp/10)
```

`temp>0` байх хооронд сүүлийн цифрийг авч шинэ тооны ард залгана. Жишээ нь `456 → 6 → 65 → 654`.

## Q5. Эхний N prime тоо

**Хариу: c.**

2-оос `√number` хүртэл ямар нэг хуваагч олдвол `isPrime ← false`. Хуваагч олоогүй тохиолдолд number-ийг хэвлээд `count ← count+1`. `count` нь хэвлэсэн prime тоонуудын тоо.

## Q6. Inheritance ба method call

**Хариу: e (`14, 6`).**

`f1` нь Rectangle object `(5,2)`. `f2` нь Cuboid `(9,4,7)` боловч `f1.enlarge(f2)` үед Rectangle-ийн method дуудагдаж length, width хоёрыг л ашиглана:

```text
(5+9, 2+4) = (14,6)
```

## Q7. Singly linked list-ийг recursion-оор урвуулах

**Хариу: a.**

Дараагийн node-оос эхэлсэн жагсаалтыг эхлээд урвуулна: `reverseList(head.next, head)`. Recursion буцахдаа одоогийн node-ийн холбоосыг өмнөх node руу `head.next ← elm` гэж эргүүлнэ.

## Q8. Stack-ийн push ба pop

**Хариу: b.**

Index 1-ээс эхэлдэг тул push үед эхлээд `tos ← tos+1`, дараа нь `stck[tos] ← item`. Pop үед оройн утгаа алдахгүйн тулд эхлээд `item ← stck[tos]`, дараа нь `tos ← tos−1`.

## Q9. Graph-ийн BFS traversal

**Хариу: c (`1,2,4,3,5`).**

Queue ашиглаж байгаа учраас breadth-first search. Trace:

```text
1-ийг гаргана, 2 ба 4-ийг queue-д хийнэ
2-ыг гаргана, 3 ба 5-ыг нэмнэ
4-ийг гаргана, шинэ vertex байхгүй
дараа нь 3, 5
```

Иймээс `1,2,4,3,5`.

## Q10. Singly linked list-д node оруулах

**Хариу: d.**

`x` undefined биш байх хооронд target-ийг хайна. Олсон үед шинэ `y` node хуучин дараагийн node-ийг заах ёстой: `y.next ← x.next`. Дараа нь `x.next ← y` гэж x-ийн ард холбоно.

## Q11. Early-stop bubble sort

**Хариу: a.**

`maxIdx>0` бол шалгах хос үлдсэн. Өмнөх pass-д ядаж нэг swap гарсан бол `exchange=true` тул дахин pass хэрэгтэй. Нэг ч swap гараагүй бол array аль хэдийн эрэмбэлэгдсэн учраас эрт зогсоно.

## Q12. Substring шалгах

**Хариу: e.**

1-based index хэрэглэсэн тул seq-ийн j-р тэмдэг str дотор `i+j−1` байрлалтай таарна. Бүх `seqlen` тэмдэг таарвал j хамгийн сүүлд нэгээр нэмэгдэж `seqlen+1` болно.

## Q13. BST-ээс node устгах

**Хариу: h.**

Устгах node баруун subtree-тэй бол тэндхийн хамгийн бага key-г орлуулна. Иймээс `node2 ← node.right`, дараа нь `node2.left` байгаа хооронд зүүн тийш явна. Олсон `node2.key`-г хуулсны дараа баруун subtree-ээс яг тэр key-г устгана.

## Q14. 3×3 magic square

**Хариу: d.**

Эхлээд хоёр diagonal тэнцүү эсэхийг шалгасан. Дараа нь k бүрийн row ба column sum diagonal sum-тай хоёулаа тэнцүү байх ёстой. Аль нэг нь өөр бол false тул нөхцөл:

```text
(rowSum[k] ≠ colSum[k]) or (rowSum[k] ≠ dia1Sum)
```

## Q15. Inverse document frequency

**Хариу: f.**

`split` хийсний дараа хайх зүйл нь бүтэн document биш `words[j]`. `words[j]=term` болмогц тухайн document term агуулсан гэж тэмдэглээд давталтаас гарна. Document дууссаны дараа `isContainsTerm=true` үед `termCount` нэгээр нэмэгдэнэ.

## Q16. Jaccard similarity

**Хариу: c (`nB`).**

Union-д B-ийн бүх элемент анхнаасаа орсон гэж тооцвол `uCount=nB`. A-ийн элемент бүрийг B-д хайж, байхгүй бол union-д шинээр нэг элемент нэмнэ. Байвал intersection count-ийг нэмнэ. Эцсийн утга `iCount/uCount`.

## Q17. Database устсан incident

**Хариу: f.**

Synchronous mirror нь production database дээрх `DROP TABLE`-ийг шууд mirror талд мөн хэрэгжүүлнэ. Тиймээс mirror руу switch хийхэд устсан data буцаж ирэхгүй; backup-аас сэргээнэ. Дахин гарахаас хамгаалахын тулд junior analyst-д superuser бус, ажилд хэрэгтэй хамгийн бага эрх өгнө.

## Q18. Plugin vulnerability ба patch management

**Хариу: d.**

Бүх component-ийг 3 хоногт test хийх human resource байхгүй. Тиймээс exploitation method нь нийтэд батлагдсан өндөр эрсдэлтэй vulnerability-г нэг долоо хоногийн дотор priority-гаар patch хийнэ. Plugin critical тул шууд disable хийх боломжгүй; patch хүртэл WAF-аар exploit request-ийг шүүнэ.

## Q19. Branch office-оос том файл аюулгүй илгээх

**Хариу: a.**

Том файлыг public-key algorithm-аар бүхэлд нь encrypt хийх нь удаан. Hybrid encryption-д файлыг random symmetric key-ээр хурдан encrypt хийгээд, зөвхөн жижиг key-г recipient Ms. T-ийн public key-ээр encrypt хийнэ. Ms. T private key-ээрээ key-г тайлж чадна.

## Q20. Source code дахь API key

**Хариу: c.**

Environment variable хэрэглэх дүрмийн хажуугаар commit хийхээс өмнө automated secret scanning ажиллуулбал орхигдсон key-г илрүүлнэ. Secret ямар нэг байдлаар алдагдсан ч тогтмол rotation хийвэл хуучин key ашиглагдах хугацаа хязгаарлагдана.

## Давтах гол алгоритм

- Loop trace, divisor, digit processing
- Stack, queue, linked list, BST
- Bubble sort, substring matching
- IDF, Jaccard similarity
- Least privilege, patching, hybrid encryption, secret scanning
