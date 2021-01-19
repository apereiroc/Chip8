//
// Created by Asier Pereiro on 28/12/20.
//

#include <string>
#include <iostream>
#include <fstream>
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

    I = ( memory[PC] << 8 ) | memory[PC+1];

    _processInstruction(I);

    /**
     * TODO: process the codes
     */

    PC += 2;

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
     */

     const i16 nnn = opcode & 0xFFF;
     const i8  n   = opcode & 0xF;
     const i8  x   = ( opcode & 0xF00 )  >> 8;
     const i8  y   = (opcode & 0xF0) >> 4;
     const i8  kk  = opcode & 0x0FF;
     
}




