

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include "registers.h"

using namespace std;

class Instruction
{
protected:
        int a1;
        int a2;
        int a3;
    public:
        Instruction(int x1, int x2, int x3)
        {
            a1 = x1;
            a2 = x2;
            a3 = x3;
        };
        virtual ~Instruction(){};
        virtual void disassemble()=0;
        virtual int execute(Registers*)=0;
};

#endif /* _INSTRUCTION_H_ */
