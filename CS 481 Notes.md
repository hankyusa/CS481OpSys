# CS 481 Notes

TA Tuesday and Thursday 12:30 pm - 1:30 pm

"Operating System Concepts" 9th edition is the better textbook.

> If you need to email the instructor or TAs, you must leave your subject line starting with either “ECE437” or “CS481”.

Computer from bottom to top:

- Hardware
- Firmware (on read-only memory (ROM))
    + Basic input output system (BIOS) or Unified Extensible Firmware Interface (UEFI)
- CMOS (BIOS settings and clock)
- Device drivers
- Operating system
    + Kernel
    + Utilities
- Applications/User

TODO Memorize, the first task of the BIOS is Power-on self-test (POST). See L1S11.

NOTE Date of the final is likely to change. The final likely will not be in the regular classroom.

Block = 512 bytes

TODO Review how the stack works.

## Interrupts

"Interrupts" are interrupts from hardware and are handled by the Interrupt Service Routine (ISR). "System calls" generate interrupts called traps from software/user and are not handled by the ISR.

I/O Device sends interrupt signal to Programmable Interrupt Controller (PIC). PIC forwards this to CPU. CPU asks PIC for I/O Device. PIC gets it from I/O Device and gives it to CPU. CPU looks in Interrupt Vector Table for address of Interrupt Routine Service (IRS). CPU runs code at address.

User program calls routine in standard C library which calls the System Call Handler which has the system call table in the kernel. This table has the addresses of the system routines.

A program is like a recipe. A process is like cooking.

## Terms 

Process Control Block (PCB)

## Assignments

### Programming Assignment 01

Due: 2018-09-11


