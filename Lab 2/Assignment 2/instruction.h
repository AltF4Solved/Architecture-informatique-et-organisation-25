#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "registers.h"

class Instruction {
public:
    virtual void disassemble() = 0;  // Pure virtual for disassembly
    virtual int execute(Registers *regs) = 0;  // Pure virtual for execution
    virtual ~Instruction() {}  // Virtual destructor
};

#endif
