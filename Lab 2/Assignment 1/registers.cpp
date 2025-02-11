#include "registers.h"
#include <iostream>

Registers::Registers() {
    for (int i = 0; i < 32; ++i) {
        registers[i] = 0;
    }
    PC = 0;
}

void Registers::setRegister(int regNum, int value) {
    if (regNum != 0) {
        registers[regNum] = value;
    }
}

int Registers::getRegister(int regNum) {
    if (regNum == 0) {
        return 0;
    } else {
        return registers[regNum];
    }
}

void Registers::setPC(int value) {
    PC = value;
}

int Registers::getPC() {
    return PC;
}

void Registers::print() {
    std::cout << "Registers:" << std::endl;
    for (int i = 0; i < 32; ++i) {
        std::cout << "$" << i << ": " << getRegister(i) << std::endl;
    }
    std::cout << "Program Counter (PC): " << getPC() << std::endl;
}