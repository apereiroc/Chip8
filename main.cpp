#include <iostream>
#include "machine.h"

int main(const int argc, const char* argv[]) {

    const char* myGame = "POG";

    machine cpu = machine(myGame);

    cpu.test();



    return 0;
}
