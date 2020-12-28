//
// Created by Asier Pereiro on 28/12/20.
//

#include <string>
#include <iostream>
#include <fstream>
#include "machine.h"

machine::machine()
: memory(MEMSIZE), stack(16), v(16)
{
    /** CONSTRUCTOR
     * Initialises the registers. Note that PC points to 512, because 0..512 is reserved
     */

    std::cout << "Hi" << std::endl;
    I  = 0x0;
    PC = 0x200;
    SP = 0;
}

machine::~machine() {
    std::cout << "Bye" << std::endl;
}


void machine::reset() {

    std::fill(this->memory.begin(), this->memory.end(), 0);
    std::fill(this->stack.begin(),  this->stack.end(),  0);
    std::fill(this->v.begin(),      this->v.end(),      0);
    I  = 0x0;
    PC = 0x200;
    SP = 0;
}

void machine::loadROM(const char* path_to_file) {

    /*
     * Load the ROM file to memory
     */
    std::ifstream   file;
    std::streamsize size;

    try {
        file.open(path_to_file, std::ios::binary | std::ios::ate); // Open it and go to the end
        size = file.tellg();                                        // Read how many bytes until here
        file.seekg(0, std::ios::beg);                                      // Go to the beginning again

        file.read(reinterpret_cast<char *>(memory.data()), size);

    } catch (int x) {
        std::cout << "Something went wrong with the file's opening!\n" <<
        "Error code: " << x << std::endl;
        file.close();
        exit(1);
    }

    file.close();
}

