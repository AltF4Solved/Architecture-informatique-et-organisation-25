#include "brne_instruction.h"
#include <iostream>

void BrneInstruction::disassemble() const {
    std::cout << "brne $" << param1 << ", $" << param2 << ", " << param3 << std::endl;
}

int BrneInstruction::execute(Registers* regs) {
    if (regs->getRegister(param1) != regs->getRegister(param2)) {
        return regs->getPC() + 1 + param3;  // Branch to offset if not equal
    }
    return regs->getPC() + 1;  // PC increment by 1 if no branch
}
