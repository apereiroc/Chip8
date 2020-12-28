//
// Created by Asier Pereiro on 28/12/20.
//

#include <string>
#include <iostream>
#include <fstream>
#include "machine.h"

machine::machine() {
    std::cout << "Hola" << std::endl;
    this->init();
}

machine::~machine() {
    std::cout << "Adiós" << std::endl;
}

void machine::init() {

    memset(this->memory, 0, MEMSIZE);
    memset(this->stack,  0, MEMSIZE);
    memset(this->v,      0, MEMSIZE);
}

void machine::loadROM(std::string name) {
    std::ifstream file;
    try {
        file.open(name);
        std::string line;

        while( getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    } catch (int x) {
        std::cout << "Something went wrong with the opening of the file!\n" <<
        "Error code: " << x << std::endl;
    }
}


