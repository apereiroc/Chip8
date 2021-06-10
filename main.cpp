#include <iostream>
#include "machine.h"

int main(const int argc, const char* argv[]) {

    const char* myGame = "/Users/apereiro/Downloads/c8games/PONG";

    machine cpu = machine(myGame);

    cpu.test();

    return 0;
}
