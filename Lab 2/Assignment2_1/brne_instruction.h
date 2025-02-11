#ifndef BRNEINSTRUCTION_H
#define BRNEINSTRUCTION_H

#include "instruction.h"
#include <iostream>

class BrneInstruction : public Instruction {
private:
    int reg1, reg2;
    int offset;
public:
    // Branch if not equal: if reg1 != reg2 then jump relative by offset.
    BrneInstruction(int reg1, int reg2, int offset)
        : reg1(reg1), reg2(reg2), offset(offset) {}

    void disassemble() override {
        std::cout << "brne $" << reg1 << ", $" << reg2 << ", " << offset << "\n";
    }
    int execute(Registers *regs) override {
        if (regs->getRegister(reg1) != regs->getRegister(reg2)) {
            return regs->getPC() + 1 + offset;
        }
        return regs->getPC() + 1;
    }
};

#endif
