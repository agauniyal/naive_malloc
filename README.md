```
$ clang++ main.cpp -std=c++17 -Wall -Wextra -stdlib=libc++
$ valgrind ./a.out
==24271== Memcheck, a memory error detector
==24271== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24271== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24271== Command: ./a.out
==24271==
3: 0x4227018
4: 0x4227048
1: 0x4227018
5: 0x4227080
2: 0x4227018
==24271==
==24271== HEAP SUMMARY:
==24271==     in use at exit: 0 bytes in 0 blocks
==24271==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==24271==
==24271== All heap blocks were freed -- no leaks are possible
==24271==
==24271== For counts of detected and suppressed errors, rerun with: -v
==24271== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
