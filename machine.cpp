//
// Created by Asier Pereiro on 28/12/20.
//

#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "machine.h"

machine::machine(const char* path_to_file)
: memory(MEMSIZE), stack(16), v(16), _file(path_to_file)
{
    /** CONSTRUCTOR
     * Initialises the registers. Note that PC points to 512, because memory positions 0..512  are reserved
     */

    std::cout << "Hi" << std::endl;
    I  = START;
    PC = START;
    SP = 0;


}

machine::~machine() {
    std::cout << "Bye" << std::endl;
}

void machine::test() {
    this->_loadROM(this->_file);
    
    unsigned int microsecond = 1000000;

    while(true)
    {

        I = ( memory[PC] << 8 ) | memory[PC+1];

        _processInstruction(I);

        PC += 2;

        // Sleep 3 seconds;
        usleep(3 * microsecond);
    }

}


[[maybe_unused]] void machine::_reset() {

    std::fill(this->memory.begin(), this->memory.end(), 0);
    std::fill(this->stack.begin(),  this->stack.end(),  0);
    std::fill(this->v.begin(),      this->v.end(),      0);
    I  = START;
    PC = START;
    SP = 0;
}

void machine::_loadROM(const char* path_to_file) {

    /**
     * Load the ROM file to memory
     */

    // First it's interesting to check if the file exists
    const bool exists = std::filesystem::exists(path_to_file);
    if (not exists) {
        std::cout << "The path to the file that you have passed does not exist! Exiting..." << std::endl;
        exit(1);
    }

    std::ifstream file;

    file.open(path_to_file, std::ios::binary | std::ios::ate);   // Open it and go to the end

    if (!file.good()) {
        file.close();
        std::cout << "The file is not good! Exiting..." << std::endl;
        exit(1);
    }
    const std::streamsize size = file.tellg();                          // Read how many bytes until here
    file.seekg(0, std::ios::beg);                              // Go to the beginning again
    // file.read(reinterpret_cast<char *>(memory.data()), size);
    file.read( reinterpret_cast<char *> ( &memory[START] ), size );  // Dump bytes to memory, starting from where
                                                                        // PC points to
    file.close();
}

void machine::_processInstruction(i16& opcode) {
    /**

    b16 b15 b14 b13 b12 b11 b10 b9 b8 b7 b6 b5 b4 b3 b2 b1
                    |--------------- nnn ----------------|
                                               |--- n ---|
                    |------ x ------|---- y -----|
                                   |--------- kk --------|

     * EXPLANATION:
        - nnn: 0xFFF is 0000111111111111, so I can get the 12 lowest bits of the instruction
        - n: 0xF is 0000000000001111, so I can get the 4 lowest bits of the instruction
        - x: 0xF00 is 0000111100000000, so I can get the 4 lowest bits of the first byte
        - y: 0xF0 is 0000000011110000, so I can get the 4 upper bits of the second byte
        - kk: 0x0FF  is 0000000011111111, so I can get the last byte
        - f: 0xf000 is 1111000000000000, so I can get the 4 upper bits of the first byte
     */

    const i16 nnn = opcode & 0xFFF;
    const i8  n   = opcode & 0xF;
    const i8  x   = ( opcode & 0xF00 )  >> 8;
    const i8  y   = (opcode & 0xF0) >> 4;
    const i8  kk  = opcode & 0x0FF;
    const i8  f   = opcode >> 12;

    switch(f)
    {
        case 0:
            switch(kk)
            {
                case 0xE0:
                    std::cout << "CLS (clear the display)" << std::endl;
                    break;
                case 0xEE:
                    std::cout << "RET (return) from subroutine" << std::endl;
                    break;
                default:
                    std::cout << "No match at switch(f == 0)! Check it" << std::endl;
                    break;
            }
            break;
        case 1:
            std::cout << "JP addr (jump to nnn)" << std::endl;
            break;
        case 2:
            std::cout << "CALL addr (call subroutine at nnn)" << std::endl;
            break;
        case 3:
            std::cout << "SE Vx, byte (skip next instruction if Vx = kk)" << std::endl;
            break;
        case 4:
            std::cout << "SNE Vx, byte (skip next instruction if Vx != kk)" << std::endl;
            break;
        case 5:
            std::cout << "SE Vx,Vy (skip next instruction if Vx = Vy)" << std::endl;
            break;
        case 6:
            std::cout << "LD Vx, byte (set Vx = kk)" << std::endl;
            break;
        case 7:
            std::cout << "ADD Vx, byte (set Vx = Vx + kk)" << std::endl;
            break;
        case 8:
            switch(n)
            {
                case 0:
                    std::cout << "LD Vx,Vy (set Vx = Vy)" << std::endl;
                    break;
                case 1:
                    std::cout << "OR Vx,Vy (set Vx = Vx | Vy)" << std::endl;
                    break;
                case 2:
                    std::cout << "AND Vx,Vy (set Vx = Vx & Vy)" << std::endl;
                    break;
                case 3:
                    std::cout << "XOR Vx,Vy (set Vx = Vx ^ Vy)" << std::endl;
                    break;
                case 4:
                    std::cout << "ADD Vx,Vy with carry (set Vx = Vx+Vy, VF = carry)" << std::endl;
                    /* Para cando implementes isto:
                     * The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. 
                     * Only the lowest 8 bits of the result are kept, and stored in Vx.
                     */
                    break;
                case 5:
                    std::cout << "SUB Vx,Vy (set Vx = Vx - Vy, set VF = NOT borrow)" << std::endl;
                    /* Para cando implementes isto:
                     * If Vx > Vy, then VF is set to 1, otherwise 0.
                     * Then Vy is subtracted from Vx, and the results stored in Vx.
                     */
                    break;
                case 6:
                    std::cout << "SHR Vx {, Vy} (set Vx = Vx SHR 1)" << std::endl;
                    /* Para cando implementes isto:
                     * If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0
                     * Then Vx is divided by 2.
                     */
                    break;
                case 7:
                    std::cout << "SUBN Vx, Vy (Set Vx = Vy - Vx, set VF = NOT borrow)" << std::endl;
                    /* Para cando implementes isto:
                     * If Vy > Vx, then VF is set to 1, otherwise 0.
                     * Then Vx is subtracted from Vy, and the results stored in Vx.
                     */
                    break;
                case 8:
                    std::cout << "SHL Vx {, Vy} (set Vx = Vx SHL 1)" << std::endl;
                    /* Para cando implementes isto:
                     * If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0
                     * Then Vx is multiplied by 2.
                     */
                    break;
                default:
                    std::cout << "No match at switch(f == 8)! Check it" << std::endl;
                    break;
            }
            break;
        case 9:
            std::cout << "SNE Vx, Vy (skip next instruction if Vx != Vy)" << std::endl;
            break;
        case 0xA:
            std::cout << "LD I, addr (set I = nnn)" << std::endl;
            break;
        case 0xB:
            std::cout << "JP V0, addr (jump to location nnn+V0)" << std::endl;
            /* Para cando implementes isto:
             * Entendo que é PC = nnn+V0
             */
            break;
        case 0xC:
            std::cout << "RND Vx, byte (set Vx = random byte AND kk)" << std::endl;
            break;
        case 0xD:
            std::cout << "DRW Vx, Vy, nibble (display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.)" << std::endl;
            break;
        case 0xE:
            switch(kk)
            {
                case 0x9E:
                    std::cout << "SKP Vx (skip next instruction if key with the value of Vx is pressed)" << std::endl;
                    break;
                case 0xA1:
                    std::cout << "SKNP Vx (skip next instruction if key with the value of Vx is not pressed)" << std::endl;
                    break;
                default:
                    std::cout << "No match at switch(f == E)! Check it" << std::endl;
                    break;
            }
            break;
        case 0xF:
            switch(kk)
            {
                case 0x07:
                    std::cout << "LD Vx, DT (set Vx = DT)" << std::endl;
                    break;
                case 0x0A:
                    std::cout << "LD Vx, K (wait for a key press, store the value of the key in Vx)" << std::endl;
                    break;
                case 0x15:
                    std::cout << "LD DT, Vx (set DT = Vx)" << std::endl;
                    break;
                case 0x18:
                    std::cout << "LD ST, Vx (set ST = Vx)" << std::endl;
                    break;
                case 0x1E:
                    std::cout << "ADD I, Vx (set I = I + Vx)" << std::endl;
                    break;
                case 0x29:
                    std::cout << "LD F, Vx (set I = location of sprite for digit Vx)" << std::endl;
                    break;
                case 0x33:
                    std::cout << "LD B, Vx (store BCD representation of Vx in memory locations I, I+1, and I+2)" << std::endl;
                    break;
                case 0x55:
                    std::cout << "LD [I], Vx (store registers V0 through Vx in memory starting at location I)" << std::endl;
                    break;
                case 0x65:
                    std::cout << "LD Vx, [I] (read registers V0 through Vx from memory starting at location I)" << std::endl;
                    break;
                default:
                    std::cout << "No match at switch(f == F)! Check it" << std::endl;
                    break;
            }
            break;
        default:
            std::cout << "No match at main switch(f)! Check it" << std::endl;
            break;
    }

}























