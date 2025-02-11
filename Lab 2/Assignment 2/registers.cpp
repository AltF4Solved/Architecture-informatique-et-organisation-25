#include "registers.h"
#include <iostream>
using namespace std;

Registers::Registers()  {
    for (int i = 0; i < 32; i++) {
        reg[i] = 0;
    }
    PC=0; // dit moet bij
}


void Registers::setRegister(int regNum, int value) {
    // Register $0 is special: it always reads as 0.
    if (regNum == 0)
            {
        rgs[regNum] = 0;
            }
    else
    {
        rgs[regNum] = value;
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
    cout << "Program Counter (PC): " << PC << "\n";
    for (int i = 0; i < 32; i++) {
        cout << "$" << i << ": " << reg[i] << "\n";
    }
}
