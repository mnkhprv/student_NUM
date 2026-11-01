# ITPEC FE 2026 оны 4-р сарын Subject B - 20 асуултын тайлбар

Subject B нь хуучны PM шалгалтыг орлосон шинэ хэлбэр. 20 асуултыг бүгдийг 100 минутанд хариулна. Үүнээс 16 нь algorithm/programming, 4 нь information security чиглэлтэй.

Доорх Q1-Q20 тайлбарын эх сурвалжийг `(2026S, FE, Subject-B, Qn)` гэж ойлгоно. Асуултыг бүтнээр хуулалгүй, program trace, зөв сонголт, гол логикийг тайлбарлав.

## Q1. Assignment ба array

**Хариу: c (`1, 2`).**

`y←x` тул y=1. `ar[x]←y` гэдэг нь `ar[1]=1`. Дараа z=1, x=1. Эцэст нь `ar[2]←z+ar[1]=1+1=2`. Output `1, 2`.

## Q2. Grade function-ийн specification bug

**Хариу: d (`b, b, d`).**

- `f(92)`: эхний if `a` болгоно. Гэхдээ дараагийн if бас true тул дахин `b` болгон дарна.
- `f(72)`: хоёр дахь if true, `b`.
- `f(-10)`: `≤60` тул `d`.

Bug нь эхний if дараагийн if-ээс тусдаа байгаа явдал. Нэг `if-elseif` chain болгох ёстой.

## Q3. Manhattan distance

**Хариу: b.**

Manhattan distance нь coordinate бүрийн зөрүүний absolute value-ийг нийлүүлдэг:

```text
p ← p + abs(S[i] - T[i])
```

## Q4. Harshad number

**Хариу: f.**

Сүүлийн цифрийг `num mod 10`-аар sum-д нэмнэ. Дараа нь `num`-ийг `integer part of (num/10)` болгож сүүлийн цифрийг хасна. Эцэст нь анхны `n mod sum = 0` бол Harshad number.

## Q5. Procedure call order

**Хариу: e (`B, C, C, A`).**

`proc1` эхлээд `proc2` дуудна. `proc2` B хэвлээд `proc3`-аар C хэвлэнэ. `proc1` рүү буцаад `proc3` дахин C, эцэст A хэвлэнэ.

## Q6. Quadratic equation

**Хариу: d.**

Хувиргасан equation нь `x²-2bx+c=0`. `val=b²-c`.

- `val=0` үед double root нь `b`.
- `val<0` үед imaginary хэсгийн хэмжээ `sqrt(-val)`.

Тиймээс A=`b`, B=`sqrt(-val)`.

## Q7. Recursive linear search

**Хариу: d.**

Одоогийн `D[index]` search key-тэй тэнцвэл `index`-ийг буцаана. Тэнцэхгүй бол массивыг араас нь урагш шалгахын тулд `recursive(searchKey, index-1)` дуудна.

## Q8. Circular queue

**Хариу: e.**

Queue full биш нөхцөл `count < capacity`. Dequeue хийсний дараа front дараагийн circular position руу шилжинэ:

```text
front ← (front + 1) mod capacity
```

`mod` ашигласнаар сүүлийн index-ийн дараа 0 руу буцна.

## Q9. Perfect binary tree

**Хариу: b.**

Height нь root-ийг оролцуулсан level-ийн тоо гэж өгөгдсөн. Perfect tree-ийн node count `2^height - 1`, өөрөөр `size+1=2^height`. `getSize` нь left size + right size + root өөрөө:

```text
getSize(root.left) + getSize(root.right) + 1
```

## Q10. Sorted linked list merge

**Хариу: c.**

Хоёр head-ийн бага утгатайг result болгоно. `head1.val ≤ head2.val` бол head1-г аваад үлдсэн `head1.next`-ийг head2-той recursive merge хийнэ. Else үед head2-г аваад head1-ийг `head2.next`-тэй merge хийнэ.

```text
A: head1.val ≤ head2.val
B: head1.next
C: head2.next
```

## Q11. Counting sort

**Хариу: d.**

Одоогийн key k хэдэн удаа гарсныг `count[k]` хадгална. `count[k]>0` үед k-г тэр тоогоор result-д бичиж, бичих бүрдээ `i←i+1`.

## Q12. Isomorphic strings

**Хариу: d.**

Mapping consistent, one-to-one байх ёстой:

- `s1[i]=s1[j]` атлаа `s2[i]≠s2[j]` бол нэг source character хоёр target руу mapping хийсэн - false.
- `s1[i]≠s1[j]` атлаа `s2[i]=s2[j]` бол хоёр source character нэг target руу mapping хийсэн - false.

Тиймээс A=`s2[i]≠s2[j]`, B=`s2[i]=s2[j]`.

## Q13. Email extraction

**Хариу: a.**

`@`-ийн зүүн талын name-г авахын тулд `atIndex-1`-ээс өмнөх search start `index` хүртэл буурч явна:

```text
decrease i from atIndex - 1 to index by 1
```

Character бүрийг candidate-ийн урд prepend хийдэг учраас name зөв дарааллаар үүснэ. Дараагийн search-ийг өмнөх `@`-ийн дараа эхлүүлснээр `a@b@c`-ээс `a@b`, `b@c` хоёрыг олно.

## Q14. Percentile

**Хариу: f.**

Student i-ийн score-оос доогуур бүх score-ийг тоолох тул inner loop бүх `n` element-ийг шалгана. Formula:

```text
percentiles[i] ← (count / (n-1)) × 100
```

Өөрийн score өөрөөсөө бага биш тул өөрийгөө count-д нэмэхгүй.

## Q15. Bag of Words

**Хариу: i.**

Word order: `{He, is, a, an, good, boy, honest, the}`.

- document III: `He1, is2, a1, an1, good2, boy2, honest1, the0`  
  `{1,2,1,1,2,2,1,0}`
- document IV: `He1, is2, a0, an1, good1, boy2, honest2, the1`  
  `{1,2,0,1,1,2,2,1}`

Bag of Words нь үгийн дарааллыг хадгалахгүй, зөвхөн давтамжийг хадгална.

## Q16. Two-byte UTF-8 encoding

**Хариу: c (`64`).**

UTF-8 хоёр дахь byte-ийн `10xxxxxx` хэсэгт code point-ийн доод 6 bit орно. Доод 6 bit=`codePoint mod 64`; үлдсэн дээд bit=`integer part of codePoint/64`. Иймээс хоёр blank хоёулаа 64.

## Q17. Password attack log patterns

**Хариу: a.**

- Pattern A: нэг `admin` account дээр олон өөр password оролдож, бүгд fail - **brute force attack**.
- Pattern B: олон өөр account дээр оролдож, зарим нь success - алдагдсан username/password pair ашигласан **credential stuffing**.

Offline cracking нь authentication server-т request илгээдэггүй тул ийм login log үүсгэхгүй.

## Q18. Least privilege access control

**Хариу: c.**

- Research Proposals: Professor ба Researcher create/edit тул RW; Student зөвхөн view тул R; Admin no access.
- Experimental Data: зөвхөн Researcher create/modify тул RW; Professor, Student review тул R; Admin no access.

Энэ нь хэрэглэгч бүрт ажилдаа хэрэгтэй хамгийн бага permission өгөх least privilege зарчим.

## Q19. SQL injection authentication bypass

**Хариу: c (`Success, Fail`).**

- `admin' --` оруулахад username condition `admin` болж, `--`-оос хойших password check comment болно. Admin record байвал authentication **success**.
- `admin' AND '1'='2' --` нь үргэлж false condition нэмдэг. Тиймээс record гарахгүй, authentication **fail**.

Хамгаалалт: user input-ийг query string-т залгахгүй, parameterized query/prepared statement ашиглана.

## Q20. Mobile app-ийн access token architecture

**Хариу: c (Architecture Three).**

API server access token-ийг server талд хадгална. Mobile app cloud storage token огт эзэмшихгүй; зөвхөн API server-тэй HTTPS-ээр харилцана. Server authentication, authorization, business logic-ийг хэрэгжүүлээд client-ийн өмнөөс storage API дуудна.

- Architecture One-д mobile app temporary token авдаг тул token client дээр ил гарч болно.
- Architecture Two-ийн VPN нь communication-г хамгаалсан ч app доторх token extraction-ийг шийдэхгүй.
- Architecture Four token-ийг proxy-д хадгалсан ч application-specific authentication/authorization хийхгүй тул дурын request relay хийх эрсдэлтэй.

## Шалгалтад бодох арга

1. Code-г толгойдоо биш, variable/value table зурж trace хий.
2. Array index 0-оос уу, 1-ээс үү гэдгийг эхлээд тэмдэглэ.
3. Recursive function бүрт base case болон дараагийн argument хэрхэн багасаж байгааг ол.
4. Linked list, tree, queue дээр жижиг зураг зур.
5. Security асуултад asset хаана хадгалагдаж, хэн permission авч, attacker юу харж чадахыг дарааллаар шалга.
