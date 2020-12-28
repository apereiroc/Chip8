#include <iostream>
#include "machine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    machine cpu = machine();

    cpu.loadROM("PONG");

    std::cout << "Goodbye, World!" << std::endl;

    return 0;
}
