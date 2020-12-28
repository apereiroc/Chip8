#include <iostream>
#include "machine.h"

int main(const int argc, const char* argv[]) {

    std::cout << "Hello, from main()!" << std::endl;

    machine cpu = machine();

    //cpu.loadROM("PONG");

    std::cout << "Goodbye, from main()!" << std::endl;

    return 0;
}
