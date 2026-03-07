
bomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 3f 00 00 	mov    0x3fd9(%rip),%rax        # 4fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 ba 3e 00 00    	push   0x3eba(%rip)        # 4ee0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 bc 3e 00 00    	jmp    *0x3ebc(%rip)        # 4ee8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   $0x0
    1039:	e9 e2 ff ff ff       	jmp    1020 <_init+0x20>
    103e:	66 90                	xchg   %ax,%ax
    1040:	f3 0f 1e fa          	endbr64
    1044:	68 01 00 00 00       	push   $0x1
    1049:	e9 d2 ff ff ff       	jmp    1020 <_init+0x20>
    104e:	66 90                	xchg   %ax,%ax
    1050:	f3 0f 1e fa          	endbr64
    1054:	68 02 00 00 00       	push   $0x2
    1059:	e9 c2 ff ff ff       	jmp    1020 <_init+0x20>
    105e:	66 90                	xchg   %ax,%ax
    1060:	f3 0f 1e fa          	endbr64
    1064:	68 03 00 00 00       	push   $0x3
    1069:	e9 b2 ff ff ff       	jmp    1020 <_init+0x20>
    106e:	66 90                	xchg   %ax,%ax
    1070:	f3 0f 1e fa          	endbr64
    1074:	68 04 00 00 00       	push   $0x4
    1079:	e9 a2 ff ff ff       	jmp    1020 <_init+0x20>
    107e:	66 90                	xchg   %ax,%ax
    1080:	f3 0f 1e fa          	endbr64
    1084:	68 05 00 00 00       	push   $0x5
    1089:	e9 92 ff ff ff       	jmp    1020 <_init+0x20>
    108e:	66 90                	xchg   %ax,%ax
    1090:	f3 0f 1e fa          	endbr64
    1094:	68 06 00 00 00       	push   $0x6
    1099:	e9 82 ff ff ff       	jmp    1020 <_init+0x20>
    109e:	66 90                	xchg   %ax,%ax
    10a0:	f3 0f 1e fa          	endbr64
    10a4:	68 07 00 00 00       	push   $0x7
    10a9:	e9 72 ff ff ff       	jmp    1020 <_init+0x20>
    10ae:	66 90                	xchg   %ax,%ax
    10b0:	f3 0f 1e fa          	endbr64
    10b4:	68 08 00 00 00       	push   $0x8
    10b9:	e9 62 ff ff ff       	jmp    1020 <_init+0x20>
    10be:	66 90                	xchg   %ax,%ax
    10c0:	f3 0f 1e fa          	endbr64
    10c4:	68 09 00 00 00       	push   $0x9
    10c9:	e9 52 ff ff ff       	jmp    1020 <_init+0x20>
    10ce:	66 90                	xchg   %ax,%ax
    10d0:	f3 0f 1e fa          	endbr64
    10d4:	68 0a 00 00 00       	push   $0xa
    10d9:	e9 42 ff ff ff       	jmp    1020 <_init+0x20>
    10de:	66 90                	xchg   %ax,%ax
    10e0:	f3 0f 1e fa          	endbr64
    10e4:	68 0b 00 00 00       	push   $0xb
    10e9:	e9 32 ff ff ff       	jmp    1020 <_init+0x20>
    10ee:	66 90                	xchg   %ax,%ax
    10f0:	f3 0f 1e fa          	endbr64
    10f4:	68 0c 00 00 00       	push   $0xc
    10f9:	e9 22 ff ff ff       	jmp    1020 <_init+0x20>
    10fe:	66 90                	xchg   %ax,%ax
    1100:	f3 0f 1e fa          	endbr64
    1104:	68 0d 00 00 00       	push   $0xd
    1109:	e9 12 ff ff ff       	jmp    1020 <_init+0x20>
    110e:	66 90                	xchg   %ax,%ax
    1110:	f3 0f 1e fa          	endbr64
    1114:	68 0e 00 00 00       	push   $0xe
    1119:	e9 02 ff ff ff       	jmp    1020 <_init+0x20>
    111e:	66 90                	xchg   %ax,%ax
    1120:	f3 0f 1e fa          	endbr64
    1124:	68 0f 00 00 00       	push   $0xf
    1129:	e9 f2 fe ff ff       	jmp    1020 <_init+0x20>
    112e:	66 90                	xchg   %ax,%ax
    1130:	f3 0f 1e fa          	endbr64
    1134:	68 10 00 00 00       	push   $0x10
    1139:	e9 e2 fe ff ff       	jmp    1020 <_init+0x20>
    113e:	66 90                	xchg   %ax,%ax
    1140:	f3 0f 1e fa          	endbr64
    1144:	68 11 00 00 00       	push   $0x11
    1149:	e9 d2 fe ff ff       	jmp    1020 <_init+0x20>
    114e:	66 90                	xchg   %ax,%ax
    1150:	f3 0f 1e fa          	endbr64
    1154:	68 12 00 00 00       	push   $0x12
    1159:	e9 c2 fe ff ff       	jmp    1020 <_init+0x20>
    115e:	66 90                	xchg   %ax,%ax
    1160:	f3 0f 1e fa          	endbr64
    1164:	68 13 00 00 00       	push   $0x13
    1169:	e9 b2 fe ff ff       	jmp    1020 <_init+0x20>
    116e:	66 90                	xchg   %ax,%ax
    1170:	f3 0f 1e fa          	endbr64
    1174:	68 14 00 00 00       	push   $0x14
    1179:	e9 a2 fe ff ff       	jmp    1020 <_init+0x20>
    117e:	66 90                	xchg   %ax,%ax
    1180:	f3 0f 1e fa          	endbr64
    1184:	68 15 00 00 00       	push   $0x15
    1189:	e9 92 fe ff ff       	jmp    1020 <_init+0x20>
    118e:	66 90                	xchg   %ax,%ax
    1190:	f3 0f 1e fa          	endbr64
    1194:	68 16 00 00 00       	push   $0x16
    1199:	e9 82 fe ff ff       	jmp    1020 <_init+0x20>
    119e:	66 90                	xchg   %ax,%ax
    11a0:	f3 0f 1e fa          	endbr64
    11a4:	68 17 00 00 00       	push   $0x17
    11a9:	e9 72 fe ff ff       	jmp    1020 <_init+0x20>
    11ae:	66 90                	xchg   %ax,%ax
    11b0:	f3 0f 1e fa          	endbr64
    11b4:	68 18 00 00 00       	push   $0x18
    11b9:	e9 62 fe ff ff       	jmp    1020 <_init+0x20>
    11be:	66 90                	xchg   %ax,%ax
    11c0:	f3 0f 1e fa          	endbr64
    11c4:	68 19 00 00 00       	push   $0x19
    11c9:	e9 52 fe ff ff       	jmp    1020 <_init+0x20>
    11ce:	66 90                	xchg   %ax,%ax
    11d0:	f3 0f 1e fa          	endbr64
    11d4:	68 1a 00 00 00       	push   $0x1a
    11d9:	e9 42 fe ff ff       	jmp    1020 <_init+0x20>
    11de:	66 90                	xchg   %ax,%ax
    11e0:	f3 0f 1e fa          	endbr64
    11e4:	68 1b 00 00 00       	push   $0x1b
    11e9:	e9 32 fe ff ff       	jmp    1020 <_init+0x20>
    11ee:	66 90                	xchg   %ax,%ax
    11f0:	f3 0f 1e fa          	endbr64
    11f4:	68 1c 00 00 00       	push   $0x1c
    11f9:	e9 22 fe ff ff       	jmp    1020 <_init+0x20>
    11fe:	66 90                	xchg   %ax,%ax

Disassembly of section .plt.got:

0000000000001200 <__cxa_finalize@plt>:
    1200:	f3 0f 1e fa          	endbr64
    1204:	ff 25 ee 3d 00 00    	jmp    *0x3dee(%rip)        # 4ff8 <__cxa_finalize@GLIBC_2.2.5>
    120a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001210 <getenv@plt>:
    1210:	f3 0f 1e fa          	endbr64
    1214:	ff 25 d6 3c 00 00    	jmp    *0x3cd6(%rip)        # 4ef0 <getenv@GLIBC_2.2.5>
    121a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001220 <__errno_location@plt>:
    1220:	f3 0f 1e fa          	endbr64
    1224:	ff 25 ce 3c 00 00    	jmp    *0x3cce(%rip)        # 4ef8 <__errno_location@GLIBC_2.2.5>
    122a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001230 <strcpy@plt>:
    1230:	f3 0f 1e fa          	endbr64
    1234:	ff 25 c6 3c 00 00    	jmp    *0x3cc6(%rip)        # 4f00 <strcpy@GLIBC_2.2.5>
    123a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001240 <puts@plt>:
    1240:	f3 0f 1e fa          	endbr64
    1244:	ff 25 be 3c 00 00    	jmp    *0x3cbe(%rip)        # 4f08 <puts@GLIBC_2.2.5>
    124a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001250 <write@plt>:
    1250:	f3 0f 1e fa          	endbr64
    1254:	ff 25 b6 3c 00 00    	jmp    *0x3cb6(%rip)        # 4f10 <write@GLIBC_2.2.5>
    125a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001260 <strlen@plt>:
    1260:	f3 0f 1e fa          	endbr64
    1264:	ff 25 ae 3c 00 00    	jmp    *0x3cae(%rip)        # 4f18 <strlen@GLIBC_2.2.5>
    126a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001270 <__stack_chk_fail@plt>:
    1270:	f3 0f 1e fa          	endbr64
    1274:	ff 25 a6 3c 00 00    	jmp    *0x3ca6(%rip)        # 4f20 <__stack_chk_fail@GLIBC_2.4>
    127a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001280 <alarm@plt>:
    1280:	f3 0f 1e fa          	endbr64
    1284:	ff 25 9e 3c 00 00    	jmp    *0x3c9e(%rip)        # 4f28 <alarm@GLIBC_2.2.5>
    128a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001290 <close@plt>:
    1290:	f3 0f 1e fa          	endbr64
    1294:	ff 25 96 3c 00 00    	jmp    *0x3c96(%rip)        # 4f30 <close@GLIBC_2.2.5>
    129a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012a0 <read@plt>:
    12a0:	f3 0f 1e fa          	endbr64
    12a4:	ff 25 8e 3c 00 00    	jmp    *0x3c8e(%rip)        # 4f38 <read@GLIBC_2.2.5>
    12aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012b0 <strcmp@plt>:
    12b0:	f3 0f 1e fa          	endbr64
    12b4:	ff 25 86 3c 00 00    	jmp    *0x3c86(%rip)        # 4f40 <strcmp@GLIBC_2.2.5>
    12ba:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012c0 <signal@plt>:
    12c0:	f3 0f 1e fa          	endbr64
    12c4:	ff 25 7e 3c 00 00    	jmp    *0x3c7e(%rip)        # 4f48 <signal@GLIBC_2.2.5>
    12ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012d0 <gethostbyname@plt>:
    12d0:	f3 0f 1e fa          	endbr64
    12d4:	ff 25 76 3c 00 00    	jmp    *0x3c76(%rip)        # 4f50 <gethostbyname@GLIBC_2.2.5>
    12da:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012e0 <__memmove_chk@plt>:
    12e0:	f3 0f 1e fa          	endbr64
    12e4:	ff 25 6e 3c 00 00    	jmp    *0x3c6e(%rip)        # 4f58 <__memmove_chk@GLIBC_2.3.4>
    12ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012f0 <__memcpy_chk@plt>:
    12f0:	f3 0f 1e fa          	endbr64
    12f4:	ff 25 66 3c 00 00    	jmp    *0x3c66(%rip)        # 4f60 <__memcpy_chk@GLIBC_2.3.4>
    12fa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001300 <strtol@plt>:
    1300:	f3 0f 1e fa          	endbr64
    1304:	ff 25 5e 3c 00 00    	jmp    *0x3c5e(%rip)        # 4f68 <strtol@GLIBC_2.2.5>
    130a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001310 <fflush@plt>:
    1310:	f3 0f 1e fa          	endbr64
    1314:	ff 25 56 3c 00 00    	jmp    *0x3c56(%rip)        # 4f70 <fflush@GLIBC_2.2.5>
    131a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001320 <__isoc99_sscanf@plt>:
    1320:	f3 0f 1e fa          	endbr64
    1324:	ff 25 4e 3c 00 00    	jmp    *0x3c4e(%rip)        # 4f78 <__isoc99_sscanf@GLIBC_2.7>
    132a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001330 <__fgets_chk@plt>:
    1330:	f3 0f 1e fa          	endbr64
    1334:	ff 25 46 3c 00 00    	jmp    *0x3c46(%rip)        # 4f80 <__fgets_chk@GLIBC_2.4>
    133a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001340 <__printf_chk@plt>:
    1340:	f3 0f 1e fa          	endbr64
    1344:	ff 25 3e 3c 00 00    	jmp    *0x3c3e(%rip)        # 4f88 <__printf_chk@GLIBC_2.3.4>
    134a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001350 <fopen@plt>:
    1350:	f3 0f 1e fa          	endbr64
    1354:	ff 25 36 3c 00 00    	jmp    *0x3c36(%rip)        # 4f90 <fopen@GLIBC_2.2.5>
    135a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001360 <gethostname@plt>:
    1360:	f3 0f 1e fa          	endbr64
    1364:	ff 25 2e 3c 00 00    	jmp    *0x3c2e(%rip)        # 4f98 <gethostname@GLIBC_2.2.5>
    136a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001370 <exit@plt>:
    1370:	f3 0f 1e fa          	endbr64
    1374:	ff 25 26 3c 00 00    	jmp    *0x3c26(%rip)        # 4fa0 <exit@GLIBC_2.2.5>
    137a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001380 <connect@plt>:
    1380:	f3 0f 1e fa          	endbr64
    1384:	ff 25 1e 3c 00 00    	jmp    *0x3c1e(%rip)        # 4fa8 <connect@GLIBC_2.2.5>
    138a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001390 <__fprintf_chk@plt>:
    1390:	f3 0f 1e fa          	endbr64
    1394:	ff 25 16 3c 00 00    	jmp    *0x3c16(%rip)        # 4fb0 <__fprintf_chk@GLIBC_2.3.4>
    139a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000013a0 <sleep@plt>:
    13a0:	f3 0f 1e fa          	endbr64
    13a4:	ff 25 0e 3c 00 00    	jmp    *0x3c0e(%rip)        # 4fb8 <sleep@GLIBC_2.2.5>
    13aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000013b0 <__ctype_b_loc@plt>:
    13b0:	f3 0f 1e fa          	endbr64
    13b4:	ff 25 06 3c 00 00    	jmp    *0x3c06(%rip)        # 4fc0 <__ctype_b_loc@GLIBC_2.3>
    13ba:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000013c0 <__sprintf_chk@plt>:
    13c0:	f3 0f 1e fa          	endbr64
    13c4:	ff 25 fe 3b 00 00    	jmp    *0x3bfe(%rip)        # 4fc8 <__sprintf_chk@GLIBC_2.3.4>
    13ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000013d0 <socket@plt>:
    13d0:	f3 0f 1e fa          	endbr64
    13d4:	ff 25 f6 3b 00 00    	jmp    *0x3bf6(%rip)        # 4fd0 <socket@GLIBC_2.2.5>
    13da:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000013e0 <_start>:
    13e0:	f3 0f 1e fa          	endbr64
    13e4:	31 ed                	xor    %ebp,%ebp
    13e6:	49 89 d1             	mov    %rdx,%r9
    13e9:	5e                   	pop    %rsi
    13ea:	48 89 e2             	mov    %rsp,%rdx
    13ed:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    13f1:	50                   	push   %rax
    13f2:	54                   	push   %rsp
    13f3:	45 31 c0             	xor    %r8d,%r8d
    13f6:	31 c9                	xor    %ecx,%ecx
    13f8:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 14c9 <main>
    13ff:	ff 15 d3 3b 00 00    	call   *0x3bd3(%rip)        # 4fd8 <__libc_start_main@GLIBC_2.34>
    1405:	f4                   	hlt
    1406:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    140d:	00 00 00 

0000000000001410 <deregister_tm_clones>:
    1410:	48 8d 3d 69 3e 00 00 	lea    0x3e69(%rip),%rdi        # 5280 <stdout@GLIBC_2.2.5>
    1417:	48 8d 05 62 3e 00 00 	lea    0x3e62(%rip),%rax        # 5280 <stdout@GLIBC_2.2.5>
    141e:	48 39 f8             	cmp    %rdi,%rax
    1421:	74 15                	je     1438 <deregister_tm_clones+0x28>
    1423:	48 8b 05 b6 3b 00 00 	mov    0x3bb6(%rip),%rax        # 4fe0 <_ITM_deregisterTMCloneTable@Base>
    142a:	48 85 c0             	test   %rax,%rax
    142d:	74 09                	je     1438 <deregister_tm_clones+0x28>
    142f:	ff e0                	jmp    *%rax
    1431:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1438:	c3                   	ret
    1439:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001440 <register_tm_clones>:
    1440:	48 8d 3d 39 3e 00 00 	lea    0x3e39(%rip),%rdi        # 5280 <stdout@GLIBC_2.2.5>
    1447:	48 8d 35 32 3e 00 00 	lea    0x3e32(%rip),%rsi        # 5280 <stdout@GLIBC_2.2.5>
    144e:	48 29 fe             	sub    %rdi,%rsi
    1451:	48 89 f0             	mov    %rsi,%rax
    1454:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1458:	48 c1 f8 03          	sar    $0x3,%rax
    145c:	48 01 c6             	add    %rax,%rsi
    145f:	48 d1 fe             	sar    $1,%rsi
    1462:	74 14                	je     1478 <register_tm_clones+0x38>
    1464:	48 8b 05 85 3b 00 00 	mov    0x3b85(%rip),%rax        # 4ff0 <_ITM_registerTMCloneTable@Base>
    146b:	48 85 c0             	test   %rax,%rax
    146e:	74 08                	je     1478 <register_tm_clones+0x38>
    1470:	ff e0                	jmp    *%rax
    1472:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1478:	c3                   	ret
    1479:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001480 <__do_global_dtors_aux>:
    1480:	f3 0f 1e fa          	endbr64
    1484:	80 3d 1d 3e 00 00 00 	cmpb   $0x0,0x3e1d(%rip)        # 52a8 <completed.0>
    148b:	75 2b                	jne    14b8 <__do_global_dtors_aux+0x38>
    148d:	55                   	push   %rbp
    148e:	48 83 3d 62 3b 00 00 	cmpq   $0x0,0x3b62(%rip)        # 4ff8 <__cxa_finalize@GLIBC_2.2.5>
    1495:	00 
    1496:	48 89 e5             	mov    %rsp,%rbp
    1499:	74 0c                	je     14a7 <__do_global_dtors_aux+0x27>
    149b:	48 8b 3d 66 3b 00 00 	mov    0x3b66(%rip),%rdi        # 5008 <__dso_handle>
    14a2:	e8 59 fd ff ff       	call   1200 <__cxa_finalize@plt>
    14a7:	e8 64 ff ff ff       	call   1410 <deregister_tm_clones>
    14ac:	c6 05 f5 3d 00 00 01 	movb   $0x1,0x3df5(%rip)        # 52a8 <completed.0>
    14b3:	5d                   	pop    %rbp
    14b4:	c3                   	ret
    14b5:	0f 1f 00             	nopl   (%rax)
    14b8:	c3                   	ret
    14b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000014c0 <frame_dummy>:
    14c0:	f3 0f 1e fa          	endbr64
    14c4:	e9 77 ff ff ff       	jmp    1440 <register_tm_clones>

00000000000014c9 <main>:
    14c9:	f3 0f 1e fa          	endbr64
    14cd:	53                   	push   %rbx
    14ce:	83 ff 01             	cmp    $0x1,%edi
    14d1:	0f 84 f8 00 00 00    	je     15cf <main+0x106>
    14d7:	48 89 f3             	mov    %rsi,%rbx
    14da:	83 ff 02             	cmp    $0x2,%edi
    14dd:	0f 85 21 01 00 00    	jne    1604 <main+0x13b>
    14e3:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
    14e7:	48 8d 35 16 1b 00 00 	lea    0x1b16(%rip),%rsi        # 3004 <_IO_stdin_used+0x4>
    14ee:	e8 5d fe ff ff       	call   1350 <fopen@plt>
    14f3:	48 89 05 b6 3d 00 00 	mov    %rax,0x3db6(%rip)        # 52b0 <infile>
    14fa:	48 85 c0             	test   %rax,%rax
    14fd:	0f 84 df 00 00 00    	je     15e2 <main+0x119>
    1503:	e8 e8 06 00 00       	call   1bf0 <initialize_bomb>
    1508:	48 8d 3d d1 1c 00 00 	lea    0x1cd1(%rip),%rdi        # 31e0 <_IO_stdin_used+0x1e0>
    150f:	e8 2c fd ff ff       	call   1240 <puts@plt>
    1514:	48 8d 3d 05 1d 00 00 	lea    0x1d05(%rip),%rdi        # 3220 <_IO_stdin_used+0x220>
    151b:	e8 20 fd ff ff       	call   1240 <puts@plt>
    1520:	e8 a7 09 00 00       	call   1ecc <read_line>
    1525:	48 89 c7             	mov    %rax,%rdi
    1528:	e8 fa 00 00 00       	call   1627 <phase_1>
    152d:	e8 dc 0a 00 00       	call   200e <phase_defused>
    1532:	48 8d 3d 17 1d 00 00 	lea    0x1d17(%rip),%rdi        # 3250 <_IO_stdin_used+0x250>
    1539:	e8 02 fd ff ff       	call   1240 <puts@plt>
    153e:	e8 89 09 00 00       	call   1ecc <read_line>
    1543:	48 89 c7             	mov    %rax,%rdi
    1546:	e8 00 01 00 00       	call   164b <phase_2>
    154b:	e8 be 0a 00 00       	call   200e <phase_defused>
    1550:	48 8d 3d e6 1a 00 00 	lea    0x1ae6(%rip),%rdi        # 303d <_IO_stdin_used+0x3d>
    1557:	e8 e4 fc ff ff       	call   1240 <puts@plt>
    155c:	e8 6b 09 00 00       	call   1ecc <read_line>
    1561:	48 89 c7             	mov    %rax,%rdi
    1564:	e8 50 01 00 00       	call   16b9 <phase_3>
    1569:	e8 a0 0a 00 00       	call   200e <phase_defused>
    156e:	48 8d 3d e6 1a 00 00 	lea    0x1ae6(%rip),%rdi        # 305b <_IO_stdin_used+0x5b>
    1575:	e8 c6 fc ff ff       	call   1240 <puts@plt>
    157a:	e8 4d 09 00 00       	call   1ecc <read_line>
    157f:	48 89 c7             	mov    %rax,%rdi
    1582:	e8 28 02 00 00       	call   17af <phase_4>
    1587:	e8 82 0a 00 00       	call   200e <phase_defused>
    158c:	48 8d 3d ed 1c 00 00 	lea    0x1ced(%rip),%rdi        # 3280 <_IO_stdin_used+0x280>
    1593:	e8 a8 fc ff ff       	call   1240 <puts@plt>
    1598:	e8 2f 09 00 00       	call   1ecc <read_line>
    159d:	48 89 c7             	mov    %rax,%rdi
    15a0:	e8 7f 02 00 00       	call   1824 <phase_5>
    15a5:	e8 64 0a 00 00       	call   200e <phase_defused>
    15aa:	48 8d 3d b9 1a 00 00 	lea    0x1ab9(%rip),%rdi        # 306a <_IO_stdin_used+0x6a>
    15b1:	e8 8a fc ff ff       	call   1240 <puts@plt>
    15b6:	e8 11 09 00 00       	call   1ecc <read_line>
    15bb:	48 89 c7             	mov    %rax,%rdi
    15be:	e8 f8 02 00 00       	call   18bb <phase_6>
    15c3:	e8 46 0a 00 00       	call   200e <phase_defused>
    15c8:	b8 00 00 00 00       	mov    $0x0,%eax
    15cd:	5b                   	pop    %rbx
    15ce:	c3                   	ret
    15cf:	48 8b 05 ba 3c 00 00 	mov    0x3cba(%rip),%rax        # 5290 <stdin@GLIBC_2.2.5>
    15d6:	48 89 05 d3 3c 00 00 	mov    %rax,0x3cd3(%rip)        # 52b0 <infile>
    15dd:	e9 21 ff ff ff       	jmp    1503 <main+0x3a>
    15e2:	48 8b 4b 08          	mov    0x8(%rbx),%rcx
    15e6:	48 8b 13             	mov    (%rbx),%rdx
    15e9:	48 8d 35 16 1a 00 00 	lea    0x1a16(%rip),%rsi        # 3006 <_IO_stdin_used+0x6>
    15f0:	bf 02 00 00 00       	mov    $0x2,%edi
    15f5:	e8 46 fd ff ff       	call   1340 <__printf_chk@plt>
    15fa:	bf 08 00 00 00       	mov    $0x8,%edi
    15ff:	e8 6c fd ff ff       	call   1370 <exit@plt>
    1604:	48 8b 16             	mov    (%rsi),%rdx
    1607:	48 8d 35 15 1a 00 00 	lea    0x1a15(%rip),%rsi        # 3023 <_IO_stdin_used+0x23>
    160e:	bf 02 00 00 00       	mov    $0x2,%edi
    1613:	b8 00 00 00 00       	mov    $0x0,%eax
    1618:	e8 23 fd ff ff       	call   1340 <__printf_chk@plt>
    161d:	bf 08 00 00 00       	mov    $0x8,%edi
    1622:	e8 49 fd ff ff       	call   1370 <exit@plt>

0000000000001627 <phase_1>:
    1627:	f3 0f 1e fa          	endbr64
    162b:	48 83 ec 08          	sub    $0x8,%rsp
    162f:	48 8d 35 52 1a 00 00 	lea    0x1a52(%rip),%rsi        # 3088 <_IO_stdin_used+0x88>
    1636:	e8 55 05 00 00       	call   1b90 <strings_not_equal>
    163b:	85 c0                	test   %eax,%eax
    163d:	75 05                	jne    1644 <phase_1+0x1d>
    163f:	48 83 c4 08          	add    $0x8,%rsp
    1643:	c3                   	ret
    1644:	e8 fc 07 00 00       	call   1e45 <explode_bomb>
    1649:	eb f4                	jmp    163f <phase_1+0x18>

000000000000164b <phase_2>:
    164b:	f3 0f 1e fa          	endbr64
    164f:	55                   	push   %rbp
    1650:	53                   	push   %rbx
    1651:	48 83 ec 28          	sub    $0x28,%rsp
    1655:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    165c:	00 00 
    165e:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
    1663:	31 c0                	xor    %eax,%eax
    1665:	48 89 e6             	mov    %rsp,%rsi
    1668:	e8 1a 08 00 00       	call   1e87 <read_six_numbers>
    166d:	83 3c 24 01          	cmpl   $0x1,(%rsp)
    1671:	75 0a                	jne    167d <phase_2+0x32>
    1673:	48 89 e3             	mov    %rsp,%rbx
    1676:	48 8d 6c 24 14       	lea    0x14(%rsp),%rbp
    167b:	eb 10                	jmp    168d <phase_2+0x42>
    167d:	e8 c3 07 00 00       	call   1e45 <explode_bomb>
    1682:	eb ef                	jmp    1673 <phase_2+0x28>
    1684:	48 83 c3 04          	add    $0x4,%rbx
    1688:	48 39 eb             	cmp    %rbp,%rbx
    168b:	74 10                	je     169d <phase_2+0x52>
    168d:	8b 03                	mov    (%rbx),%eax
    168f:	01 c0                	add    %eax,%eax
    1691:	39 43 04             	cmp    %eax,0x4(%rbx)
    1694:	74 ee                	je     1684 <phase_2+0x39>
    1696:	e8 aa 07 00 00       	call   1e45 <explode_bomb>
    169b:	eb e7                	jmp    1684 <phase_2+0x39>
    169d:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
    16a2:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    16a9:	00 00 
    16ab:	75 07                	jne    16b4 <phase_2+0x69>
    16ad:	48 83 c4 28          	add    $0x28,%rsp
    16b1:	5b                   	pop    %rbx
    16b2:	5d                   	pop    %rbp
    16b3:	c3                   	ret
    16b4:	e8 b7 fb ff ff       	call   1270 <__stack_chk_fail@plt>

00000000000016b9 <phase_3>:
    16b9:	f3 0f 1e fa          	endbr64
    16bd:	48 83 ec 18          	sub    $0x18,%rsp
    16c1:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    16c8:	00 00 
    16ca:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
    16cf:	31 c0                	xor    %eax,%eax
    16d1:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
    16d6:	48 89 e2             	mov    %rsp,%rdx
    16d9:	48 8d 35 40 1a 00 00 	lea    0x1a40(%rip),%rsi        # 3120 <_IO_stdin_used+0x120>
    16e0:	e8 3b fc ff ff       	call   1320 <__isoc99_sscanf@plt>
    16e5:	83 f8 01             	cmp    $0x1,%eax
    16e8:	7e 1a                	jle    1704 <phase_3+0x4b>
    16ea:	83 3c 24 07          	cmpl   $0x7,(%rsp)
    16ee:	77 65                	ja     1755 <phase_3+0x9c>
    16f0:	8b 04 24             	mov    (%rsp),%eax
    16f3:	48 8d 15 26 1e 00 00 	lea    0x1e26(%rip),%rdx        # 3520 <_IO_stdin_used+0x520>
    16fa:	48 63 04 82          	movslq (%rdx,%rax,4),%rax
    16fe:	48 01 d0             	add    %rdx,%rax
    1701:	3e ff e0             	notrack jmp *%rax
    1704:	e8 3c 07 00 00       	call   1e45 <explode_bomb>
    1709:	eb df                	jmp    16ea <phase_3+0x31>
    170b:	b8 29 02 00 00       	mov    $0x229,%eax
    1710:	39 44 24 04          	cmp    %eax,0x4(%rsp)
    1714:	75 52                	jne    1768 <phase_3+0xaf>
    1716:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
    171b:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    1722:	00 00 
    1724:	75 49                	jne    176f <phase_3+0xb6>
    1726:	48 83 c4 18          	add    $0x18,%rsp
    172a:	c3                   	ret
    172b:	b8 c5 03 00 00       	mov    $0x3c5,%eax
    1730:	eb de                	jmp    1710 <phase_3+0x57>
    1732:	b8 87 02 00 00       	mov    $0x287,%eax
    1737:	eb d7                	jmp    1710 <phase_3+0x57>
    1739:	b8 4e 00 00 00       	mov    $0x4e,%eax
    173e:	eb d0                	jmp    1710 <phase_3+0x57>
    1740:	b8 b0 03 00 00       	mov    $0x3b0,%eax
    1745:	eb c9                	jmp    1710 <phase_3+0x57>
    1747:	b8 4f 02 00 00       	mov    $0x24f,%eax
    174c:	eb c2                	jmp    1710 <phase_3+0x57>
    174e:	b8 b4 00 00 00       	mov    $0xb4,%eax
    1753:	eb bb                	jmp    1710 <phase_3+0x57>
    1755:	e8 eb 06 00 00       	call   1e45 <explode_bomb>
    175a:	b8 00 00 00 00       	mov    $0x0,%eax
    175f:	eb af                	jmp    1710 <phase_3+0x57>
    1761:	b8 a1 00 00 00       	mov    $0xa1,%eax
    1766:	eb a8                	jmp    1710 <phase_3+0x57>
    1768:	e8 d8 06 00 00       	call   1e45 <explode_bomb>
    176d:	eb a7                	jmp    1716 <phase_3+0x5d>
    176f:	e8 fc fa ff ff       	call   1270 <__stack_chk_fail@plt>

0000000000001774 <func4>:
    1774:	f3 0f 1e fa          	endbr64
    1778:	b8 00 00 00 00       	mov    $0x0,%eax
    177d:	85 ff                	test   %edi,%edi
    177f:	7e 2d                	jle    17ae <func4+0x3a>
    1781:	41 54                	push   %r12
    1783:	55                   	push   %rbp
    1784:	53                   	push   %rbx
    1785:	89 fb                	mov    %edi,%ebx
    1787:	89 f5                	mov    %esi,%ebp
    1789:	89 f0                	mov    %esi,%eax
    178b:	83 ff 01             	cmp    $0x1,%edi
    178e:	74 19                	je     17a9 <func4+0x35>
    1790:	8d 7f ff             	lea    -0x1(%rdi),%edi
    1793:	e8 dc ff ff ff       	call   1774 <func4>
    1798:	44 8d 24 28          	lea    (%rax,%rbp,1),%r12d
    179c:	8d 7b fe             	lea    -0x2(%rbx),%edi
    179f:	89 ee                	mov    %ebp,%esi
    17a1:	e8 ce ff ff ff       	call   1774 <func4>
    17a6:	44 01 e0             	add    %r12d,%eax
    17a9:	5b                   	pop    %rbx
    17aa:	5d                   	pop    %rbp
    17ab:	41 5c                	pop    %r12
    17ad:	c3                   	ret
    17ae:	c3                   	ret

00000000000017af <phase_4>:
    17af:	f3 0f 1e fa          	endbr64
    17b3:	48 83 ec 18          	sub    $0x18,%rsp
    17b7:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    17be:	00 00 
    17c0:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
    17c5:	31 c0                	xor    %eax,%eax
    17c7:	48 89 e1             	mov    %rsp,%rcx
    17ca:	48 8d 54 24 04       	lea    0x4(%rsp),%rdx
    17cf:	48 8d 35 4a 19 00 00 	lea    0x194a(%rip),%rsi        # 3120 <_IO_stdin_used+0x120>
    17d6:	e8 45 fb ff ff       	call   1320 <__isoc99_sscanf@plt>
    17db:	83 f8 02             	cmp    $0x2,%eax
    17de:	75 0b                	jne    17eb <phase_4+0x3c>
    17e0:	8b 04 24             	mov    (%rsp),%eax
    17e3:	83 e8 02             	sub    $0x2,%eax
    17e6:	83 f8 02             	cmp    $0x2,%eax
    17e9:	76 05                	jbe    17f0 <phase_4+0x41>
    17eb:	e8 55 06 00 00       	call   1e45 <explode_bomb>
    17f0:	8b 34 24             	mov    (%rsp),%esi
    17f3:	bf 09 00 00 00       	mov    $0x9,%edi
    17f8:	e8 77 ff ff ff       	call   1774 <func4>
    17fd:	39 44 24 04          	cmp    %eax,0x4(%rsp)
    1801:	75 15                	jne    1818 <phase_4+0x69>
    1803:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
    1808:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    180f:	00 00 
    1811:	75 0c                	jne    181f <phase_4+0x70>
    1813:	48 83 c4 18          	add    $0x18,%rsp
    1817:	c3                   	ret
    1818:	e8 28 06 00 00       	call   1e45 <explode_bomb>
    181d:	eb e4                	jmp    1803 <phase_4+0x54>
    181f:	e8 4c fa ff ff       	call   1270 <__stack_chk_fail@plt>

0000000000001824 <phase_5>:
    1824:	f3 0f 1e fa          	endbr64
    1828:	48 83 ec 18          	sub    $0x18,%rsp
    182c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1833:	00 00 
    1835:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
    183a:	31 c0                	xor    %eax,%eax
    183c:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
    1841:	48 89 e2             	mov    %rsp,%rdx
    1844:	48 8d 35 d5 18 00 00 	lea    0x18d5(%rip),%rsi        # 3120 <_IO_stdin_used+0x120>
    184b:	e8 d0 fa ff ff       	call   1320 <__isoc99_sscanf@plt>
    1850:	83 f8 01             	cmp    $0x1,%eax
    1853:	7e 5a                	jle    18af <phase_5+0x8b>
    1855:	8b 04 24             	mov    (%rsp),%eax
    1858:	83 e0 0f             	and    $0xf,%eax
    185b:	89 04 24             	mov    %eax,(%rsp)
    185e:	83 f8 0f             	cmp    $0xf,%eax
    1861:	74 32                	je     1895 <phase_5+0x71>
    1863:	b9 00 00 00 00       	mov    $0x0,%ecx
    1868:	ba 00 00 00 00       	mov    $0x0,%edx
    186d:	48 8d 35 cc 1c 00 00 	lea    0x1ccc(%rip),%rsi        # 3540 <array.0>
    1874:	83 c2 01             	add    $0x1,%edx
    1877:	48 98                	cltq
    1879:	8b 04 86             	mov    (%rsi,%rax,4),%eax
    187c:	01 c1                	add    %eax,%ecx
    187e:	83 f8 0f             	cmp    $0xf,%eax
    1881:	75 f1                	jne    1874 <phase_5+0x50>
    1883:	c7 04 24 0f 00 00 00 	movl   $0xf,(%rsp)
    188a:	83 fa 0f             	cmp    $0xf,%edx
    188d:	75 06                	jne    1895 <phase_5+0x71>
    188f:	39 4c 24 04          	cmp    %ecx,0x4(%rsp)
    1893:	74 05                	je     189a <phase_5+0x76>
    1895:	e8 ab 05 00 00       	call   1e45 <explode_bomb>
    189a:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
    189f:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    18a6:	00 00 
    18a8:	75 0c                	jne    18b6 <phase_5+0x92>
    18aa:	48 83 c4 18          	add    $0x18,%rsp
    18ae:	c3                   	ret
    18af:	e8 91 05 00 00       	call   1e45 <explode_bomb>
    18b4:	eb 9f                	jmp    1855 <phase_5+0x31>
    18b6:	e8 b5 f9 ff ff       	call   1270 <__stack_chk_fail@plt>

00000000000018bb <phase_6>:
    18bb:	f3 0f 1e fa          	endbr64
    18bf:	41 57                	push   %r15
    18c1:	41 56                	push   %r14
    18c3:	41 55                	push   %r13
    18c5:	41 54                	push   %r12
    18c7:	55                   	push   %rbp
    18c8:	53                   	push   %rbx
    18c9:	48 83 ec 78          	sub    $0x78,%rsp
    18cd:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    18d4:	00 00 
    18d6:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
    18db:	31 c0                	xor    %eax,%eax
    18dd:	4c 8d 7c 24 10       	lea    0x10(%rsp),%r15
    18e2:	4c 89 7c 24 08       	mov    %r15,0x8(%rsp)
    18e7:	4c 89 fe             	mov    %r15,%rsi
    18ea:	e8 98 05 00 00       	call   1e87 <read_six_numbers>
    18ef:	4d 89 fc             	mov    %r15,%r12
    18f2:	41 be 01 00 00 00    	mov    $0x1,%r14d
    18f8:	4d 89 fd             	mov    %r15,%r13
    18fb:	e9 fb 00 00 00       	jmp    19fb <phase_6+0x140>
    1900:	e8 40 05 00 00       	call   1e45 <explode_bomb>
    1905:	41 83 fe 05          	cmp    $0x5,%r14d
    1909:	0f 8e 08 01 00 00    	jle    1a17 <phase_6+0x15c>
    190f:	eb 2c                	jmp    193d <phase_6+0x82>
    1911:	48 83 c3 01          	add    $0x1,%rbx
    1915:	83 fb 05             	cmp    $0x5,%ebx
    1918:	0f 8f d5 00 00 00    	jg     19f3 <phase_6+0x138>
    191e:	41 8b 44 9d 00       	mov    0x0(%r13,%rbx,4),%eax
    1923:	39 45 00             	cmp    %eax,0x0(%rbp)
    1926:	75 e9                	jne    1911 <phase_6+0x56>
    1928:	e8 18 05 00 00       	call   1e45 <explode_bomb>
    192d:	eb e2                	jmp    1911 <phase_6+0x56>
    192f:	49 83 c6 01          	add    $0x1,%r14
    1933:	49 83 fe 07          	cmp    $0x7,%r14
    1937:	0f 85 96 00 00 00    	jne    19d3 <phase_6+0x118>
    193d:	48 8b 54 24 08       	mov    0x8(%rsp),%rdx
    1942:	48 83 c2 18          	add    $0x18,%rdx
    1946:	b9 07 00 00 00       	mov    $0x7,%ecx
    194b:	89 c8                	mov    %ecx,%eax
    194d:	41 2b 04 24          	sub    (%r12),%eax
    1951:	41 89 04 24          	mov    %eax,(%r12)
    1955:	49 83 c4 04          	add    $0x4,%r12
    1959:	49 39 d4             	cmp    %rdx,%r12
    195c:	75 ed                	jne    194b <phase_6+0x90>
    195e:	be 00 00 00 00       	mov    $0x0,%esi
    1963:	8b 4c b4 10          	mov    0x10(%rsp,%rsi,4),%ecx
    1967:	b8 01 00 00 00       	mov    $0x1,%eax
    196c:	48 8d 15 bd 38 00 00 	lea    0x38bd(%rip),%rdx        # 5230 <node1>
    1973:	83 f9 01             	cmp    $0x1,%ecx
    1976:	7e 0b                	jle    1983 <phase_6+0xc8>
    1978:	48 8b 52 08          	mov    0x8(%rdx),%rdx
    197c:	83 c0 01             	add    $0x1,%eax
    197f:	39 c8                	cmp    %ecx,%eax
    1981:	75 f5                	jne    1978 <phase_6+0xbd>
    1983:	48 89 54 f4 30       	mov    %rdx,0x30(%rsp,%rsi,8)
    1988:	48 83 c6 01          	add    $0x1,%rsi
    198c:	48 83 fe 06          	cmp    $0x6,%rsi
    1990:	75 d1                	jne    1963 <phase_6+0xa8>
    1992:	48 8b 5c 24 30       	mov    0x30(%rsp),%rbx
    1997:	48 8b 44 24 38       	mov    0x38(%rsp),%rax
    199c:	48 89 43 08          	mov    %rax,0x8(%rbx)
    19a0:	48 8b 54 24 40       	mov    0x40(%rsp),%rdx
    19a5:	48 89 50 08          	mov    %rdx,0x8(%rax)
    19a9:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
    19ae:	48 89 42 08          	mov    %rax,0x8(%rdx)
    19b2:	48 8b 54 24 50       	mov    0x50(%rsp),%rdx
    19b7:	48 89 50 08          	mov    %rdx,0x8(%rax)
    19bb:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
    19c0:	48 89 42 08          	mov    %rax,0x8(%rdx)
    19c4:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
    19cb:	00 
    19cc:	bd 05 00 00 00       	mov    $0x5,%ebp
    19d1:	eb 0f                	jmp    19e2 <phase_6+0x127>
    19d3:	49 83 c7 04          	add    $0x4,%r15
    19d7:	eb 22                	jmp    19fb <phase_6+0x140>
    19d9:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
    19dd:	83 ed 01             	sub    $0x1,%ebp
    19e0:	74 3d                	je     1a1f <phase_6+0x164>
    19e2:	48 8b 43 08          	mov    0x8(%rbx),%rax
    19e6:	8b 00                	mov    (%rax),%eax
    19e8:	39 03                	cmp    %eax,(%rbx)
    19ea:	7d ed                	jge    19d9 <phase_6+0x11e>
    19ec:	e8 54 04 00 00       	call   1e45 <explode_bomb>
    19f1:	eb e6                	jmp    19d9 <phase_6+0x11e>
    19f3:	49 83 c7 04          	add    $0x4,%r15
    19f7:	49 83 c6 01          	add    $0x1,%r14
    19fb:	4c 89 fd             	mov    %r15,%rbp
    19fe:	41 8b 07             	mov    (%r15),%eax
    1a01:	83 e8 01             	sub    $0x1,%eax
    1a04:	83 f8 05             	cmp    $0x5,%eax
    1a07:	0f 87 f3 fe ff ff    	ja     1900 <phase_6+0x45>
    1a0d:	41 83 fe 05          	cmp    $0x5,%r14d
    1a11:	0f 8f 18 ff ff ff    	jg     192f <phase_6+0x74>
    1a17:	4c 89 f3             	mov    %r14,%rbx
    1a1a:	e9 ff fe ff ff       	jmp    191e <phase_6+0x63>
    1a1f:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
    1a24:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    1a2b:	00 00 
    1a2d:	75 0f                	jne    1a3e <phase_6+0x183>
    1a2f:	48 83 c4 78          	add    $0x78,%rsp
    1a33:	5b                   	pop    %rbx
    1a34:	5d                   	pop    %rbp
    1a35:	41 5c                	pop    %r12
    1a37:	41 5d                	pop    %r13
    1a39:	41 5e                	pop    %r14
    1a3b:	41 5f                	pop    %r15
    1a3d:	c3                   	ret
    1a3e:	e8 2d f8 ff ff       	call   1270 <__stack_chk_fail@plt>

0000000000001a43 <fun7>:
    1a43:	f3 0f 1e fa          	endbr64
    1a47:	48 85 ff             	test   %rdi,%rdi
    1a4a:	74 32                	je     1a7e <fun7+0x3b>
    1a4c:	48 83 ec 08          	sub    $0x8,%rsp
    1a50:	8b 17                	mov    (%rdi),%edx
    1a52:	39 f2                	cmp    %esi,%edx
    1a54:	7f 0c                	jg     1a62 <fun7+0x1f>
    1a56:	b8 00 00 00 00       	mov    $0x0,%eax
    1a5b:	75 12                	jne    1a6f <fun7+0x2c>
    1a5d:	48 83 c4 08          	add    $0x8,%rsp
    1a61:	c3                   	ret
    1a62:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
    1a66:	e8 d8 ff ff ff       	call   1a43 <fun7>
    1a6b:	01 c0                	add    %eax,%eax
    1a6d:	eb ee                	jmp    1a5d <fun7+0x1a>
    1a6f:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
    1a73:	e8 cb ff ff ff       	call   1a43 <fun7>
    1a78:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
    1a7c:	eb df                	jmp    1a5d <fun7+0x1a>
    1a7e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    1a83:	c3                   	ret

0000000000001a84 <secret_phase>:
    1a84:	f3 0f 1e fa          	endbr64
    1a88:	53                   	push   %rbx
    1a89:	e8 3e 04 00 00       	call   1ecc <read_line>
    1a8e:	48 89 c7             	mov    %rax,%rdi
    1a91:	ba 0a 00 00 00       	mov    $0xa,%edx
    1a96:	be 00 00 00 00       	mov    $0x0,%esi
    1a9b:	e8 60 f8 ff ff       	call   1300 <strtol@plt>
    1aa0:	89 c3                	mov    %eax,%ebx
    1aa2:	83 e8 01             	sub    $0x1,%eax
    1aa5:	3d e8 03 00 00       	cmp    $0x3e8,%eax
    1aaa:	77 26                	ja     1ad2 <secret_phase+0x4e>
    1aac:	89 de                	mov    %ebx,%esi
    1aae:	48 8d 3d 9b 36 00 00 	lea    0x369b(%rip),%rdi        # 5150 <n1>
    1ab5:	e8 89 ff ff ff       	call   1a43 <fun7>
    1aba:	83 f8 03             	cmp    $0x3,%eax
    1abd:	75 1a                	jne    1ad9 <secret_phase+0x55>
    1abf:	48 8d 3d e2 17 00 00 	lea    0x17e2(%rip),%rdi        # 32a8 <_IO_stdin_used+0x2a8>
    1ac6:	e8 75 f7 ff ff       	call   1240 <puts@plt>
    1acb:	e8 3e 05 00 00       	call   200e <phase_defused>
    1ad0:	5b                   	pop    %rbx
    1ad1:	c3                   	ret
    1ad2:	e8 6e 03 00 00       	call   1e45 <explode_bomb>
    1ad7:	eb d3                	jmp    1aac <secret_phase+0x28>
    1ad9:	e8 67 03 00 00       	call   1e45 <explode_bomb>
    1ade:	eb df                	jmp    1abf <secret_phase+0x3b>

0000000000001ae0 <sig_handler>:
    1ae0:	f3 0f 1e fa          	endbr64
    1ae4:	50                   	push   %rax
    1ae5:	58                   	pop    %rax
    1ae6:	48 83 ec 08          	sub    $0x8,%rsp
    1aea:	48 8d 3d df 17 00 00 	lea    0x17df(%rip),%rdi        # 32d0 <_IO_stdin_used+0x2d0>
    1af1:	e8 4a f7 ff ff       	call   1240 <puts@plt>
    1af6:	bf 03 00 00 00       	mov    $0x3,%edi
    1afb:	e8 a0 f8 ff ff       	call   13a0 <sleep@plt>
    1b00:	48 8d 35 95 15 00 00 	lea    0x1595(%rip),%rsi        # 309c <_IO_stdin_used+0x9c>
    1b07:	bf 02 00 00 00       	mov    $0x2,%edi
    1b0c:	b8 00 00 00 00       	mov    $0x0,%eax
    1b11:	e8 2a f8 ff ff       	call   1340 <__printf_chk@plt>
    1b16:	48 8b 3d 63 37 00 00 	mov    0x3763(%rip),%rdi        # 5280 <stdout@GLIBC_2.2.5>
    1b1d:	e8 ee f7 ff ff       	call   1310 <fflush@plt>
    1b22:	bf 01 00 00 00       	mov    $0x1,%edi
    1b27:	e8 74 f8 ff ff       	call   13a0 <sleep@plt>
    1b2c:	48 8d 3d 71 15 00 00 	lea    0x1571(%rip),%rdi        # 30a4 <_IO_stdin_used+0xa4>
    1b33:	e8 08 f7 ff ff       	call   1240 <puts@plt>
    1b38:	bf 10 00 00 00       	mov    $0x10,%edi
    1b3d:	e8 2e f8 ff ff       	call   1370 <exit@plt>

0000000000001b42 <invalid_phase>:
    1b42:	f3 0f 1e fa          	endbr64
    1b46:	50                   	push   %rax
    1b47:	58                   	pop    %rax
    1b48:	48 83 ec 08          	sub    $0x8,%rsp
    1b4c:	48 89 fa             	mov    %rdi,%rdx
    1b4f:	48 8d 35 56 15 00 00 	lea    0x1556(%rip),%rsi        # 30ac <_IO_stdin_used+0xac>
    1b56:	bf 02 00 00 00       	mov    $0x2,%edi
    1b5b:	b8 00 00 00 00       	mov    $0x0,%eax
    1b60:	e8 db f7 ff ff       	call   1340 <__printf_chk@plt>
    1b65:	bf 08 00 00 00       	mov    $0x8,%edi
    1b6a:	e8 01 f8 ff ff       	call   1370 <exit@plt>

0000000000001b6f <string_length>:
    1b6f:	f3 0f 1e fa          	endbr64
    1b73:	80 3f 00             	cmpb   $0x0,(%rdi)
    1b76:	74 12                	je     1b8a <string_length+0x1b>
    1b78:	b8 00 00 00 00       	mov    $0x0,%eax
    1b7d:	48 83 c7 01          	add    $0x1,%rdi
    1b81:	83 c0 01             	add    $0x1,%eax
    1b84:	80 3f 00             	cmpb   $0x0,(%rdi)
    1b87:	75 f4                	jne    1b7d <string_length+0xe>
    1b89:	c3                   	ret
    1b8a:	b8 00 00 00 00       	mov    $0x0,%eax
    1b8f:	c3                   	ret

0000000000001b90 <strings_not_equal>:
    1b90:	f3 0f 1e fa          	endbr64
    1b94:	41 54                	push   %r12
    1b96:	55                   	push   %rbp
    1b97:	53                   	push   %rbx
    1b98:	48 89 fb             	mov    %rdi,%rbx
    1b9b:	48 89 f5             	mov    %rsi,%rbp
    1b9e:	e8 cc ff ff ff       	call   1b6f <string_length>
    1ba3:	41 89 c4             	mov    %eax,%r12d
    1ba6:	48 89 ef             	mov    %rbp,%rdi
    1ba9:	e8 c1 ff ff ff       	call   1b6f <string_length>
    1bae:	89 c2                	mov    %eax,%edx
    1bb0:	b8 01 00 00 00       	mov    $0x1,%eax
    1bb5:	41 39 d4             	cmp    %edx,%r12d
    1bb8:	75 31                	jne    1beb <strings_not_equal+0x5b>
    1bba:	0f b6 13             	movzbl (%rbx),%edx
    1bbd:	84 d2                	test   %dl,%dl
    1bbf:	74 1e                	je     1bdf <strings_not_equal+0x4f>
    1bc1:	b8 00 00 00 00       	mov    $0x0,%eax
    1bc6:	38 54 05 00          	cmp    %dl,0x0(%rbp,%rax,1)
    1bca:	75 1a                	jne    1be6 <strings_not_equal+0x56>
    1bcc:	48 83 c0 01          	add    $0x1,%rax
    1bd0:	0f b6 14 03          	movzbl (%rbx,%rax,1),%edx
    1bd4:	84 d2                	test   %dl,%dl
    1bd6:	75 ee                	jne    1bc6 <strings_not_equal+0x36>
    1bd8:	b8 00 00 00 00       	mov    $0x0,%eax
    1bdd:	eb 0c                	jmp    1beb <strings_not_equal+0x5b>
    1bdf:	b8 00 00 00 00       	mov    $0x0,%eax
    1be4:	eb 05                	jmp    1beb <strings_not_equal+0x5b>
    1be6:	b8 01 00 00 00       	mov    $0x1,%eax
    1beb:	5b                   	pop    %rbx
    1bec:	5d                   	pop    %rbp
    1bed:	41 5c                	pop    %r12
    1bef:	c3                   	ret

0000000000001bf0 <initialize_bomb>:
    1bf0:	f3 0f 1e fa          	endbr64
    1bf4:	48 81 ec 00 10 00 00 	sub    $0x1000,%rsp
    1bfb:	48 83 0c 24 00       	orq    $0x0,(%rsp)
    1c00:	48 81 ec 00 10 00 00 	sub    $0x1000,%rsp
    1c07:	48 83 0c 24 00       	orq    $0x0,(%rsp)
    1c0c:	48 83 ec 58          	sub    $0x58,%rsp
    1c10:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1c17:	00 00 
    1c19:	48 89 84 24 48 20 00 	mov    %rax,0x2048(%rsp)
    1c20:	00 
    1c21:	31 c0                	xor    %eax,%eax
    1c23:	48 8d 35 b6 fe ff ff 	lea    -0x14a(%rip),%rsi        # 1ae0 <sig_handler>
    1c2a:	bf 02 00 00 00       	mov    $0x2,%edi
    1c2f:	e8 8c f6 ff ff       	call   12c0 <signal@plt>
    1c34:	48 89 e7             	mov    %rsp,%rdi
    1c37:	be 40 00 00 00       	mov    $0x40,%esi
    1c3c:	e8 1f f7 ff ff       	call   1360 <gethostname@plt>
    1c41:	85 c0                	test   %eax,%eax
    1c43:	75 29                	jne    1c6e <initialize_bomb+0x7e>
    1c45:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
    1c4a:	e8 92 0d 00 00       	call   29e1 <init_driver>
    1c4f:	85 c0                	test   %eax,%eax
    1c51:	78 31                	js     1c84 <initialize_bomb+0x94>
    1c53:	48 8b 84 24 48 20 00 	mov    0x2048(%rsp),%rax
    1c5a:	00 
    1c5b:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    1c62:	00 00 
    1c64:	75 43                	jne    1ca9 <initialize_bomb+0xb9>
    1c66:	48 81 c4 58 20 00 00 	add    $0x2058,%rsp
    1c6d:	c3                   	ret
    1c6e:	48 8d 3d 93 16 00 00 	lea    0x1693(%rip),%rdi        # 3308 <_IO_stdin_used+0x308>
    1c75:	e8 c6 f5 ff ff       	call   1240 <puts@plt>
    1c7a:	bf 08 00 00 00       	mov    $0x8,%edi
    1c7f:	e8 ec f6 ff ff       	call   1370 <exit@plt>
    1c84:	48 8d 54 24 40       	lea    0x40(%rsp),%rdx
    1c89:	48 8d 35 2d 14 00 00 	lea    0x142d(%rip),%rsi        # 30bd <_IO_stdin_used+0xbd>
    1c90:	bf 02 00 00 00       	mov    $0x2,%edi
    1c95:	b8 00 00 00 00       	mov    $0x0,%eax
    1c9a:	e8 a1 f6 ff ff       	call   1340 <__printf_chk@plt>
    1c9f:	bf 08 00 00 00       	mov    $0x8,%edi
    1ca4:	e8 c7 f6 ff ff       	call   1370 <exit@plt>
    1ca9:	e8 c2 f5 ff ff       	call   1270 <__stack_chk_fail@plt>

0000000000001cae <initialize_bomb_solve>:
    1cae:	f3 0f 1e fa          	endbr64
    1cb2:	c3                   	ret

0000000000001cb3 <blank_line>:
    1cb3:	f3 0f 1e fa          	endbr64
    1cb7:	55                   	push   %rbp
    1cb8:	53                   	push   %rbx
    1cb9:	48 83 ec 08          	sub    $0x8,%rsp
    1cbd:	48 89 fd             	mov    %rdi,%rbp
    1cc0:	0f b6 5d 00          	movzbl 0x0(%rbp),%ebx
    1cc4:	84 db                	test   %bl,%bl
    1cc6:	74 1e                	je     1ce6 <blank_line+0x33>
    1cc8:	e8 e3 f6 ff ff       	call   13b0 <__ctype_b_loc@plt>
    1ccd:	48 83 c5 01          	add    $0x1,%rbp
    1cd1:	48 0f be db          	movsbq %bl,%rbx
    1cd5:	48 8b 00             	mov    (%rax),%rax
    1cd8:	f6 44 58 01 20       	testb  $0x20,0x1(%rax,%rbx,2)
    1cdd:	75 e1                	jne    1cc0 <blank_line+0xd>
    1cdf:	b8 00 00 00 00       	mov    $0x0,%eax
    1ce4:	eb 05                	jmp    1ceb <blank_line+0x38>
    1ce6:	b8 01 00 00 00       	mov    $0x1,%eax
    1ceb:	48 83 c4 08          	add    $0x8,%rsp
    1cef:	5b                   	pop    %rbx
    1cf0:	5d                   	pop    %rbp
    1cf1:	c3                   	ret

0000000000001cf2 <skip>:
    1cf2:	f3 0f 1e fa          	endbr64
    1cf6:	55                   	push   %rbp
    1cf7:	53                   	push   %rbx
    1cf8:	48 83 ec 08          	sub    $0x8,%rsp
    1cfc:	48 8d 1d 1d 36 00 00 	lea    0x361d(%rip),%rbx        # 5320 <input_strings>
    1d03:	48 63 05 06 36 00 00 	movslq 0x3606(%rip),%rax        # 5310 <num_input_strings>
    1d0a:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
    1d0e:	48 c1 e7 04          	shl    $0x4,%rdi
    1d12:	be 40 06 00 00       	mov    $0x640,%esi
    1d17:	48 39 f7             	cmp    %rsi,%rdi
    1d1a:	48 0f 43 f7          	cmovae %rdi,%rsi
    1d1e:	48 29 fe             	sub    %rdi,%rsi
    1d21:	48 01 df             	add    %rbx,%rdi
    1d24:	48 8b 0d 85 35 00 00 	mov    0x3585(%rip),%rcx        # 52b0 <infile>
    1d2b:	ba 50 00 00 00       	mov    $0x50,%edx
    1d30:	e8 fb f5 ff ff       	call   1330 <__fgets_chk@plt>
    1d35:	48 89 c5             	mov    %rax,%rbp
    1d38:	48 85 c0             	test   %rax,%rax
    1d3b:	74 0c                	je     1d49 <skip+0x57>
    1d3d:	48 89 c7             	mov    %rax,%rdi
    1d40:	e8 6e ff ff ff       	call   1cb3 <blank_line>
    1d45:	85 c0                	test   %eax,%eax
    1d47:	75 ba                	jne    1d03 <skip+0x11>
    1d49:	48 89 e8             	mov    %rbp,%rax
    1d4c:	48 83 c4 08          	add    $0x8,%rsp
    1d50:	5b                   	pop    %rbx
    1d51:	5d                   	pop    %rbp
    1d52:	c3                   	ret

0000000000001d53 <send_msg>:
    1d53:	f3 0f 1e fa          	endbr64
    1d57:	53                   	push   %rbx
    1d58:	4c 8d 9c 24 00 c0 ff 	lea    -0x4000(%rsp),%r11
    1d5f:	ff 
    1d60:	48 81 ec 00 10 00 00 	sub    $0x1000,%rsp
    1d67:	48 83 0c 24 00       	orq    $0x0,(%rsp)
    1d6c:	4c 39 dc             	cmp    %r11,%rsp
    1d6f:	75 ef                	jne    1d60 <send_msg+0xd>
    1d71:	48 83 ec 10          	sub    $0x10,%rsp
    1d75:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1d7c:	00 00 
    1d7e:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
    1d85:	00 
    1d86:	31 c0                	xor    %eax,%eax
    1d88:	8b 15 82 35 00 00    	mov    0x3582(%rip),%edx        # 5310 <num_input_strings>
    1d8e:	8d 42 ff             	lea    -0x1(%rdx),%eax
    1d91:	48 98                	cltq
    1d93:	48 8d 04 80          	lea    (%rax,%rax,4),%rax
    1d97:	48 c1 e0 04          	shl    $0x4,%rax
    1d9b:	48 8d 0d 7e 35 00 00 	lea    0x357e(%rip),%rcx        # 5320 <input_strings>
    1da2:	48 01 c8             	add    %rcx,%rax
    1da5:	85 ff                	test   %edi,%edi
    1da7:	4c 8d 0d 31 13 00 00 	lea    0x1331(%rip),%r9        # 30df <_IO_stdin_used+0xdf>
    1dae:	48 8d 0d 22 13 00 00 	lea    0x1322(%rip),%rcx        # 30d7 <_IO_stdin_used+0xd7>
    1db5:	4c 0f 45 c9          	cmovne %rcx,%r9
    1db9:	48 89 e3             	mov    %rsp,%rbx
    1dbc:	50                   	push   %rax
    1dbd:	52                   	push   %rdx
    1dbe:	44 8b 05 7f 33 00 00 	mov    0x337f(%rip),%r8d        # 5144 <bomb_id>
    1dc5:	48 8d 0d 1c 13 00 00 	lea    0x131c(%rip),%rcx        # 30e8 <_IO_stdin_used+0xe8>
    1dcc:	ba 00 20 00 00       	mov    $0x2000,%edx
    1dd1:	be 02 00 00 00       	mov    $0x2,%esi
    1dd6:	48 89 df             	mov    %rbx,%rdi
    1dd9:	b8 00 00 00 00       	mov    $0x0,%eax
    1dde:	e8 dd f5 ff ff       	call   13c0 <__sprintf_chk@plt>
    1de3:	4c 8d 84 24 10 20 00 	lea    0x2010(%rsp),%r8
    1dea:	00 
    1deb:	b9 00 00 00 00       	mov    $0x0,%ecx
    1df0:	48 89 da             	mov    %rbx,%rdx
    1df3:	48 8d 35 26 33 00 00 	lea    0x3326(%rip),%rsi        # 5120 <user_password>
    1dfa:	48 8d 3d 37 33 00 00 	lea    0x3337(%rip),%rdi        # 5138 <userid>
    1e01:	e8 cf 0d 00 00       	call   2bd5 <driver_post>
    1e06:	48 89 dc             	mov    %rbx,%rsp
    1e09:	85 c0                	test   %eax,%eax
    1e0b:	78 1c                	js     1e29 <send_msg+0xd6>
    1e0d:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
    1e14:	00 
    1e15:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    1e1c:	00 00 
    1e1e:	75 20                	jne    1e40 <send_msg+0xed>
    1e20:	48 81 c4 10 40 00 00 	add    $0x4010,%rsp
    1e27:	5b                   	pop    %rbx
    1e28:	c3                   	ret
    1e29:	48 8d bc 24 00 20 00 	lea    0x2000(%rsp),%rdi
    1e30:	00 
    1e31:	e8 0a f4 ff ff       	call   1240 <puts@plt>
    1e36:	bf 00 00 00 00       	mov    $0x0,%edi
    1e3b:	e8 30 f5 ff ff       	call   1370 <exit@plt>
    1e40:	e8 2b f4 ff ff       	call   1270 <__stack_chk_fail@plt>

0000000000001e45 <explode_bomb>:
    1e45:	f3 0f 1e fa          	endbr64
    1e49:	50                   	push   %rax
    1e4a:	58                   	pop    %rax
    1e4b:	48 83 ec 08          	sub    $0x8,%rsp
    1e4f:	48 8d 3d 9e 12 00 00 	lea    0x129e(%rip),%rdi        # 30f4 <_IO_stdin_used+0xf4>
    1e56:	e8 e5 f3 ff ff       	call   1240 <puts@plt>
    1e5b:	48 8d 3d 9b 12 00 00 	lea    0x129b(%rip),%rdi        # 30fd <_IO_stdin_used+0xfd>
    1e62:	e8 d9 f3 ff ff       	call   1240 <puts@plt>
    1e67:	bf 00 00 00 00       	mov    $0x0,%edi
    1e6c:	e8 e2 fe ff ff       	call   1d53 <send_msg>
    1e71:	48 8d 3d c8 14 00 00 	lea    0x14c8(%rip),%rdi        # 3340 <_IO_stdin_used+0x340>
    1e78:	e8 c3 f3 ff ff       	call   1240 <puts@plt>
    1e7d:	bf 08 00 00 00       	mov    $0x8,%edi
    1e82:	e8 e9 f4 ff ff       	call   1370 <exit@plt>

0000000000001e87 <read_six_numbers>:
    1e87:	f3 0f 1e fa          	endbr64
    1e8b:	48 83 ec 08          	sub    $0x8,%rsp
    1e8f:	48 89 f2             	mov    %rsi,%rdx
    1e92:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
    1e96:	48 8d 46 14          	lea    0x14(%rsi),%rax
    1e9a:	50                   	push   %rax
    1e9b:	48 8d 46 10          	lea    0x10(%rsi),%rax
    1e9f:	50                   	push   %rax
    1ea0:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
    1ea4:	4c 8d 46 08          	lea    0x8(%rsi),%r8
    1ea8:	48 8d 35 65 12 00 00 	lea    0x1265(%rip),%rsi        # 3114 <_IO_stdin_used+0x114>
    1eaf:	b8 00 00 00 00       	mov    $0x0,%eax
    1eb4:	e8 67 f4 ff ff       	call   1320 <__isoc99_sscanf@plt>
    1eb9:	48 83 c4 10          	add    $0x10,%rsp
    1ebd:	83 f8 05             	cmp    $0x5,%eax
    1ec0:	7e 05                	jle    1ec7 <read_six_numbers+0x40>
    1ec2:	48 83 c4 08          	add    $0x8,%rsp
    1ec6:	c3                   	ret
    1ec7:	e8 79 ff ff ff       	call   1e45 <explode_bomb>

0000000000001ecc <read_line>:
    1ecc:	f3 0f 1e fa          	endbr64
    1ed0:	55                   	push   %rbp
    1ed1:	53                   	push   %rbx
    1ed2:	48 83 ec 08          	sub    $0x8,%rsp
    1ed6:	b8 00 00 00 00       	mov    $0x0,%eax
    1edb:	e8 12 fe ff ff       	call   1cf2 <skip>
    1ee0:	48 85 c0             	test   %rax,%rax
    1ee3:	74 5d                	je     1f42 <read_line+0x76>
    1ee5:	8b 2d 25 34 00 00    	mov    0x3425(%rip),%ebp        # 5310 <num_input_strings>
    1eeb:	48 63 c5             	movslq %ebp,%rax
    1eee:	48 8d 1c 80          	lea    (%rax,%rax,4),%rbx
    1ef2:	48 c1 e3 04          	shl    $0x4,%rbx
    1ef6:	48 8d 05 23 34 00 00 	lea    0x3423(%rip),%rax        # 5320 <input_strings>
    1efd:	48 01 c3             	add    %rax,%rbx
    1f00:	48 89 df             	mov    %rbx,%rdi
    1f03:	e8 58 f3 ff ff       	call   1260 <strlen@plt>
    1f08:	83 f8 4e             	cmp    $0x4e,%eax
    1f0b:	0f 8f a9 00 00 00    	jg     1fba <read_line+0xee>
    1f11:	83 e8 01             	sub    $0x1,%eax
    1f14:	48 98                	cltq
    1f16:	48 63 d5             	movslq %ebp,%rdx
    1f19:	48 8d 0c 92          	lea    (%rdx,%rdx,4),%rcx
    1f1d:	48 c1 e1 04          	shl    $0x4,%rcx
    1f21:	48 8d 15 f8 33 00 00 	lea    0x33f8(%rip),%rdx        # 5320 <input_strings>
    1f28:	48 01 ca             	add    %rcx,%rdx
    1f2b:	c6 04 02 00          	movb   $0x0,(%rdx,%rax,1)
    1f2f:	83 c5 01             	add    $0x1,%ebp
    1f32:	89 2d d8 33 00 00    	mov    %ebp,0x33d8(%rip)        # 5310 <num_input_strings>
    1f38:	48 89 d8             	mov    %rbx,%rax
    1f3b:	48 83 c4 08          	add    $0x8,%rsp
    1f3f:	5b                   	pop    %rbx
    1f40:	5d                   	pop    %rbp
    1f41:	c3                   	ret
    1f42:	48 8b 05 47 33 00 00 	mov    0x3347(%rip),%rax        # 5290 <stdin@GLIBC_2.2.5>
    1f49:	48 39 05 60 33 00 00 	cmp    %rax,0x3360(%rip)        # 52b0 <infile>
    1f50:	74 1b                	je     1f6d <read_line+0xa1>
    1f52:	48 8d 3d eb 11 00 00 	lea    0x11eb(%rip),%rdi        # 3144 <_IO_stdin_used+0x144>
    1f59:	e8 b2 f2 ff ff       	call   1210 <getenv@plt>
    1f5e:	48 85 c0             	test   %rax,%rax
    1f61:	74 20                	je     1f83 <read_line+0xb7>
    1f63:	bf 00 00 00 00       	mov    $0x0,%edi
    1f68:	e8 03 f4 ff ff       	call   1370 <exit@plt>
    1f6d:	48 8d 3d b2 11 00 00 	lea    0x11b2(%rip),%rdi        # 3126 <_IO_stdin_used+0x126>
    1f74:	e8 c7 f2 ff ff       	call   1240 <puts@plt>
    1f79:	bf 08 00 00 00       	mov    $0x8,%edi
    1f7e:	e8 ed f3 ff ff       	call   1370 <exit@plt>
    1f83:	48 8b 05 06 33 00 00 	mov    0x3306(%rip),%rax        # 5290 <stdin@GLIBC_2.2.5>
    1f8a:	48 89 05 1f 33 00 00 	mov    %rax,0x331f(%rip)        # 52b0 <infile>
    1f91:	b8 00 00 00 00       	mov    $0x0,%eax
    1f96:	e8 57 fd ff ff       	call   1cf2 <skip>
    1f9b:	48 85 c0             	test   %rax,%rax
    1f9e:	0f 85 41 ff ff ff    	jne    1ee5 <read_line+0x19>
    1fa4:	48 8d 3d 7b 11 00 00 	lea    0x117b(%rip),%rdi        # 3126 <_IO_stdin_used+0x126>
    1fab:	e8 90 f2 ff ff       	call   1240 <puts@plt>
    1fb0:	bf 00 00 00 00       	mov    $0x0,%edi
    1fb5:	e8 b6 f3 ff ff       	call   1370 <exit@plt>
    1fba:	48 8d 3d 8e 11 00 00 	lea    0x118e(%rip),%rdi        # 314f <_IO_stdin_used+0x14f>
    1fc1:	e8 7a f2 ff ff       	call   1240 <puts@plt>
    1fc6:	8b 05 44 33 00 00    	mov    0x3344(%rip),%eax        # 5310 <num_input_strings>
    1fcc:	8d 50 01             	lea    0x1(%rax),%edx
    1fcf:	89 15 3b 33 00 00    	mov    %edx,0x333b(%rip)        # 5310 <num_input_strings>
    1fd5:	48 98                	cltq
    1fd7:	48 6b c0 50          	imul   $0x50,%rax,%rax
    1fdb:	ba 40 06 00 00       	mov    $0x640,%edx
    1fe0:	48 39 d0             	cmp    %rdx,%rax
    1fe3:	48 0f 43 d0          	cmovae %rax,%rdx
    1fe7:	48 89 d1             	mov    %rdx,%rcx
    1fea:	48 29 c1             	sub    %rax,%rcx
    1fed:	48 8d 15 2c 33 00 00 	lea    0x332c(%rip),%rdx        # 5320 <input_strings>
    1ff4:	48 8d 3c 10          	lea    (%rax,%rdx,1),%rdi
    1ff8:	ba 10 00 00 00       	mov    $0x10,%edx
    1ffd:	48 8d 35 66 11 00 00 	lea    0x1166(%rip),%rsi        # 316a <_IO_stdin_used+0x16a>
    2004:	e8 e7 f2 ff ff       	call   12f0 <__memcpy_chk@plt>
    2009:	e8 37 fe ff ff       	call   1e45 <explode_bomb>

000000000000200e <phase_defused>:
    200e:	f3 0f 1e fa          	endbr64
    2012:	48 83 ec 78          	sub    $0x78,%rsp
    2016:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    201d:	00 00 
    201f:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
    2024:	31 c0                	xor    %eax,%eax
    2026:	bf 01 00 00 00       	mov    $0x1,%edi
    202b:	e8 23 fd ff ff       	call   1d53 <send_msg>
    2030:	83 3d d9 32 00 00 06 	cmpl   $0x6,0x32d9(%rip)        # 5310 <num_input_strings>
    2037:	74 19                	je     2052 <phase_defused+0x44>
    2039:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
    203e:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2045:	00 00 
    2047:	0f 85 84 00 00 00    	jne    20d1 <phase_defused+0xc3>
    204d:	48 83 c4 78          	add    $0x78,%rsp
    2051:	c3                   	ret
    2052:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
    2057:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
    205c:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
    2061:	48 8d 35 12 11 00 00 	lea    0x1112(%rip),%rsi        # 317a <_IO_stdin_used+0x17a>
    2068:	48 8d 3d a1 33 00 00 	lea    0x33a1(%rip),%rdi        # 5410 <input_strings+0xf0>
    206f:	b8 00 00 00 00       	mov    $0x0,%eax
    2074:	e8 a7 f2 ff ff       	call   1320 <__isoc99_sscanf@plt>
    2079:	83 f8 03             	cmp    $0x3,%eax
    207c:	74 1a                	je     2098 <phase_defused+0x8a>
    207e:	48 8d 3d 43 13 00 00 	lea    0x1343(%rip),%rdi        # 33c8 <_IO_stdin_used+0x3c8>
    2085:	e8 b6 f1 ff ff       	call   1240 <puts@plt>
    208a:	48 8d 3d 67 13 00 00 	lea    0x1367(%rip),%rdi        # 33f8 <_IO_stdin_used+0x3f8>
    2091:	e8 aa f1 ff ff       	call   1240 <puts@plt>
    2096:	eb a1                	jmp    2039 <phase_defused+0x2b>
    2098:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
    209d:	48 8d 35 df 10 00 00 	lea    0x10df(%rip),%rsi        # 3183 <_IO_stdin_used+0x183>
    20a4:	e8 e7 fa ff ff       	call   1b90 <strings_not_equal>
    20a9:	85 c0                	test   %eax,%eax
    20ab:	75 d1                	jne    207e <phase_defused+0x70>
    20ad:	48 8d 3d b4 12 00 00 	lea    0x12b4(%rip),%rdi        # 3368 <_IO_stdin_used+0x368>
    20b4:	e8 87 f1 ff ff       	call   1240 <puts@plt>
    20b9:	48 8d 3d d0 12 00 00 	lea    0x12d0(%rip),%rdi        # 3390 <_IO_stdin_used+0x390>
    20c0:	e8 7b f1 ff ff       	call   1240 <puts@plt>
    20c5:	b8 00 00 00 00       	mov    $0x0,%eax
    20ca:	e8 b5 f9 ff ff       	call   1a84 <secret_phase>
    20cf:	eb ad                	jmp    207e <phase_defused+0x70>
    20d1:	e8 9a f1 ff ff       	call   1270 <__stack_chk_fail@plt>

00000000000020d6 <sigalrm_handler>:
    20d6:	f3 0f 1e fa          	endbr64
    20da:	50                   	push   %rax
    20db:	58                   	pop    %rax
    20dc:	48 83 ec 08          	sub    $0x8,%rsp
    20e0:	b9 00 00 00 00       	mov    $0x0,%ecx
    20e5:	48 8d 15 54 13 00 00 	lea    0x1354(%rip),%rdx        # 3440 <_IO_stdin_used+0x440>
    20ec:	be 02 00 00 00       	mov    $0x2,%esi
    20f1:	48 8b 3d a8 31 00 00 	mov    0x31a8(%rip),%rdi        # 52a0 <stderr@GLIBC_2.2.5>
    20f8:	b8 00 00 00 00       	mov    $0x0,%eax
    20fd:	e8 8e f2 ff ff       	call   1390 <__fprintf_chk@plt>
    2102:	bf 01 00 00 00       	mov    $0x1,%edi
    2107:	e8 64 f2 ff ff       	call   1370 <exit@plt>

000000000000210c <rio_readlineb>:
    210c:	41 56                	push   %r14
    210e:	41 55                	push   %r13
    2110:	41 54                	push   %r12
    2112:	55                   	push   %rbp
    2113:	53                   	push   %rbx
    2114:	49 89 f4             	mov    %rsi,%r12
    2117:	48 83 fa 01          	cmp    $0x1,%rdx
    211b:	0f 86 90 00 00 00    	jbe    21b1 <rio_readlineb+0xa5>
    2121:	48 89 fb             	mov    %rdi,%rbx
    2124:	4c 8d 74 16 ff       	lea    -0x1(%rsi,%rdx,1),%r14
    2129:	41 bd 01 00 00 00    	mov    $0x1,%r13d
    212f:	48 8d 6f 10          	lea    0x10(%rdi),%rbp
    2133:	eb 54                	jmp    2189 <rio_readlineb+0x7d>
    2135:	e8 e6 f0 ff ff       	call   1220 <__errno_location@plt>
    213a:	83 38 04             	cmpl   $0x4,(%rax)
    213d:	75 53                	jne    2192 <rio_readlineb+0x86>
    213f:	8b 3b                	mov    (%rbx),%edi
    2141:	ba 00 20 00 00       	mov    $0x2000,%edx
    2146:	48 89 ee             	mov    %rbp,%rsi
    2149:	e8 52 f1 ff ff       	call   12a0 <read@plt>
    214e:	89 c2                	mov    %eax,%edx
    2150:	89 43 04             	mov    %eax,0x4(%rbx)
    2153:	85 c0                	test   %eax,%eax
    2155:	78 de                	js     2135 <rio_readlineb+0x29>
    2157:	74 42                	je     219b <rio_readlineb+0x8f>
    2159:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
    215d:	48 8b 43 08          	mov    0x8(%rbx),%rax
    2161:	0f b6 08             	movzbl (%rax),%ecx
    2164:	48 83 c0 01          	add    $0x1,%rax
    2168:	48 89 43 08          	mov    %rax,0x8(%rbx)
    216c:	83 ea 01             	sub    $0x1,%edx
    216f:	89 53 04             	mov    %edx,0x4(%rbx)
    2172:	49 83 c4 01          	add    $0x1,%r12
    2176:	41 88 4c 24 ff       	mov    %cl,-0x1(%r12)
    217b:	80 f9 0a             	cmp    $0xa,%cl
    217e:	74 3c                	je     21bc <rio_readlineb+0xb0>
    2180:	41 83 c5 01          	add    $0x1,%r13d
    2184:	4d 39 f4             	cmp    %r14,%r12
    2187:	74 30                	je     21b9 <rio_readlineb+0xad>
    2189:	8b 53 04             	mov    0x4(%rbx),%edx
    218c:	85 d2                	test   %edx,%edx
    218e:	7e af                	jle    213f <rio_readlineb+0x33>
    2190:	eb cb                	jmp    215d <rio_readlineb+0x51>
    2192:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    2199:	eb 05                	jmp    21a0 <rio_readlineb+0x94>
    219b:	b8 00 00 00 00       	mov    $0x0,%eax
    21a0:	85 c0                	test   %eax,%eax
    21a2:	75 29                	jne    21cd <rio_readlineb+0xc1>
    21a4:	b8 00 00 00 00       	mov    $0x0,%eax
    21a9:	41 83 fd 01          	cmp    $0x1,%r13d
    21ad:	75 0d                	jne    21bc <rio_readlineb+0xb0>
    21af:	eb 13                	jmp    21c4 <rio_readlineb+0xb8>
    21b1:	41 bd 01 00 00 00    	mov    $0x1,%r13d
    21b7:	eb 03                	jmp    21bc <rio_readlineb+0xb0>
    21b9:	4d 89 f4             	mov    %r14,%r12
    21bc:	41 c6 04 24 00       	movb   $0x0,(%r12)
    21c1:	49 63 c5             	movslq %r13d,%rax
    21c4:	5b                   	pop    %rbx
    21c5:	5d                   	pop    %rbp
    21c6:	41 5c                	pop    %r12
    21c8:	41 5d                	pop    %r13
    21ca:	41 5e                	pop    %r14
    21cc:	c3                   	ret
    21cd:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    21d4:	eb ee                	jmp    21c4 <rio_readlineb+0xb8>

00000000000021d6 <submitr>:
    21d6:	f3 0f 1e fa          	endbr64
    21da:	41 57                	push   %r15
    21dc:	41 56                	push   %r14
    21de:	41 55                	push   %r13
    21e0:	41 54                	push   %r12
    21e2:	55                   	push   %rbp
    21e3:	53                   	push   %rbx
    21e4:	4c 8d 9c 24 00 60 ff 	lea    -0xa000(%rsp),%r11
    21eb:	ff 
    21ec:	48 81 ec 00 10 00 00 	sub    $0x1000,%rsp
    21f3:	48 83 0c 24 00       	orq    $0x0,(%rsp)
    21f8:	4c 39 dc             	cmp    %r11,%rsp
    21fb:	75 ef                	jne    21ec <submitr+0x16>
    21fd:	48 83 ec 68          	sub    $0x68,%rsp
    2201:	49 89 fd             	mov    %rdi,%r13
    2204:	89 f5                	mov    %esi,%ebp
    2206:	48 89 14 24          	mov    %rdx,(%rsp)
    220a:	48 89 4c 24 08       	mov    %rcx,0x8(%rsp)
    220f:	4c 89 44 24 18       	mov    %r8,0x18(%rsp)
    2214:	4c 89 4c 24 10       	mov    %r9,0x10(%rsp)
    2219:	48 8b 9c 24 a0 a0 00 	mov    0xa0a0(%rsp),%rbx
    2220:	00 
    2221:	4c 8b bc 24 a8 a0 00 	mov    0xa0a8(%rsp),%r15
    2228:	00 
    2229:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2230:	00 00 
    2232:	48 89 84 24 58 a0 00 	mov    %rax,0xa058(%rsp)
    2239:	00 
    223a:	31 c0                	xor    %eax,%eax
    223c:	c7 44 24 2c 00 00 00 	movl   $0x0,0x2c(%rsp)
    2243:	00 
    2244:	ba 00 00 00 00       	mov    $0x0,%edx
    2249:	be 01 00 00 00       	mov    $0x1,%esi
    224e:	bf 02 00 00 00       	mov    $0x2,%edi
    2253:	e8 78 f1 ff ff       	call   13d0 <socket@plt>
    2258:	85 c0                	test   %eax,%eax
    225a:	0f 88 04 01 00 00    	js     2364 <submitr+0x18e>
    2260:	41 89 c4             	mov    %eax,%r12d
    2263:	4c 89 ef             	mov    %r13,%rdi
    2266:	e8 65 f0 ff ff       	call   12d0 <gethostbyname@plt>
    226b:	48 85 c0             	test   %rax,%rax
    226e:	0f 84 3f 01 00 00    	je     23b3 <submitr+0x1dd>
    2274:	4c 8d 6c 24 30       	lea    0x30(%rsp),%r13
    2279:	48 c7 44 24 32 00 00 	movq   $0x0,0x32(%rsp)
    2280:	00 00 
    2282:	48 c7 44 24 38 00 00 	movq   $0x0,0x38(%rsp)
    2289:	00 00 
    228b:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%rsp)
    2292:	48 63 50 14          	movslq 0x14(%rax),%rdx
    2296:	48 8b 40 18          	mov    0x18(%rax),%rax
    229a:	48 8b 30             	mov    (%rax),%rsi
    229d:	48 8d 7c 24 34       	lea    0x34(%rsp),%rdi
    22a2:	b9 0c 00 00 00       	mov    $0xc,%ecx
    22a7:	e8 34 f0 ff ff       	call   12e0 <__memmove_chk@plt>
    22ac:	66 c1 c5 08          	rol    $0x8,%bp
    22b0:	66 89 6c 24 32       	mov    %bp,0x32(%rsp)
    22b5:	ba 10 00 00 00       	mov    $0x10,%edx
    22ba:	4c 89 ee             	mov    %r13,%rsi
    22bd:	44 89 e7             	mov    %r12d,%edi
    22c0:	e8 bb f0 ff ff       	call   1380 <connect@plt>
    22c5:	85 c0                	test   %eax,%eax
    22c7:	0f 88 4b 01 00 00    	js     2418 <submitr+0x242>
    22cd:	48 89 df             	mov    %rbx,%rdi
    22d0:	e8 8b ef ff ff       	call   1260 <strlen@plt>
    22d5:	48 89 c5             	mov    %rax,%rbp
    22d8:	48 8b 3c 24          	mov    (%rsp),%rdi
    22dc:	e8 7f ef ff ff       	call   1260 <strlen@plt>
    22e1:	49 89 c6             	mov    %rax,%r14
    22e4:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
    22e9:	e8 72 ef ff ff       	call   1260 <strlen@plt>
    22ee:	49 89 c5             	mov    %rax,%r13
    22f1:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
    22f6:	e8 65 ef ff ff       	call   1260 <strlen@plt>
    22fb:	48 89 c2             	mov    %rax,%rdx
    22fe:	4b 8d 84 2e 80 00 00 	lea    0x80(%r14,%r13,1),%rax
    2305:	00 
    2306:	48 01 d0             	add    %rdx,%rax
    2309:	48 8d 54 6d 00       	lea    0x0(%rbp,%rbp,2),%rdx
    230e:	48 01 d0             	add    %rdx,%rax
    2311:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
    2317:	0f 87 52 01 00 00    	ja     246f <submitr+0x299>
    231d:	48 8d 94 24 50 40 00 	lea    0x4050(%rsp),%rdx
    2324:	00 
    2325:	b9 00 04 00 00       	mov    $0x400,%ecx
    232a:	b8 00 00 00 00       	mov    $0x0,%eax
    232f:	48 89 d7             	mov    %rdx,%rdi
    2332:	f3 48 ab             	rep stos %rax,%es:(%rdi)
    2335:	48 89 df             	mov    %rbx,%rdi
    2338:	e8 23 ef ff ff       	call   1260 <strlen@plt>
    233d:	85 c0                	test   %eax,%eax
    233f:	0f 84 47 02 00 00    	je     258c <submitr+0x3b6>
    2345:	8d 40 ff             	lea    -0x1(%rax),%eax
    2348:	4c 8d 6c 03 01       	lea    0x1(%rbx,%rax,1),%r13
    234d:	48 8d ac 24 50 40 00 	lea    0x4050(%rsp),%rbp
    2354:	00 
    2355:	49 be d9 ff 00 00 00 	movabs $0x2000000000ffd9,%r14
    235c:	00 20 00 
    235f:	e9 99 01 00 00       	jmp    24fd <submitr+0x327>
    2364:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    236b:	3a 20 43 
    236e:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2375:	20 75 6e 
    2378:	49 89 07             	mov    %rax,(%r15)
    237b:	49 89 57 08          	mov    %rdx,0x8(%r15)
    237f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2386:	74 6f 20 
    2389:	48 ba 63 72 65 61 74 	movabs $0x7320657461657263,%rdx
    2390:	65 20 73 
    2393:	49 89 47 10          	mov    %rax,0x10(%r15)
    2397:	49 89 57 18          	mov    %rdx,0x18(%r15)
    239b:	48 b8 20 73 6f 63 6b 	movabs $0x74656b636f7320,%rax
    23a2:	65 74 00 
    23a5:	49 89 47 1e          	mov    %rax,0x1e(%r15)
    23a9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    23ae:	e9 d4 04 00 00       	jmp    2887 <submitr+0x6b1>
    23b3:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
    23ba:	3a 20 44 
    23bd:	48 ba 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rdx
    23c4:	20 75 6e 
    23c7:	49 89 07             	mov    %rax,(%r15)
    23ca:	49 89 57 08          	mov    %rdx,0x8(%r15)
    23ce:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    23d5:	74 6f 20 
    23d8:	48 ba 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rdx
    23df:	76 65 20 
    23e2:	49 89 47 10          	mov    %rax,0x10(%r15)
    23e6:	49 89 57 18          	mov    %rdx,0x18(%r15)
    23ea:	48 b8 20 73 65 72 76 	movabs $0x2072657672657320,%rax
    23f1:	65 72 20 
    23f4:	48 ba 61 64 64 72 65 	movabs $0x73736572646461,%rdx
    23fb:	73 73 00 
    23fe:	49 89 47 1f          	mov    %rax,0x1f(%r15)
    2402:	49 89 57 27          	mov    %rdx,0x27(%r15)
    2406:	44 89 e7             	mov    %r12d,%edi
    2409:	e8 82 ee ff ff       	call   1290 <close@plt>
    240e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2413:	e9 6f 04 00 00       	jmp    2887 <submitr+0x6b1>
    2418:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
    241f:	3a 20 55 
    2422:	48 ba 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rdx
    2429:	20 74 6f 
    242c:	49 89 07             	mov    %rax,(%r15)
    242f:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2433:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
    243a:	65 63 74 
    243d:	48 ba 20 74 6f 20 74 	movabs $0x20656874206f7420,%rdx
    2444:	68 65 20 
    2447:	49 89 47 10          	mov    %rax,0x10(%r15)
    244b:	49 89 57 18          	mov    %rdx,0x18(%r15)
    244f:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
    2456:	65 72 00 
    2459:	49 89 47 1f          	mov    %rax,0x1f(%r15)
    245d:	44 89 e7             	mov    %r12d,%edi
    2460:	e8 2b ee ff ff       	call   1290 <close@plt>
    2465:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    246a:	e9 18 04 00 00       	jmp    2887 <submitr+0x6b1>
    246f:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
    2476:	3a 20 52 
    2479:	48 ba 65 73 75 6c 74 	movabs $0x747320746c757365,%rdx
    2480:	20 73 74 
    2483:	49 89 07             	mov    %rax,(%r15)
    2486:	49 89 57 08          	mov    %rdx,0x8(%r15)
    248a:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
    2491:	74 6f 6f 
    2494:	48 ba 20 6c 61 72 67 	movabs $0x202e656772616c20,%rdx
    249b:	65 2e 20 
    249e:	49 89 47 10          	mov    %rax,0x10(%r15)
    24a2:	49 89 57 18          	mov    %rdx,0x18(%r15)
    24a6:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
    24ad:	61 73 65 
    24b0:	48 ba 20 53 55 42 4d 	movabs $0x5254494d42555320,%rdx
    24b7:	49 54 52 
    24ba:	49 89 47 20          	mov    %rax,0x20(%r15)
    24be:	49 89 57 28          	mov    %rdx,0x28(%r15)
    24c2:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
    24c9:	55 46 00 
    24cc:	49 89 47 30          	mov    %rax,0x30(%r15)
    24d0:	44 89 e7             	mov    %r12d,%edi
    24d3:	e8 b8 ed ff ff       	call   1290 <close@plt>
    24d8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    24dd:	e9 a5 03 00 00       	jmp    2887 <submitr+0x6b1>
    24e2:	49 0f a3 c6          	bt     %rax,%r14
    24e6:	73 21                	jae    2509 <submitr+0x333>
    24e8:	44 88 45 00          	mov    %r8b,0x0(%rbp)
    24ec:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
    24f0:	48 83 c3 01          	add    $0x1,%rbx
    24f4:	49 39 dd             	cmp    %rbx,%r13
    24f7:	0f 84 8f 00 00 00    	je     258c <submitr+0x3b6>
    24fd:	44 0f b6 03          	movzbl (%rbx),%r8d
    2501:	41 8d 40 d6          	lea    -0x2a(%r8),%eax
    2505:	3c 35                	cmp    $0x35,%al
    2507:	76 d9                	jbe    24e2 <submitr+0x30c>
    2509:	44 89 c0             	mov    %r8d,%eax
    250c:	83 e0 df             	and    $0xffffffdf,%eax
    250f:	83 e8 41             	sub    $0x41,%eax
    2512:	3c 19                	cmp    $0x19,%al
    2514:	76 d2                	jbe    24e8 <submitr+0x312>
    2516:	41 80 f8 20          	cmp    $0x20,%r8b
    251a:	74 63                	je     257f <submitr+0x3a9>
    251c:	41 8d 40 e0          	lea    -0x20(%r8),%eax
    2520:	3c 5f                	cmp    $0x5f,%al
    2522:	76 0a                	jbe    252e <submitr+0x358>
    2524:	41 80 f8 09          	cmp    $0x9,%r8b
    2528:	0f 85 f5 03 00 00    	jne    2923 <submitr+0x74d>
    252e:	48 8d bc 24 50 80 00 	lea    0x8050(%rsp),%rdi
    2535:	00 
    2536:	45 0f b6 c0          	movzbl %r8b,%r8d
    253a:	48 8d 0d 49 0c 00 00 	lea    0xc49(%rip),%rcx        # 318a <_IO_stdin_used+0x18a>
    2541:	ba 08 00 00 00       	mov    $0x8,%edx
    2546:	be 02 00 00 00       	mov    $0x2,%esi
    254b:	b8 00 00 00 00       	mov    $0x0,%eax
    2550:	e8 6b ee ff ff       	call   13c0 <__sprintf_chk@plt>
    2555:	0f b6 84 24 50 80 00 	movzbl 0x8050(%rsp),%eax
    255c:	00 
    255d:	88 45 00             	mov    %al,0x0(%rbp)
    2560:	0f b6 84 24 51 80 00 	movzbl 0x8051(%rsp),%eax
    2567:	00 
    2568:	88 45 01             	mov    %al,0x1(%rbp)
    256b:	0f b6 84 24 52 80 00 	movzbl 0x8052(%rsp),%eax
    2572:	00 
    2573:	88 45 02             	mov    %al,0x2(%rbp)
    2576:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
    257a:	e9 71 ff ff ff       	jmp    24f0 <submitr+0x31a>
    257f:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
    2583:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
    2587:	e9 64 ff ff ff       	jmp    24f0 <submitr+0x31a>
    258c:	48 8d 9c 24 50 20 00 	lea    0x2050(%rsp),%rbx
    2593:	00 
    2594:	48 83 ec 08          	sub    $0x8,%rsp
    2598:	48 8d 84 24 58 40 00 	lea    0x4058(%rsp),%rax
    259f:	00 
    25a0:	50                   	push   %rax
    25a1:	ff 74 24 20          	push   0x20(%rsp)
    25a5:	ff 74 24 30          	push   0x30(%rsp)
    25a9:	4c 8b 4c 24 28       	mov    0x28(%rsp),%r9
    25ae:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
    25b3:	48 8d 0d ae 0e 00 00 	lea    0xeae(%rip),%rcx        # 3468 <_IO_stdin_used+0x468>
    25ba:	ba 00 20 00 00       	mov    $0x2000,%edx
    25bf:	be 02 00 00 00       	mov    $0x2,%esi
    25c4:	48 89 df             	mov    %rbx,%rdi
    25c7:	b8 00 00 00 00       	mov    $0x0,%eax
    25cc:	e8 ef ed ff ff       	call   13c0 <__sprintf_chk@plt>
    25d1:	48 83 c4 20          	add    $0x20,%rsp
    25d5:	48 89 df             	mov    %rbx,%rdi
    25d8:	e8 83 ec ff ff       	call   1260 <strlen@plt>
    25dd:	48 89 c3             	mov    %rax,%rbx
    25e0:	48 85 c0             	test   %rax,%rax
    25e3:	74 33                	je     2618 <submitr+0x442>
    25e5:	48 8d ac 24 50 20 00 	lea    0x2050(%rsp),%rbp
    25ec:	00 
    25ed:	eb 0e                	jmp    25fd <submitr+0x427>
    25ef:	e8 2c ec ff ff       	call   1220 <__errno_location@plt>
    25f4:	83 38 04             	cmpl   $0x4,(%rax)
    25f7:	0f 85 37 01 00 00    	jne    2734 <submitr+0x55e>
    25fd:	48 89 da             	mov    %rbx,%rdx
    2600:	48 89 ee             	mov    %rbp,%rsi
    2603:	44 89 e7             	mov    %r12d,%edi
    2606:	e8 45 ec ff ff       	call   1250 <write@plt>
    260b:	48 85 c0             	test   %rax,%rax
    260e:	7e df                	jle    25ef <submitr+0x419>
    2610:	48 01 c5             	add    %rax,%rbp
    2613:	48 29 c3             	sub    %rax,%rbx
    2616:	75 e5                	jne    25fd <submitr+0x427>
    2618:	44 89 64 24 40       	mov    %r12d,0x40(%rsp)
    261d:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%rsp)
    2624:	00 
    2625:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
    262a:	48 8d 44 24 50       	lea    0x50(%rsp),%rax
    262f:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
    2634:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
    263b:	00 
    263c:	ba 00 20 00 00       	mov    $0x2000,%edx
    2641:	e8 c6 fa ff ff       	call   210c <rio_readlineb>
    2646:	48 85 c0             	test   %rax,%rax
    2649:	0f 8e 4a 01 00 00    	jle    2799 <submitr+0x5c3>
    264f:	48 8d 4c 24 2c       	lea    0x2c(%rsp),%rcx
    2654:	48 8d 94 24 50 60 00 	lea    0x6050(%rsp),%rdx
    265b:	00 
    265c:	48 8d bc 24 50 20 00 	lea    0x2050(%rsp),%rdi
    2663:	00 
    2664:	4c 8d 84 24 50 80 00 	lea    0x8050(%rsp),%r8
    266b:	00 
    266c:	48 8d 35 1e 0b 00 00 	lea    0xb1e(%rip),%rsi        # 3191 <_IO_stdin_used+0x191>
    2673:	b8 00 00 00 00       	mov    $0x0,%eax
    2678:	e8 a3 ec ff ff       	call   1320 <__isoc99_sscanf@plt>
    267d:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
    2682:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
    2689:	0f 85 7a 01 00 00    	jne    2809 <submitr+0x633>
    268f:	48 8d 1d 0c 0b 00 00 	lea    0xb0c(%rip),%rbx        # 31a2 <_IO_stdin_used+0x1a2>
    2696:	48 8d bc 24 50 20 00 	lea    0x2050(%rsp),%rdi
    269d:	00 
    269e:	48 89 de             	mov    %rbx,%rsi
    26a1:	e8 0a ec ff ff       	call   12b0 <strcmp@plt>
    26a6:	85 c0                	test   %eax,%eax
    26a8:	0f 84 92 01 00 00    	je     2840 <submitr+0x66a>
    26ae:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
    26b5:	00 
    26b6:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
    26bb:	ba 00 20 00 00       	mov    $0x2000,%edx
    26c0:	e8 47 fa ff ff       	call   210c <rio_readlineb>
    26c5:	48 85 c0             	test   %rax,%rax
    26c8:	7f cc                	jg     2696 <submitr+0x4c0>
    26ca:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    26d1:	3a 20 43 
    26d4:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    26db:	20 75 6e 
    26de:	49 89 07             	mov    %rax,(%r15)
    26e1:	49 89 57 08          	mov    %rdx,0x8(%r15)
    26e5:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    26ec:	74 6f 20 
    26ef:	48 ba 72 65 61 64 20 	movabs $0x6165682064616572,%rdx
    26f6:	68 65 61 
    26f9:	49 89 47 10          	mov    %rax,0x10(%r15)
    26fd:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2701:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
    2708:	66 72 6f 
    270b:	48 ba 6d 20 73 65 72 	movabs $0x726576726573206d,%rdx
    2712:	76 65 72 
    2715:	49 89 47 20          	mov    %rax,0x20(%r15)
    2719:	49 89 57 28          	mov    %rdx,0x28(%r15)
    271d:	41 c6 47 30 00       	movb   $0x0,0x30(%r15)
    2722:	44 89 e7             	mov    %r12d,%edi
    2725:	e8 66 eb ff ff       	call   1290 <close@plt>
    272a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    272f:	e9 53 01 00 00       	jmp    2887 <submitr+0x6b1>
    2734:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    273b:	3a 20 43 
    273e:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2745:	20 75 6e 
    2748:	49 89 07             	mov    %rax,(%r15)
    274b:	49 89 57 08          	mov    %rdx,0x8(%r15)
    274f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2756:	74 6f 20 
    2759:	48 ba 77 72 69 74 65 	movabs $0x6f74206574697277,%rdx
    2760:	20 74 6f 
    2763:	49 89 47 10          	mov    %rax,0x10(%r15)
    2767:	49 89 57 18          	mov    %rdx,0x18(%r15)
    276b:	48 b8 65 20 74 6f 20 	movabs $0x656874206f742065,%rax
    2772:	74 68 65 
    2775:	48 ba 20 73 65 72 76 	movabs $0x72657672657320,%rdx
    277c:	65 72 00 
    277f:	49 89 47 1c          	mov    %rax,0x1c(%r15)
    2783:	49 89 57 24          	mov    %rdx,0x24(%r15)
    2787:	44 89 e7             	mov    %r12d,%edi
    278a:	e8 01 eb ff ff       	call   1290 <close@plt>
    278f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2794:	e9 ee 00 00 00       	jmp    2887 <submitr+0x6b1>
    2799:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    27a0:	3a 20 43 
    27a3:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    27aa:	20 75 6e 
    27ad:	49 89 07             	mov    %rax,(%r15)
    27b0:	49 89 57 08          	mov    %rdx,0x8(%r15)
    27b4:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    27bb:	74 6f 20 
    27be:	48 ba 72 65 61 64 20 	movabs $0x7269662064616572,%rdx
    27c5:	66 69 72 
    27c8:	49 89 47 10          	mov    %rax,0x10(%r15)
    27cc:	49 89 57 18          	mov    %rdx,0x18(%r15)
    27d0:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
    27d7:	61 64 65 
    27da:	48 ba 72 20 66 72 6f 	movabs $0x73206d6f72662072,%rdx
    27e1:	6d 20 73 
    27e4:	49 89 47 20          	mov    %rax,0x20(%r15)
    27e8:	49 89 57 28          	mov    %rdx,0x28(%r15)
    27ec:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
    27f3:	65 72 00 
    27f6:	49 89 47 2e          	mov    %rax,0x2e(%r15)
    27fa:	44 89 e7             	mov    %r12d,%edi
    27fd:	e8 8e ea ff ff       	call   1290 <close@plt>
    2802:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2807:	eb 7e                	jmp    2887 <submitr+0x6b1>
    2809:	4c 8d 8c 24 50 80 00 	lea    0x8050(%rsp),%r9
    2810:	00 
    2811:	48 8d 0d a8 0c 00 00 	lea    0xca8(%rip),%rcx        # 34c0 <_IO_stdin_used+0x4c0>
    2818:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
    281f:	be 02 00 00 00       	mov    $0x2,%esi
    2824:	4c 89 ff             	mov    %r15,%rdi
    2827:	b8 00 00 00 00       	mov    $0x0,%eax
    282c:	e8 8f eb ff ff       	call   13c0 <__sprintf_chk@plt>
    2831:	44 89 e7             	mov    %r12d,%edi
    2834:	e8 57 ea ff ff       	call   1290 <close@plt>
    2839:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    283e:	eb 47                	jmp    2887 <submitr+0x6b1>
    2840:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
    2847:	00 
    2848:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
    284d:	ba 00 20 00 00       	mov    $0x2000,%edx
    2852:	e8 b5 f8 ff ff       	call   210c <rio_readlineb>
    2857:	48 85 c0             	test   %rax,%rax
    285a:	7e 54                	jle    28b0 <submitr+0x6da>
    285c:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
    2863:	00 
    2864:	4c 89 ff             	mov    %r15,%rdi
    2867:	e8 c4 e9 ff ff       	call   1230 <strcpy@plt>
    286c:	44 89 e7             	mov    %r12d,%edi
    286f:	e8 1c ea ff ff       	call   1290 <close@plt>
    2874:	48 8d 35 2a 09 00 00 	lea    0x92a(%rip),%rsi        # 31a5 <_IO_stdin_used+0x1a5>
    287b:	4c 89 ff             	mov    %r15,%rdi
    287e:	e8 2d ea ff ff       	call   12b0 <strcmp@plt>
    2883:	f7 d8                	neg    %eax
    2885:	19 c0                	sbb    %eax,%eax
    2887:	48 8b 94 24 58 a0 00 	mov    0xa058(%rsp),%rdx
    288e:	00 
    288f:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    2896:	00 00 
    2898:	0f 85 0e 01 00 00    	jne    29ac <submitr+0x7d6>
    289e:	48 81 c4 68 a0 00 00 	add    $0xa068,%rsp
    28a5:	5b                   	pop    %rbx
    28a6:	5d                   	pop    %rbp
    28a7:	41 5c                	pop    %r12
    28a9:	41 5d                	pop    %r13
    28ab:	41 5e                	pop    %r14
    28ad:	41 5f                	pop    %r15
    28af:	c3                   	ret
    28b0:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    28b7:	3a 20 43 
    28ba:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    28c1:	20 75 6e 
    28c4:	49 89 07             	mov    %rax,(%r15)
    28c7:	49 89 57 08          	mov    %rdx,0x8(%r15)
    28cb:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    28d2:	74 6f 20 
    28d5:	48 ba 72 65 61 64 20 	movabs $0x6174732064616572,%rdx
    28dc:	73 74 61 
    28df:	49 89 47 10          	mov    %rax,0x10(%r15)
    28e3:	49 89 57 18          	mov    %rdx,0x18(%r15)
    28e7:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
    28ee:	65 73 73 
    28f1:	48 ba 61 67 65 20 66 	movabs $0x6d6f726620656761,%rdx
    28f8:	72 6f 6d 
    28fb:	49 89 47 20          	mov    %rax,0x20(%r15)
    28ff:	49 89 57 28          	mov    %rdx,0x28(%r15)
    2903:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
    290a:	65 72 00 
    290d:	49 89 47 30          	mov    %rax,0x30(%r15)
    2911:	44 89 e7             	mov    %r12d,%edi
    2914:	e8 77 e9 ff ff       	call   1290 <close@plt>
    2919:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    291e:	e9 64 ff ff ff       	jmp    2887 <submitr+0x6b1>
    2923:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
    292a:	3a 20 52 
    292d:	48 ba 65 73 75 6c 74 	movabs $0x747320746c757365,%rdx
    2934:	20 73 74 
    2937:	49 89 07             	mov    %rax,(%r15)
    293a:	49 89 57 08          	mov    %rdx,0x8(%r15)
    293e:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
    2945:	63 6f 6e 
    2948:	48 ba 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rdx
    294f:	20 61 6e 
    2952:	49 89 47 10          	mov    %rax,0x10(%r15)
    2956:	49 89 57 18          	mov    %rdx,0x18(%r15)
    295a:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
    2961:	67 61 6c 
    2964:	48 ba 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rdx
    296b:	6e 70 72 
    296e:	49 89 47 20          	mov    %rax,0x20(%r15)
    2972:	49 89 57 28          	mov    %rdx,0x28(%r15)
    2976:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
    297d:	6c 65 20 
    2980:	48 ba 63 68 61 72 61 	movabs $0x6574636172616863,%rdx
    2987:	63 74 65 
    298a:	49 89 47 30          	mov    %rax,0x30(%r15)
    298e:	49 89 57 38          	mov    %rdx,0x38(%r15)
    2992:	41 c7 47 3f 65 72 2e 	movl   $0x2e7265,0x3f(%r15)
    2999:	00 
    299a:	44 89 e7             	mov    %r12d,%edi
    299d:	e8 ee e8 ff ff       	call   1290 <close@plt>
    29a2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    29a7:	e9 db fe ff ff       	jmp    2887 <submitr+0x6b1>
    29ac:	e8 bf e8 ff ff       	call   1270 <__stack_chk_fail@plt>

00000000000029b1 <init_timeout>:
    29b1:	f3 0f 1e fa          	endbr64
    29b5:	85 ff                	test   %edi,%edi
    29b7:	75 01                	jne    29ba <init_timeout+0x9>
    29b9:	c3                   	ret
    29ba:	53                   	push   %rbx
    29bb:	89 fb                	mov    %edi,%ebx
    29bd:	48 8d 35 12 f7 ff ff 	lea    -0x8ee(%rip),%rsi        # 20d6 <sigalrm_handler>
    29c4:	bf 0e 00 00 00       	mov    $0xe,%edi
    29c9:	e8 f2 e8 ff ff       	call   12c0 <signal@plt>
    29ce:	85 db                	test   %ebx,%ebx
    29d0:	b8 00 00 00 00       	mov    $0x0,%eax
    29d5:	0f 49 c3             	cmovns %ebx,%eax
    29d8:	89 c7                	mov    %eax,%edi
    29da:	e8 a1 e8 ff ff       	call   1280 <alarm@plt>
    29df:	5b                   	pop    %rbx
    29e0:	c3                   	ret

00000000000029e1 <init_driver>:
    29e1:	f3 0f 1e fa          	endbr64
    29e5:	41 54                	push   %r12
    29e7:	55                   	push   %rbp
    29e8:	53                   	push   %rbx
    29e9:	48 83 ec 20          	sub    $0x20,%rsp
    29ed:	48 89 fd             	mov    %rdi,%rbp
    29f0:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    29f7:	00 00 
    29f9:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
    29fe:	31 c0                	xor    %eax,%eax
    2a00:	be 01 00 00 00       	mov    $0x1,%esi
    2a05:	bf 0d 00 00 00       	mov    $0xd,%edi
    2a0a:	e8 b1 e8 ff ff       	call   12c0 <signal@plt>
    2a0f:	be 01 00 00 00       	mov    $0x1,%esi
    2a14:	bf 1d 00 00 00       	mov    $0x1d,%edi
    2a19:	e8 a2 e8 ff ff       	call   12c0 <signal@plt>
    2a1e:	be 01 00 00 00       	mov    $0x1,%esi
    2a23:	bf 1d 00 00 00       	mov    $0x1d,%edi
    2a28:	e8 93 e8 ff ff       	call   12c0 <signal@plt>
    2a2d:	ba 00 00 00 00       	mov    $0x0,%edx
    2a32:	be 01 00 00 00       	mov    $0x1,%esi
    2a37:	bf 02 00 00 00       	mov    $0x2,%edi
    2a3c:	e8 8f e9 ff ff       	call   13d0 <socket@plt>
    2a41:	85 c0                	test   %eax,%eax
    2a43:	0f 88 9d 00 00 00    	js     2ae6 <init_driver+0x105>
    2a49:	89 c3                	mov    %eax,%ebx
    2a4b:	48 8d 3d 56 07 00 00 	lea    0x756(%rip),%rdi        # 31a8 <_IO_stdin_used+0x1a8>
    2a52:	e8 79 e8 ff ff       	call   12d0 <gethostbyname@plt>
    2a57:	48 85 c0             	test   %rax,%rax
    2a5a:	0f 84 d3 00 00 00    	je     2b33 <init_driver+0x152>
    2a60:	49 89 e4             	mov    %rsp,%r12
    2a63:	48 c7 44 24 02 00 00 	movq   $0x0,0x2(%rsp)
    2a6a:	00 00 
    2a6c:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
    2a73:	00 00 
    2a75:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
    2a7b:	48 63 50 14          	movslq 0x14(%rax),%rdx
    2a7f:	48 8b 40 18          	mov    0x18(%rax),%rax
    2a83:	48 8b 30             	mov    (%rax),%rsi
    2a86:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
    2a8b:	b9 0c 00 00 00       	mov    $0xc,%ecx
    2a90:	e8 4b e8 ff ff       	call   12e0 <__memmove_chk@plt>
    2a95:	66 c7 44 24 02 0f a1 	movw   $0xa10f,0x2(%rsp)
    2a9c:	ba 10 00 00 00       	mov    $0x10,%edx
    2aa1:	4c 89 e6             	mov    %r12,%rsi
    2aa4:	89 df                	mov    %ebx,%edi
    2aa6:	e8 d5 e8 ff ff       	call   1380 <connect@plt>
    2aab:	85 c0                	test   %eax,%eax
    2aad:	0f 88 e5 00 00 00    	js     2b98 <init_driver+0x1b7>
    2ab3:	89 df                	mov    %ebx,%edi
    2ab5:	e8 d6 e7 ff ff       	call   1290 <close@plt>
    2aba:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
    2ac0:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
    2ac4:	b8 00 00 00 00       	mov    $0x0,%eax
    2ac9:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
    2ace:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    2ad5:	00 00 
    2ad7:	0f 85 f3 00 00 00    	jne    2bd0 <init_driver+0x1ef>
    2add:	48 83 c4 20          	add    $0x20,%rsp
    2ae1:	5b                   	pop    %rbx
    2ae2:	5d                   	pop    %rbp
    2ae3:	41 5c                	pop    %r12
    2ae5:	c3                   	ret
    2ae6:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    2aed:	3a 20 43 
    2af0:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2af7:	20 75 6e 
    2afa:	48 89 45 00          	mov    %rax,0x0(%rbp)
    2afe:	48 89 55 08          	mov    %rdx,0x8(%rbp)
    2b02:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2b09:	74 6f 20 
    2b0c:	48 ba 63 72 65 61 74 	movabs $0x7320657461657263,%rdx
    2b13:	65 20 73 
    2b16:	48 89 45 10          	mov    %rax,0x10(%rbp)
    2b1a:	48 89 55 18          	mov    %rdx,0x18(%rbp)
    2b1e:	48 b8 20 73 6f 63 6b 	movabs $0x74656b636f7320,%rax
    2b25:	65 74 00 
    2b28:	48 89 45 1e          	mov    %rax,0x1e(%rbp)
    2b2c:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2b31:	eb 96                	jmp    2ac9 <init_driver+0xe8>
    2b33:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
    2b3a:	3a 20 44 
    2b3d:	48 ba 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rdx
    2b44:	20 75 6e 
    2b47:	48 89 45 00          	mov    %rax,0x0(%rbp)
    2b4b:	48 89 55 08          	mov    %rdx,0x8(%rbp)
    2b4f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2b56:	74 6f 20 
    2b59:	48 ba 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rdx
    2b60:	76 65 20 
    2b63:	48 89 45 10          	mov    %rax,0x10(%rbp)
    2b67:	48 89 55 18          	mov    %rdx,0x18(%rbp)
    2b6b:	48 b8 20 73 65 72 76 	movabs $0x2072657672657320,%rax
    2b72:	65 72 20 
    2b75:	48 ba 61 64 64 72 65 	movabs $0x73736572646461,%rdx
    2b7c:	73 73 00 
    2b7f:	48 89 45 1f          	mov    %rax,0x1f(%rbp)
    2b83:	48 89 55 27          	mov    %rdx,0x27(%rbp)
    2b87:	89 df                	mov    %ebx,%edi
    2b89:	e8 02 e7 ff ff       	call   1290 <close@plt>
    2b8e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2b93:	e9 31 ff ff ff       	jmp    2ac9 <init_driver+0xe8>
    2b98:	4c 8d 05 09 06 00 00 	lea    0x609(%rip),%r8        # 31a8 <_IO_stdin_used+0x1a8>
    2b9f:	48 8d 0d 4a 09 00 00 	lea    0x94a(%rip),%rcx        # 34f0 <_IO_stdin_used+0x4f0>
    2ba6:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
    2bad:	be 02 00 00 00       	mov    $0x2,%esi
    2bb2:	48 89 ef             	mov    %rbp,%rdi
    2bb5:	b8 00 00 00 00       	mov    $0x0,%eax
    2bba:	e8 01 e8 ff ff       	call   13c0 <__sprintf_chk@plt>
    2bbf:	89 df                	mov    %ebx,%edi
    2bc1:	e8 ca e6 ff ff       	call   1290 <close@plt>
    2bc6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2bcb:	e9 f9 fe ff ff       	jmp    2ac9 <init_driver+0xe8>
    2bd0:	e8 9b e6 ff ff       	call   1270 <__stack_chk_fail@plt>

0000000000002bd5 <driver_post>:
    2bd5:	f3 0f 1e fa          	endbr64
    2bd9:	53                   	push   %rbx
    2bda:	4c 89 c3             	mov    %r8,%rbx
    2bdd:	85 c9                	test   %ecx,%ecx
    2bdf:	75 17                	jne    2bf8 <driver_post+0x23>
    2be1:	48 85 ff             	test   %rdi,%rdi
    2be4:	74 05                	je     2beb <driver_post+0x16>
    2be6:	80 3f 00             	cmpb   $0x0,(%rdi)
    2be9:	75 33                	jne    2c1e <driver_post+0x49>
    2beb:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
    2bf0:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
    2bf4:	89 c8                	mov    %ecx,%eax
    2bf6:	5b                   	pop    %rbx
    2bf7:	c3                   	ret
    2bf8:	48 8d 35 b9 05 00 00 	lea    0x5b9(%rip),%rsi        # 31b8 <_IO_stdin_used+0x1b8>
    2bff:	bf 02 00 00 00       	mov    $0x2,%edi
    2c04:	b8 00 00 00 00       	mov    $0x0,%eax
    2c09:	e8 32 e7 ff ff       	call   1340 <__printf_chk@plt>
    2c0e:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
    2c13:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
    2c17:	b8 00 00 00 00       	mov    $0x0,%eax
    2c1c:	eb d8                	jmp    2bf6 <driver_post+0x21>
    2c1e:	41 50                	push   %r8
    2c20:	52                   	push   %rdx
    2c21:	4c 8d 0d a7 05 00 00 	lea    0x5a7(%rip),%r9        # 31cf <_IO_stdin_used+0x1cf>
    2c28:	49 89 f0             	mov    %rsi,%r8
    2c2b:	48 89 f9             	mov    %rdi,%rcx
    2c2e:	48 8d 15 9e 05 00 00 	lea    0x59e(%rip),%rdx        # 31d3 <_IO_stdin_used+0x1d3>
    2c35:	be a1 0f 00 00       	mov    $0xfa1,%esi
    2c3a:	48 8d 3d 67 05 00 00 	lea    0x567(%rip),%rdi        # 31a8 <_IO_stdin_used+0x1a8>
    2c41:	e8 90 f5 ff ff       	call   21d6 <submitr>
    2c46:	48 83 c4 10          	add    $0x10,%rsp
    2c4a:	eb aa                	jmp    2bf6 <driver_post+0x21>

Disassembly of section .fini:

0000000000002c4c <_fini>:
    2c4c:	f3 0f 1e fa          	endbr64
    2c50:	48 83 ec 08          	sub    $0x8,%rsp
    2c54:	48 83 c4 08          	add    $0x8,%rsp
    2c58:	c3                   	ret
