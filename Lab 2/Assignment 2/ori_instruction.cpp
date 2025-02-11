#include "ori_instruction.h"
#include <iostream>

void OriInstruction::disassemble() const {
    std::cout << "ori $" << param1 << ", $" << param2 << ", " << param3 << std::endl;
}

int OriInstruction::execute(Registers* regs) {
    int result = regs->getRegister(param2) | param3;
    regs->setRegister(param1, result);
    return regs->getPC() + 1;  // PC increment by 1
}
