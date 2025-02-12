

#include "simulator.h"
#include "simulator.cpp"
#include "program.h"
#include "program.cpp"
#include "registers.h"
#include "registers.cpp"
#include "oriInstruction.h"
#include "subInstruction.h"
#include "addInstruction.h"
#include "brneInstruction.h"

void loadProgram (Program *program)
{
	program->appendInstruction (new OriInstruction (1, 0, 12));
	program->appendInstruction (new OriInstruction (2, 0, 4));
	program->appendInstruction (new OriInstruction (3, 0, 1));
	program->appendInstruction (new AddInstruction (4, 4, 1));
	program->appendInstruction (new SubInstruction (2, 2, 3));
	program->appendInstruction (new BrneInstruction (2, 0, -3));
}


int main (void)
{
	Registers *registers	= new Registers ();
	Program	*program	= new Program ();

	loadProgram (program);

	Simulator theSimulator = Simulator (registers, program);

	theSimulator.ui ();

	return 0;
}



// #include <iostream>
// #include "registers.cpp"
// #include "registers.h"  // Include the header file for the Registers class

// int main() {
//     Registers regs;

//     regs.setRegister(1, 10);
//     regs.setRegister(2, 20);
//     regs.setRegister(3, 30);

//     regs.setPC(100);  // Set PC to 100

//     std::cout << "Initial register values:" << std::endl;
//     regs.print();

//     std::cout << "Reading values from registers:" << std::endl;
//     std::cout << "$1: " << regs.getRegister(1) << std::endl;
//     std::cout << "$2: " << regs.getRegister(2) << std::endl;
//     std::cout << "$3: " << regs.getRegister(3) << std::endl;

//     std::cout << "PC: " << regs.getPC() << std::endl;

//     std::cout << "$0: " << regs.getRegister(0) << std::endl;  // Should always return 0

//     return 0;
// }
