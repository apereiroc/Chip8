//
// Created by Asier Pereiro on 28/12/20.
//

#ifndef CHIP8_MACHINE_H
#define CHIP8_MACHINE_H

/**
     CHIP-8 specifications:
        * Memory:
            - RAM memory: it has 4 kB (4096 bytes) of RAM, from location 0x000 (0) to 0xFFF (4095).
                          The first 512 bytes, from 0x000 to 0x1FF, are where the original interpreter
                          was located, and should not be used by programs. This chip-8 starts at 0x200 (512).
            - Stack memory: it has 16 values of 16-bit, and stores the address that the interpreter should
                            return to when finished with a subroutine.
        * Registers:
            - 16 general purpose 8-bit registers, referred to as Vx (x = 0..F)
            - 1 16-bit register, I. Generally, it stores the memory addresses so only the lowest
                (rightmost) 12 bits are usually used.
        * Pseudo-registers:
            - 16-bit, Program Counter (PC). Stores the currently executing address.
            - 8-bit, Stack Pointer (SP). It is used to point to the topmost level of the stack.
     */

#include <cstdint>
#include <vector>
#include "configs.h"

class machine {
public:
    explicit machine(const char* path_to_file);
    ~machine();
    void test();

private:
    std::vector<i8>  memory;         // RAM memory
    std::vector<i16> stack;          // Stack memory
    std::vector<i8>  v;              // 8-bit registers
    i16 I;                           // 16-bit register
    i16 PC;                          // Program Counter
    i8  SP;                          // Stack Pointer
    const char* _file;               // Program file to be loaded

    [[maybe_unused]] void _reset();
    void _loadROM(const char* path_to_file);
    static void _processInstruction(i16 &opcode);
};


#endif //CHIP8_MACHINE_H
