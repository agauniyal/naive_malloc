```
$ clang++ main.cpp -std=c++17 -Wall -Wextra -stdlib=libc++
$ valgrind ./a.out
==23493== Memcheck, a memory error detector
==23493== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==23493== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==23493== Command: ./a.out
==23493==
1: 0x4227018
2: 0x4227018
3: 0x4227018
4: 0x4227018
5: 0x4227018
==23493==
==23493== HEAP SUMMARY:
==23493==     in use at exit: 0 bytes in 0 blocks
==23493==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==23493==
==23493== All heap blocks were freed -- no leaks are possible
==23493==
==23493== For counts of detected and suppressed errors, rerun with: -v
==23493== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
