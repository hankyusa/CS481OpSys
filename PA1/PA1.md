# Operating Systems Progamming Assignment 1

by Luke Hanks

## Part 1

```
$ strace ./myCode
execve("./myCode", ["./myCode"], [/* 46 vars */]) = 0
brk(NULL)                               = 0xbc6000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=299248, ...}) = 0
mmap(NULL, 299248, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f95e91ed000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f95e91ec000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f95e8c48000
mprotect(0x7f95e8e08000, 2097152, PROT_NONE) = 0
mmap(0x7f95e9008000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7f95e9008000
mmap(0x7f95e900e000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f95e900e000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f95e91eb000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f95e91ea000
arch_prctl(ARCH_SET_FS, 0x7f95e91eb700) = 0
mprotect(0x7f95e9008000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f95e9237000, 4096, PROT_READ) = 0
munmap(0x7f95e91ed000, 299248)          = 0
brk(NULL)                               = 0xbc6000
brk(0xbe7000)                           = 0xbe7000
open("myTstFile", O_RDWR)               = -1 ENOENT (No such file or directory)
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 6), ...}) = 0
write(1, "\n", 1
)                       = 1
write(1, " Program Failed, figure out why."..., 35 Program Failed, figure out why...
) = 35
exit_group(0)                           = ?
+++ exited with 0 +++

$ strace -c ./myCode

 Program Failed, figure out why...
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 31.14    0.000071          24         3         1 open
 16.67    0.000038           5         7           mmap
 15.35    0.000035           9         4           mprotect
  9.21    0.000021          11         2           write
  9.21    0.000021          21         1           munmap
  7.02    0.000016           5         3         3 access
  3.51    0.000008           3         3           brk
  3.07    0.000007           2         3           fstat
  1.75    0.000004           4         1           execve
  1.32    0.000003           3         1           read
  0.88    0.000002           1         2           close
  0.88    0.000002           2         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000228                    31         4 total
```

Most called system calls:

1. open
2. mmap
3. mprotect
4. write
5. munmap

I beleive that `open` caused the program to fail because *myTstFile* isn't in the working directory.

```
$ strace ./myCode
execve("./myCode", ["./myCode"], [/* 46 vars */]) = 0
brk(NULL)                               = 0x12f4000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=299248, ...}) = 0
mmap(NULL, 299248, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f4450c48000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4450c47000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f44506a3000
mprotect(0x7f4450863000, 2097152, PROT_NONE) = 0
mmap(0x7f4450a63000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7f4450a63000
mmap(0x7f4450a69000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f4450a69000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4450c46000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4450c45000
arch_prctl(ARCH_SET_FS, 0x7f4450c46700) = 0
mprotect(0x7f4450a63000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f4450c92000, 4096, PROT_READ) = 0
munmap(0x7f4450c48000, 299248)          = 0
brk(NULL)                               = 0x12f4000
brk(0x1315000)                          = 0x1315000
open("myTstFile", O_RDWR)               = 3
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 6), ...}) = 0
write(1, "\n", 1
)                       = 1
write(1, " Simple pie value 3.14159012\n", 29 Simple pie value 3.14159012
) = 29
fstat(3, {st_mode=S_IFREG|0644, st_size=1055, ...}) = 0
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "9.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "17.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "18.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "15.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "28.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "39.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "17.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "75.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "12.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "23.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "80.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "120.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "45.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "93.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "105.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "39.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "117.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "23.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "171.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "157.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "210.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "51.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "55.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "84.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "199.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "148.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "273.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "65.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "67.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "267.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "309.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "248.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "111.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "225.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "41.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "81.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "363.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "126.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "45.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "390.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "179.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "318.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "371.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "191.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "243.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "153.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "309.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "55.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "327.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "168.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "115.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "351.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "62.141590\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "303.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "308.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "251.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "444.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "387.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "328.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "399.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "606.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "207.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "486.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "283.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "358.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "147.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "368.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "299.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "528.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "307.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "311.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "237.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "563.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "651.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "495.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "667.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "675.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "343.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "261.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "90.141586\n", 10)             = 10
write(1, ".", 1.)                        = 1
write(3, "355.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "804.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "183.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "3.141590\n", 9)               = 9
write(1, ".", 1.)                        = 1
write(3, "555.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "747.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "849.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "193.141586\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "579.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "585.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "395.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
write(3, "894.141602\n", 11)            = 11
write(1, ".", 1.)                        = 1
close(3)                                = 0
write(1, "\n", 1
)                       = 1
write(1, " Program successful ends\n", 25 Program successful ends
) = 25
exit_group(0)                           = ?
+++ exited with 0 +++

$ strace -c ./myCode

 Simple pie value 3.14159012
....................................................................................................
 Program successful ends
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 97.82    0.002158          11       204           write
  2.18    0.000048          16         3           close
  0.00    0.000000           0         1           read
  0.00    0.000000           0         3           open
  0.00    0.000000           0         4           fstat
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         3         3 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.002206                   235         3 total
```

Most used is `write`. 

`fopen` is not a system call. It is most correlated with the `open` system call.

`fprint` is not a system call. It is most correlated with the `write` system call.

## Part 2

```
$ strace -c cal
   September 2018     
Su Mo Tu We Th Fr Sa  
                   1  
 2  3  4  5  6  7  8  
 9 10 11 12 13 14 15  
16 17 18 19 20 21 22  
23 24 25 26 27 28 29  
30                    
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 27.65    0.000128           8        16           write
 15.77    0.000073           6        12           mmap
 11.88    0.000055           8         7           open
  9.72    0.000045           8         6           mprotect
  9.07    0.000042           8         5         1 stat
  5.40    0.000025           4         6         5 access
  4.75    0.000022          22         1           munmap
  4.10    0.000019           3         6           read
  4.10    0.000019           2         9           fstat
  2.16    0.000010           1         7           close
  2.16    0.000010           2         5           ioctl
  1.73    0.000008           3         3           brk
  0.65    0.000003           3         1           execve
  0.43    0.000002           2         1           lseek
  0.43    0.000002           2         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000463                    86         6 total

```
`write` is used to write to a file or to the terminal. `mmap` is used to map some number of bytes into memory. `open` is used to open files.

# Part 3

```
$ strace ls
execve("/bin/ls", ["ls"], [/* 46 vars */]) = 0
brk(NULL)                               = 0x1de5000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=299248, ...}) = 0
mmap(NULL, 299248, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7feaf95e5000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260Z\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=130224, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7feaf95e4000
mmap(NULL, 2234080, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7feaf91e8000
mprotect(0x7feaf9207000, 2093056, PROT_NONE) = 0
mmap(0x7feaf9406000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e000) = 0x7feaf9406000
mmap(0x7feaf9408000, 5856, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7feaf9408000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7feaf8e1e000
mprotect(0x7feaf8fde000, 2097152, PROT_NONE) = 0
mmap(0x7feaf91de000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7feaf91de000
mmap(0x7feaf91e4000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7feaf91e4000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libpcre.so.3", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000\25\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=456632, ...}) = 0
mmap(NULL, 2552072, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7feaf8bae000
mprotect(0x7feaf8c1c000, 2097152, PROT_NONE) = 0
mmap(0x7feaf8e1c000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6e000) = 0x7feaf8e1c000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libdl.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\240\r\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=14608, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7feaf95e3000
mmap(NULL, 2109680, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7feaf89aa000
mprotect(0x7feaf89ad000, 2093056, PROT_NONE) = 0
mmap(0x7feaf8bac000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7feaf8bac000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libpthread.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260`\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=138696, ...}) = 0
mmap(NULL, 2212904, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7feaf878d000
mprotect(0x7feaf87a5000, 2093056, PROT_NONE) = 0
mmap(0x7feaf89a4000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17000) = 0x7feaf89a4000
mmap(0x7feaf89a6000, 13352, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7feaf89a6000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7feaf95e2000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7feaf95e0000
arch_prctl(ARCH_SET_FS, 0x7feaf95e0800) = 0
mprotect(0x7feaf91de000, 16384, PROT_READ) = 0
mprotect(0x7feaf89a4000, 4096, PROT_READ) = 0
mprotect(0x7feaf8bac000, 4096, PROT_READ) = 0
mprotect(0x7feaf8e1c000, 4096, PROT_READ) = 0
mprotect(0x7feaf9406000, 4096, PROT_READ) = 0
mprotect(0x61d000, 4096, PROT_READ)     = 0
mprotect(0x7feaf962f000, 4096, PROT_READ) = 0
munmap(0x7feaf95e5000, 299248)          = 0
set_tid_address(0x7feaf95e0ad0)         = 23839
set_robust_list(0x7feaf95e0ae0, 24)     = 0
rt_sigaction(SIGRTMIN, {0x7feaf8792b50, [], SA_RESTORER|SA_SIGINFO, 0x7feaf879e390}, NULL, 8) = 0
rt_sigaction(SIGRT_1, {0x7feaf8792be0, [], SA_RESTORER|SA_RESTART|SA_SIGINFO, 0x7feaf879e390}, NULL, 8) = 0
rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
getrlimit(RLIMIT_STACK, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
statfs("/sys/fs/selinux", 0x7fff4ec89f40) = -1 ENOENT (No such file or directory)
statfs("/selinux", 0x7fff4ec89f40)      = -1 ENOENT (No such file or directory)
brk(NULL)                               = 0x1de5000
brk(0x1e06000)                          = 0x1e06000
open("/proc/filesystems", O_RDONLY)     = 3
fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
read(3, "nodev\tsysfs\nnodev\trootfs\nnodev\tr"..., 1024) = 515
read(3, "", 1024)                       = 0
close(3)                                = 0
open("/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=2981280, ...}) = 0
mmap(NULL, 2981280, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7feaf84b5000
close(3)                                = 0
ioctl(1, TCGETS, {B38400 opost isig icanon echo ...}) = 0
ioctl(1, TIOCGWINSZ, {ws_row=24, ws_col=184, ws_xpixel=0, ws_ypixel=0}) = 0
open(".", O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
getdents(3, /* 7 entries */, 32768)     = 208
getdents(3, /* 0 entries */, 32768)     = 0
close(3)                                = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 6), ...}) = 0
write(1, "myCode\tmyCode.c  myTstFile  PA1."..., 45myCode	myCode.c  myTstFile  PA1.md  PA-1.pdf
) = 45
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++

$ ltrace ls
malloc(552)                                                                                                       = 0x1e46010
malloc(120)                                                                                                       = 0x1e46240
malloc(1024)                                                                                                      = 0x1e462c0
free(0x1e462c0)                                                                                                   = <void>
free(0x1e46010)                                                                                                   = <void>
__libc_start_main(0x402a00, 1, 0x7ffc24e42a28, 0x413bb0 <unfinished ...>
strrchr("ls", '/')                                                                                                = nil
setlocale(LC_ALL, "" <unfinished ...>
malloc(5)                                                                                                         = 0x1e46010
free(0x1e46010)                                                                                                   = <void>
malloc(120)                                                                                                       = 0x1e46030
malloc(12)                                                                                                        = 0x1e46010
malloc(776)                                                                                                       = 0x1e460b0
malloc(112)                                                                                                       = 0x1e463c0
malloc(952)                                                                                                       = 0x1e46440
malloc(216)                                                                                                       = 0x1e46800
malloc(432)                                                                                                       = 0x1e468e0
malloc(104)                                                                                                       = 0x1e46aa0
malloc(88)                                                                                                        = 0x1e46b10
malloc(120)                                                                                                       = 0x1e46b70
malloc(168)                                                                                                       = 0x1e46bf0
malloc(104)                                                                                                       = 0x1e46ca0
malloc(80)                                                                                                        = 0x1e46d10
malloc(192)                                                                                                       = 0x1e46d70
malloc(12)                                                                                                        = 0x1e46e40
malloc(12)                                                                                                        = 0x1e46e60
malloc(12)                                                                                                        = 0x1e46e80
malloc(12)                                                                                                        = 0x1e46ea0
malloc(12)                                                                                                        = 0x1e46ec0
malloc(12)                                                                                                        = 0x1e46ee0
malloc(12)                                                                                                        = 0x1e46f00
malloc(12)                                                                                                        = 0x1e46f20
malloc(12)                                                                                                        = 0x1e46f40
malloc(12)                                                                                                        = 0x1e46f60
malloc(12)                                                                                                        = 0x1e46f80
malloc(12)                                                                                                        = 0x1e46fa0
malloc(12)                                                                                                        = 0x1e46fc0
free(0)                                                                                                           = <void>
free(0)                                                                                                           = <void>
<... setlocale resumed> )                                                                                         = "en_US.UTF-8"
bindtextdomain("coreutils", "/usr/share/locale" <unfinished ...>
malloc(34)                                                                                                        = 0x1e46fe0
<... bindtextdomain resumed> )                                                                                    = "/usr/share/locale"
textdomain("coreutils" <unfinished ...>
malloc(10)                                                                                                        = 0x1e47010
<... textdomain resumed> )                                                                                        = "coreutils"
__cxa_atexit(0x40a320, 0, 0, 0)                                                                                   = 0
isatty(1)                                                                                                         = 1
getenv("QUOTING_STYLE")                                                                                           = nil
getenv("COLUMNS")                                                                                                 = nil
ioctl(1, 21523, 0x7ffc24e425c0)                                                                                   = 0
getenv("TABSIZE")                                                                                                 = nil
getopt_long(1, 0x7ffc24e42a28, "abcdfghiklmnopqrstuvw:xABCDFGHI:"..., 0x414da0, -1)                               = -1
getenv("LS_BLOCK_SIZE")                                                                                           = nil
getenv("BLOCK_SIZE")                                                                                              = nil
getenv("BLOCKSIZE")                                                                                               = nil
getenv("POSIXLY_CORRECT")                                                                                         = nil
getenv("BLOCK_SIZE")                                                                                              = nil
__errno_location()                                                                                                = 0x7f49c74056b8
malloc(56)                                                                                                        = 0x1e47030
memcpy(0x1e47030, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 56)                      = 0x1e47030
__errno_location()                                                                                                = 0x7f49c74056b8
malloc(56)                                                                                                        = 0x1e47070
memcpy(0x1e47070, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 56)                      = 0x1e47070
getenv("TZ")                                                                                                      = nil
malloc(128)                                                                                                       = 0x1e470b0
malloc(19200)                                                                                                     = 0x1e47140
malloc(32)                                                                                                        = 0x1e4bc50
strlen(".")                                                                                                       = 1
malloc(2)                                                                                                         = 0x1e4bc80
memcpy(0x1e4bc80, ".\0", 2)                                                                                       = 0x1e4bc80
__errno_location()                                                                                                = 0x7f49c74056b8
opendir("." <unfinished ...>
malloc(32816)                                                                                                     = 0x1e4bca0
<... opendir resumed> )                                                                                           = 0x1e4bca0
readdir(0x1e4bca0)                                                                                                = 0x1e4bcd0
readdir(0x1e4bca0)                                                                                                = 0x1e4bce8
readdir(0x1e4bca0)                                                                                                = 0x1e4bd00
strlen("myCode")                                                                                                  = 6
malloc(7)                                                                                                         = 0x1e53ce0
memcpy(0x1e53ce0, "myCode\0", 7)                                                                                  = 0x1e53ce0
readdir(0x1e4bca0)                                                                                                = 0x1e4bd20
strlen("PA-1.pdf")                                                                                                = 8
malloc(9)                                                                                                         = 0x1e53d00
memcpy(0x1e53d00, "PA-1.pdf\0", 9)                                                                                = 0x1e53d00
readdir(0x1e4bca0)                                                                                                = 0x1e4bd40
strlen("myTstFile")                                                                                               = 9
malloc(10)                                                                                                        = 0x1e53d20
memcpy(0x1e53d20, "myTstFile\0", 10)                                                                              = 0x1e53d20
readdir(0x1e4bca0)                                                                                                = 0x1e4bd60
strlen("PA1.md")                                                                                                  = 6
malloc(7)                                                                                                         = 0x1e53d40
memcpy(0x1e53d40, "PA1.md\0", 7)                                                                                  = 0x1e53d40
readdir(0x1e4bca0)                                                                                                = 0x1e4bd80
strlen("myCode.c")                                                                                                = 8
malloc(9)                                                                                                         = 0x1e53d60
memcpy(0x1e53d60, "myCode.c\0", 9)                                                                                = 0x1e53d60
readdir(0x1e4bca0)                                                                                                = 0
closedir(0x1e4bca0 <unfinished ...>
free(0x1e4bca0)                                                                                                   = <void>
<... closedir resumed> )                                                                                          = 0
free(0)                                                                                                           = <void>
malloc(120)                                                                                                       = 0x1e4bca0
_setjmp(0x61e680, 0x400000, 0x1e47500, 0x1e4bcc8)                                                                 = 0
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("PA1.md", "myCode.c")                                                                                     = 3
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("myTstFile", "myCode.c")                                                                                  = 17
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("myTstFile", "PA1.md")                                                                                    = -3
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("myCode", "PA-1.pdf")                                                                                     = -3
memcpy(0x1e4bcd0, "\0r\344\001\0\0\0\0", 8)                                                                       = 0x1e4bcd0
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("myCode", "myCode.c")                                                                                     = -1
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("PA-1.pdf", "myCode.c")                                                                                   = 3
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("PA-1.pdf", "myTstFile")                                                                                  = 3
__errno_location()                                                                                                = 0x7f49c74056b8
strcoll("PA-1.pdf", "PA1.md")                                                                                     = 3
memcpy(0x1e4bcc0, "\0r\344\001\0\0\0\0", 8)                                                                       = 0x1e4bcc0
realloc(0, 240)                                                                                                   = 0x1e4bd20
malloc(440)                                                                                                       = 0x1e4be20
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
fwrite_unlocked("myCode", 1, 6, 0x7f49c7008620 <unfinished ...>
malloc(1024)                                                                                                      = 0x1e4bfe0
<... fwrite_unlocked resumed> )                                                                                   = 6
__overflow(0x7f49c7008620, 9, 7, 8)                                                                               = 9
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
fwrite_unlocked("myCode.c", 1, 8, 0x7f49c7008620)                                                                 = 8
__overflow(0x7f49c7008620, 32, 1, 8)                                                                              = 32
__overflow(0x7f49c7008620, 32, 2, 8)                                                                              = 32
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
fwrite_unlocked("myTstFile", 1, 9, 0x7f49c7008620)                                                                = 9
__overflow(0x7f49c7008620, 32, 4, 8)                                                                              = 32
__overflow(0x7f49c7008620, 32, 5, 8)                                                                              = 32
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
fwrite_unlocked("PA1.md", 1, 6, 0x7f49c7008620)                                                                   = 6
__overflow(0x7f49c7008620, 32, 4, 8)                                                                              = 32
__overflow(0x7f49c7008620, 32, 5, 8)                                                                              = 32
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
__errno_location()                                                                                                = 0x7f49c74056b8
__ctype_get_mb_cur_max()                                                                                          = 6
__ctype_get_mb_cur_max()                                                                                          = 6
fwrite_unlocked("PA-1.pdf", 1, 8, 0x7f49c7008620)                                                                 = 8
__overflow(0x7f49c7008620, 10, 0, 0x6664702e312d4150myCode	myCode.c  myTstFile  PA1.md  PA-1.pdf
)                                                             = 10
free(0x1e4bc80)                                                                                                   = <void>
free(0)                                                                                                           = <void>
free(0x1e4bc50)                                                                                                   = <void>
__fpending(0x7f49c7008620, 0, 0x40a320, 0x7f49c7008c70)                                                           = 0
fileno(0x7f49c7008620)                                                                                            = 1
__freading(0x7f49c7008620, 0, 0x40a320, 0x7f49c7008c70)                                                           = 0
__freading(0x7f49c7008620, 0, 2052, 0x7f49c7008c70)                                                               = 0
fflush(0x7f49c7008620)                                                                                            = 0
fclose(0x7f49c7008620 <unfinished ...>
free(0x1e4bfe0)                                                                                                   = <void>
<... fclose resumed> )                                                                                            = 0
__fpending(0x7f49c7008540, 0, 0x7f49c7009780, 0)                                                                  = 0
fileno(0x7f49c7008540)                                                                                            = 2
__freading(0x7f49c7008540, 0, 0x7f49c7009780, 0)                                                                  = 0
__freading(0x7f49c7008540, 0, 4, 0)                                                                               = 0
fflush(0x7f49c7008540)                                                                                            = 0
fclose(0x7f49c7008540)                                                                                            = 0
```

### a. Open the current directory

Library call: `opendir`
System call: `open`

### b. Get the list of directory entries

Library call: `readdir`
System call: `read`

### c. Print the output to your screen

Library call: `strcoll`
System call: `write`



