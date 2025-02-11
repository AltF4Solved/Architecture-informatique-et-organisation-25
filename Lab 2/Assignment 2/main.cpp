#include <iostream>
#include "registers.h"  // Include the header file for the Registers class

int main() {
    Registers regs;

    regs.setRegister(1, 10);
    regs.setRegister(2, 20);
    regs.setRegister(3, 30);

    regs.setPC(100);  // Set PC to 100

    std::cout << "Initial register values:" << std::endl;
    regs.print();

    std::cout << "Reading values from registers:" << std::endl;
    std::cout << "$1: " << regs.getRegister(1) << std::endl;
    std::cout << "$2: " << regs.getRegister(2) << std::endl;
    std::cout << "$3: " << regs.getRegister(3) << std::endl;

    std::cout << "PC: " << regs.getPC() << std::endl;

    std::cout << "$0: " << regs.getRegister(0) << std::endl;  // Should always return 0

    return 0;
}
