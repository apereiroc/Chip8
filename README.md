Hello! Welcome to the **CHIP-8** emulator. This code tries to emulate a CHIP-8 interpreter, with which it will be 
possible to play games compiled for this architecture.

### **The software is not ready yet!**
### **Current status**: 
- [ ] Add sound
- [ ] Games can be played
- [ ] Add a keyboard
- [ ] Construct a screen
- [ ] Process the intructions
- [ ] Separate the instructions
- [x] Read ROMs into memory.
- [x] Class structure

## What's a CHIP-8?
> Chip-8 is a simple, interpreted, programming language which was first used on some do-it-yourself computer systems in 
> the late 1970s and early 1980s. The COSMAC VIP, DREAM 6800, and ETI 660 computers are a few examples. These computers 
> typically were designed to use a television as a display, had between 1 and 4K of RAM, and used a 16-key hexadecimal 
> keypad for input. The interpreter took up only 512 bytes of memory, and programs, which were entered into the computer
> in hexadecimal, were even smaller.

(Extracted from [Thomas P. Greene](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#memmap))

In other words: it emulates a virtual machine (specifications are below) capable of reading and processing ROMs written 
in hexadecimal.

## Specifications

As it's written in *machine.h*:

- Memory:
    - RAM memory: it has 4 kB (4096 bytes) of RAM, from location 0x000 (0) to 0xFFF (4095).
    The first 512 bytes, from 0x000 to 0x1FF, are where the original interpreter
    was located, and should not be used by programs. This chip-8 starts at 0x200 (512).
    - Stack memory: it has 16 values of 16-bit, and stores the address that the interpreter should
    return to when finished with a subroutine.
- Registers:
    - 16 general purpose 8-bit registers, referred to as Vx (x = 0..F)
    - 1 16-bit register, I. Generally, it stores the memory addresses so only the lowest
    (rightmost) 12 bits are usually used.
- Pseudo-registers:
    - 16-bit, Program Counter (PC). Stores the currently executing address.
    - 8-bit, Stack Pointer (SP). It is used to point to the topmost level of the stack.

## The emulator

You can compile the current version by running ``make`` inside the directory
