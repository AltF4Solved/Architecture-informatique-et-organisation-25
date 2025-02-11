#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "registers.h"

class Instruction {
public:
    virtual void disassemble() = 0;
    virtual int execute(Registers *regs) = 0;
    virtual ~Instruction() {}
};

#endif
