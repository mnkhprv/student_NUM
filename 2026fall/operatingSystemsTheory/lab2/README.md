# Лабораторийн ажил 2 — Линуксийн цөмийн модуль

## Файлууд

- `simple.c` — энгийн цөмийн модуль.
- `birthday_list.c` — холбоост жагсаалт ашигласан цөмийн модуль.
- `birthday_proc.c` — PDF-д байгаа сайжруулсан `procfs` модуль.
- `Makefile` — гурван модулийг компайл хийж ажиллуулна.

## Компайл хийх

```bash
make
```

Энэ команд гурван модулийг зөвхөн компайл хийнэ. Модуль автоматаар ачаалагдахгүй.

Гурван модулийг компайл хийгээд ажиллуулах:

```bash
make run
```

`make run` нь өмнө ачаалагдсан лабораторийн модулиуд байвал эхлээд устгана. Дараа нь модуль бүрийг ачаалж, `lsmod`-оор шалгаад буцааж устгана. `birthday_proc` модулийн `/proc/birthdays` гаралт болон төгсгөлд цөмийн логийг харуулна.

## `simple` модулийг ажиллуулах

```bash
sudo insmod simple.ko
lsmod | grep simple
dmesg | tail
sudo rmmod simple
dmesg | tail
```

## `birthday_list` модулийг ажиллуулах

```bash
sudo insmod birthday_list.ko
lsmod | grep birthday_list
dmesg | tail -n 10
sudo rmmod birthday_list
dmesg | tail -n 10
```

## `simple.c` тайлбар

`simple_init()` нь модулийг `insmod` командаар ачаалахад ажиллаж, `Loading Module` гэсэн мэдээллийг цөмийн логт бичнэ.

`simple_exit()` нь модулийг `rmmod` командаар устгахад ажиллаж, `Removing Module` гэж бичнэ.

`module_init()` болон `module_exit()` макронууд дээрх хоёр функцийг модулийн эхлэх, дуусах цэг болгон бүртгэнэ.

## `birthday_list.c` тайлбар

`struct birthday` нь өдөр, сар, жил болон жагсаалтын холбоосыг хадгална. `LIST_HEAD(birthday_list)` нь хоосон жагсаалтын толгойг үүсгэнэ.

`birthday_init()` дотор давталтаар 5 ширхэг элементэд `kmalloc()` ашиглан санах ой авна. Элемент бүрд огноо оноож, `list_add_tail()` ашиглан жагсаалтын сүүлд нэмнэ. Дараа нь `list_for_each_entry()` ашиглан жагсаалтыг гүйж бүх огноог цөмийн логт хэвлэнэ.

`birthday_exit()` дотор `list_for_each_entry_safe()` ашиглан бүх элементийг аюулгүй гүйж устгана. `list_del()` нь элементийг жагсаалтаас салгаж, `kfree()` нь авсан санах ойг чөлөөлнө.

## `birthday_proc.c` тайлбар

Энэ нь PDF-д өгсөн сайжруулсан модуль. 2000 оноос өмнөх огноог `*` тэмдгээр ялгаж, жагсаалтыг `/proc/birthdays` файлаар хэрэглэгчийн түвшнээс унших боломжтой болгоно.

Эхний хоёр огноог `list_add()` ашиглан толгойд нэмэх учраас дараалал урвуу болно. Сүүлийн хоёр огноог `list_add_tail()` ашиглан сүүлд нэмэх учраас оруулсан дарааллаараа үлдэнэ.

```bash
sudo insmod birthday_proc.ko
lsmod | grep birthday_proc
cat /proc/birthdays
sudo rmmod birthday_proc
```

## Үүссэн файлуудыг цэвэрлэх

```bash
make clean
```

Логийг гараар харахдаа:

```bash
dmesg | tail -n 40
```
