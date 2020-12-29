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
    I  = 0x0;
    PC = START_PC;
    SP = 0;


}

machine::~machine() {
    std::cout << "Bye" << std::endl;
}

void machine::test() {
    this->_loadROM(this->_file);
}


[[maybe_unused]] void machine::_reset() {

    std::fill(this->memory.begin(), this->memory.end(), 0);
    std::fill(this->stack.begin(),  this->stack.end(),  0);
    std::fill(this->v.begin(),      this->v.end(),      0);
    I  = 0x00;
    PC = START_PC;
    SP = 0;
}

void machine::_loadROM(const char* path_to_file) {

    /*
     * Load the ROM file to memory
     */

    // First it's interesting to check if the file exists
    bool exists = std::filesystem::exists(path_to_file);
    if (not exists) {
        std::cout << "The path or the file that gyou have passed does not exist! Exiting..." << std::endl;
        exit(1);
    }

    std::ifstream   file;
    std::streamsize size;
    // try {
    file.open(path_to_file, std::ios::binary | std::ios::ate); // Open it and go to the end

    if (!file.good()) {
        file.close();
        std::cout << "The file is not good! Exiting..." << std::endl;
        exit(1);
    }
    size = file.tellg();                                                        // Read how many bytes until here
    file.seekg(0, std::ios::beg);                                      // Go to the beginning again

    // file.read(reinterpret_cast<char *>(memory.data()), size);
    file.read( reinterpret_cast<char *> ( &memory[START_PC] ), size ); // Dump bytes to memory

    file.close();
}

void machine::_readInstruction(i16 opcode) {

}



