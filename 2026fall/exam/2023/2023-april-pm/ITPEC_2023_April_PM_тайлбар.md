# ITPEC FE 2023 оны 4-р сарын PM - бүх бодлогын тайлбар

Энэ нь хуучин хэлбэрийн 150 минутын Afternoon шалгалт. Q1, Q6 заавал; Q2-Q5-аас 2; Q7-Q8-аас 1-ийг сонгож, нийт 5 бодлого хариулдаг. Давтахдаа бүх 8 бодлогыг ойлгох нь ашигтай.

Доорх Q1-Q8-ын эх сурвалжийг `(2023S, FE, Afternoon, Qn)` гэж ойлгоно. Асуултыг бүтнээр хуулалгүй, зөв сонголт ба бодох аргыг тайлбарлав.

## Q1. TLS 1.2 connection establishment

**Зөв хариу:** A=b, B=a, C=f, D=e, E=e, F=d.

- **A = CA-ийн private key.** CA server certificate-д digital signature хийхдээ өөрийн private key-г ашиглана. Client CA-ийн public key-ээр signature-г шалгана.
- **B = (2) ServerHello.** ClientHello ба ServerHello дуусахад хоёр тал TLS version, cipher suite зэрэг connection parameter дээр тохирсон байна.
- **C = session key.** Master secret-ээс тухайн session-д ашиглах symmetric encryption key-үүд гарна.
- **D = (6) ClientKeyExchange.** Үүнийг авсны дараа server master secret үүсгэхэд хэрэгтэй client-ийн мэдээлэлтэй болно.
- **E = server-ийн public key.** RSA key exchange-д client premaster secret-ийг server certificate доторх public key-ээр encrypt хийнэ. Зөвхөн server private key-ээр тайлна.
- **F = server-ийн private key.** Энгийн RSA key exchange-д private key алдагдвал өмнө нь бичиж авсан traffic-аас premaster/session key-г сэргээх эрсдэлтэй. DHE-RSA ephemeral secret ашигладаг тул forward secrecy өгч, дараа private key алдагдсан ч хуучин session шууд тайлагдахгүй.

**Гол санаа:** asymmetric cryptography-г authentication ба key exchange-д, хурдан symmetric cryptography-г бодит data encryption-д ашигладаг.

## Q2. File allocation ба inode

### Subquestion 1

**Зөв хариу:** A=b, B=c, C=d (`C1=11`, `C2=11`).

- Linked allocation-д тодорхой хэсэг рүү direct access хийхийн тулд эхний block-оос link бүрийг дагах шаардлагатай. Тиймээс **A=b**.
- Indexed allocation-д жижиг file бүр ч тусдаа index block эзэлж болох тул wasted space ихэснэ. Тиймээс **B=c**.
- Linked allocation-ын нэг block-д 4-byte next pointer орно. Payload нь `4096-4=4092 byte`; `40×1024=40960 byte`, `ceil(40960/4092)=11 block`.
- Indexed allocation-д 40 kB data яг 10 data block, дээр нь 1 index block: нийт 11.

### Subquestion 2

**Зөв хариу:** D=b (`257`), E=a (`ойролцоогоор 16 GB`).

- 1 MB file нь `1 MB / 4 kB = 256` data block. Эхний 12-г inode direct pointer-оор, үлдсэн 244-ийг нэг single-indirect block-оор заана. Иймээс `256 data + 1 index = 257 block`.
- Block 1 kB, pointer 4 byte бол нэг indirect block-д `1024/4=256 pointer`. Triple-indirect capacity дангаараа `256³ × 1 kB = 16 GB`; бусад түвшний хэмжээ харьцангуй бага.

## Q3. DVD shop database ба SQL

### Subquestion 1

**Зөв хариу:** A=g, B=c, C=f.

Зөв query-ийн гол хэсэг:

```sql
SELECT st.StoreID, st.StoreName, SUM(Amount) AS Sales
FROM Payment p
INNER JOIN Staff s ON s.StaffID = p.StaffID
INNER JOIN Store st ON st.StoreID = s.StoreID
GROUP BY st.StoreID, st.StoreName
ORDER BY Sales DESC;
```

`SUM` store бүрийн payment-ийг нийлүүлнэ. `GROUP BY` store-оор бүлэглэж, `DESC` их борлуулалтаас бага руу эрэмбэлнэ.

### Subquestion 2

**Зөв хариу:** D=b.

```sql
(FirstName LIKE 'B%') AND (LastName LIKE 'Gre_n')
```

`B%` нь B-ээр эхэлсэн ямар ч урттай нэр. `Gre_n` нь яг 5 тэмдэгттэй, `Gre`, нэг үл мэдэгдэх тэмдэгт, `n` гэсэн овог.

### Subquestion 3

**Зөв хариу:** E=b.

```sql
AND p.PayDate BETWEEN '2023-04-01' AND '2023-04-15'
GROUP BY c.CustomerID, c.LastName
HAVING COUNT(*) >= 2
```

`WHERE` мөрүүдийг огноогоор шүүнэ. `GROUP BY` customer бүрийн payment-ийг бүлэглэнэ. Aggregate `COUNT(*)`-ийн нөхцөлийг `HAVING`-д бичнэ.

## Q4. VLSM network ба firewall

### Subquestion 1

**Зөв хариу:** A=c, B=d, C=j.

- DMZ нь `172.16.10.240/29`; network address .240, usable range .241-.246. Эхний usable gateway тул **A=`172.16.10.241`**.
- Technology department `172.16.10.0/25` нь .0-.127-г эзэлнэ.
- Sales-д 32 host хэрэгтэй. `/27` зөвхөн 30 usable тул `/26` буюу 62 usable шаардлагатай. Дараагийн aligned network нь **B=`172.16.10.128/26`**.
- Solutions-д 28 host тул `/27` буюу 30 usable хангалттай. Дараагийн network нь **C=`172.16.10.192/27`**.

Үүний дараа Finance `.224/28`, DMZ `.240/29`, server farm `.248/30`, Link A `.252/30` гэж /24 дотор яг багтана.

### Subquestion 2

**Зөв хариу:** D=h, E=d, F=f.

- Rule 3: DMZ-ээс **Internet** рүү гарах traffic-д NAT хэрэгтэй, тиймээс D=the Internet.
- Finance server рүү HTTPS зөвхөн Finance subnet `172.16.10.224/28`-аас зөвшөөрнө, тиймээс E=d.
- Дараагийн rule нь бусад бүх source-ийг хаах ёстой учраас F=ANY.

**Rule order чухал:** permit rule түрүүлж, өргөн deny rule дараа нь байна. Firewall эхний таарсан rule-ийг хэрэгжүүлээд зогсоно.

## Q5. Statistic program testing

**Зөв хариу:** A=d, B=a, C=e, D=c, E=a, F=d.

- **A=South.** Анхны `>` comparison equal утгаар update хийхгүй. 15%-тай анхны city South high city болж үлдэнэ. Low city мөн адил анхны 10%-тай East боловч тэр хэсэг асуултад нуусан байна.
- **B=`????`.** Бүх rate 0 үед `UnempRate > 0.0` хэзээ ч true болохгүй. `CityHigh` initial string хэвээр үлдэнэ.
- Comparison-ыг `>=`, `<=` болгосны дараа equal утга бүр previous city-г солино.
- **C=West.** Бүгд 100% үед low city сүүлийн уншсан West болно.
- **D=North.** Дахин Test case 1 ажиллуулахад 10%-ийн хамгийн сүүлийн city North low city болно. High city нь 15%-ийн хамгийн сүүлийн West.
- Comparison-ыг өөрчлөхгүй зөв ажиллуулах өөр арга нь high initial value-ийг боломжит minimum-ээс бага **E=-0.1**, low initial value-ийг maximum-ээс их **F=100.1** болгох.

**Гол санаа:** boundary value болон equal-value testcase нь initialization, `>`/`>=` ялгааны bug-ийг сайн илрүүлдэг.

## Q6. Dynamic memory allocation linked list

### Subquestion 1

**Зөв хариу:** A=d; B/C=b/f (хооронд нь сольж болно); D=a; E/F=d/f (хооронд нь сольж болно); G=e.

#### `allocate`

- Free node-ийн хэмжээ хүссэн хэмжээтэй яг тэнцвэл link өөрчлөхгүй, `free.state ← procName`; A=d.
- Хэмжээ их бол шинэ allocated node-ийг `last` ба `free` хоёрын дунд оруулна:

```text
last.next ← new
new.prev ← last
new.next ← free
free.prev ← new
```

Тиймээс B/C нь `free.prev ← new` ба `new.prev ← last`; assignment-ийн дараалал хоёр янзаар зөв.
- Үлдсэн free хэмжээ `free.size - reqSize`; D=a.

#### `release`

Эхлээд дараагийн free node-той merge хийнэ. Дараа previous node free бол previous-ийг list-ээс салгаж `proc`-ийг `prev2`-той холбоно:

```text
prev2.next ← proc
proc.prev ← prev2
proc.start ← prev1.start
proc.size ← proc.size + prev1.size
```

Тиймээс E/F=d/f, G=e.

### Subquestion 2

**Зөв хариу:** H=e (case 1 ба case 3).

- Case 1: free node n1 хуваагдаж, өмнө нь new node орно. Sentinel n0-ийн `next` new node руу өөрчлөгдөнө.
- Case 2: n1 яг бүтнээрээ Z болно; зөвхөн state өөрчлөгдөх тул `n0.next` хэвээр.
- Case 3: n2 release хийгээд хоёр талын free хэсэгтэй merge хийнэ. n1 устах тул `n0.next` n2 руу өөрчлөгдөнө.

## Q7. C program - palindrome ба Lychrel process

### Subquestion 1

**Зөв хариу:** A=b, B=c, C=b, D=a, E=d, F=a.

- **A:** character нь `'0'`-оос бага **эсвэл** `'9'`-өөс их бол цифр биш: `str[i] < '0' || str[i] > '9'`.
- **B:** reverse хийхдээ source-ийн төгсгөлөөс эхэлж destination-ийн эхлэл рүү бичнэ: `i=len-1, j=0; i>=0; i--, j++`.
- **C:** palindrome comparison нь `str[i]`-г `str[len-1-i]`-тэй харьцуулна.
- **D:** нийлбэрийн тухайн digit `digit % 10`.
- **E:** carry `digit / 10`-ын бүхэл хэсэг.
- **F:** maximum attempt дотор palindrome болоогүй үед function `-1` буцаадаг.

### Subquestion 2

**Зөв хариу:** G=c, H=d.

- Бүх character 0 бол loop pointer-ийг NUL хүртэл явуулна. Сүүлийн zero руу буцаахын тулд `return str - 1`.
- Leading zero-г in-place арилгахдаа destination нь `strNum`, source нь `skipLeadingZeros(strNum)`. NUL тэмдэгтийг хамт хуулахын тулд length дээр 1 нэмнэ:

```c
memmove(strNum,
        skipLeadingZeros(strNum),
        strlen(skipLeadingZeros(strNum)) + 1);
```

## Q8. Java generic ArrayBag

### Subquestion 1

**Зөв хариу:** A=b, B=h, C=f, D=g, E=c, F=a.

Зөв бүтэц:

```java
public class ArrayBag<T> implements Bag<T> {
    private final T[] bag;

    public int size() {
        return numberOfEntries;
    }

    // Амжилттай нэмэхдээ одоогийн index-д бичээд count өсгөнө.
    bag[numberOfEntries++] = entry;

    // full ба empty шалгалт
    return numberOfEntries >= bag.length;
    return numberOfEntries == 0;
}
```

`numberOfEntries++` нь эхлээд хуучин утгыг index болгон ашиглаад дараа нь count-ийг өсгөнө.

### Subquestion 2

**Зөв хариу:** G=d, H=e.

```java
result = bag[index];
bag[index] = bag[numberOfEntries - 1];
bag[numberOfEntries - 1] = null;
numberOfEntries--;
```

Bag-д order чухал биш тул устгасан position руу сүүлийн element-ийг зөөхөд бусдыг shift хийх шаардлагагүй. Ингэснээр remove ажиллагаа хурдан байна.

## Давтах дараалал

1. Q1-ийн certificate signing, public/private key, session key гурвыг ялгаж сур.
2. Q2-ийн block count-ийг `ceil` ашиглан дахин бод.
3. Q3-ийн `WHERE -> GROUP BY -> HAVING -> ORDER BY` үүргийг цээжил.
4. Q4 дээр required host-оос prefix сонгож, network boundary-г дарааллаар тавь.
5. Q6 дээр linked list-ийн өмнөх/дараах pointer-уудыг цаасан дээр зур.
6. Q7, Q8-ийн code-г blank-гүйгээр өөрөө дахин бичиж үз.
