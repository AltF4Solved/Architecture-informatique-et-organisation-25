#include "add_instruction.h"
#include <iostream>

void AddInstruction::disassemble() const {
    std::cout << "add $" << param1 << ", $" << param2 << ", $" << param3 << std::endl;
}

int AddInstruction::execute(Registers* regs) {
    int result = regs->getRegister(param2) + regs->getRegister(param3);
    regs->setRegister(param1, result);
    return regs->getPC() + 1;  // PC increment by 1
}
