#ifndef ORIINSTRUCTION_H
#define ORIINSTRUCTION_H

#include "instruction.h"
#include <iostream>
using namespace std;

class OriInstruction : public Instruction {
private:
    int dest, src, immediate;  // Represents: ori $dest, $src, immediate
public:
    OriInstruction(int dest, int src, int immediate)
        : dest(dest), src(src), immediate(immediate) {}

    void disassemble() override {
        cout << "ori $" << dest << ", $" << src << ", " << immediate << "\n";
    }

    int execute(Registers *regs) override {
        int result = regs->getRegister(src) | immediate;
        regs->setRegister(dest, result);
        return regs->getPC() + 1;
    }
};

#endif
