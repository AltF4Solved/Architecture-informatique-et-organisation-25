#include "registers.h"
#include <iostream>
#include <algorithm>

Registers::Registers() {
    std::fill(std::begin(regs), std::end(regs), 0);
    PC = 0;
}

void Registers::setRegister(int regNum, int value) {
    if (regNum == 0) {
        return;
    }
    if (regNum >= 0 && regNum < 32) {
        regs[regNum] = value;
    }
}

int Registers::getRegister(int regNum)
{
    return rgs[regNum];
}

void Registers::setPC(int value) {
    PC = value;
}

int Registers::getPC() {
    return PC;
}

void Registers::print() {
    for (int i = 0; i < 32; ++i) {
        std::cout << "$" << i << ": " << regs[i] << " ";
        if ((i + 1) % 8 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << "\nProgram Counter (PC): " << PC << std::endl;
}
