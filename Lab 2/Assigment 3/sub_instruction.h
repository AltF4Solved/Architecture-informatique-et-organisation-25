#ifndef SUBINSTRUCTION_H
#define SUBINSTRUCTION_H

#include "instruction.h"
#include <iostream>
using namespace std;

class SubInstruction : public Instruction {
private:
    int dest, src1, src2;
public:
    SubInstruction(int dest, int src1, int src2)
        : dest(dest), src1(src1), src2(src2) {}

    void disassemble() override {
        cout << "sub $" << dest << ", $" << src1 << ", $" << src2 << "\n";
    }

    int execute(Registers *regs) override {
        int result = regs->getRegister(src1) - regs->getRegister(src2);
        regs->setRegister(dest, result);
        return regs->getPC() + 1;
    }
};

#endif
