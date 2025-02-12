

#ifndef BRNEINSTRUCTION_H
#define BRNEINSTRUCTION_H
#include "instruction.h"


class BrneInstruction : public Instruction
{
    public:
        BrneInstruction(int x1, int x2, int x3) : Instruction(x1, x2, x3){
            cout << "Registers Brne Instruction: " << x1 << " " << x2 << " " << x3 << "\n";

        };

        void disassemble(){
            cout << "Brne\t" << "$" << a1 << "\t" <<  "$" <<a2 << "\t" << a3 << endl;
        };

        int execute(Registers* reg){
            if(reg->getRegister(a1) != reg->getRegister(a2)){
                return reg->getPC()+a3+1;}
            else{
                return reg->getPC()+1;
            }
        };
};

#endif // BRNEINSTRUCTION_H
