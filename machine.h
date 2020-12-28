//
// Created by Asier Pereiro on 28/12/20.
//

#ifndef CHIP8_MACHINE_H
#define CHIP8_MACHINE_H

#include <cstdint>
#include "configs.h"

class machine {
public:
    machine();
    ~machine();
    void loadROM(std::string name);

private:
    uint8_t  memory[MEMSIZE];            // RAM memory
    uint16_t stack[16];                  // Stack memory
    uint8_t  v[16];                      // 8-bit registers
    uint16_t I;                          // 16-bit register
    uint16_t PC;                         // Program Counter
    uint8_t  SP;                         // Stack Pointer

    void init();


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



};


#endif //CHIP8_MACHINE_H
