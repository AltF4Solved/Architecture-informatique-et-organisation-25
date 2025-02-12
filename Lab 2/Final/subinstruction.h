

#ifndef SUBINSTRUCTION_H
#define SUBINSTRUCTION_H

#include "instruction.h"

class SubInstruction : public Instruction
{
     public:
        SubInstruction(int x1, int x2, int x3) : Instruction(x1, x2, x3){
               cout << "Registers Sub Instruction: " << x1 << " " << x2 << " " << x3 << "\n";

        };

        void disassemble(){
            cout << "Sub\t" << "$" << a1 << "\t" <<  "$" <<a2 << "\t" <<  "$" << a3 << endl;
        };

        int execute(Registers* reg){
            reg->setRegister(a1, reg->getRegister(a2)-reg->getRegister(a3));
            return reg->getPC()+1;

        };
};

#endif // SUBINSTRUCTION_H
