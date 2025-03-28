//////////////////////////////
// By Waris Ibrahimi [5550343]
//  & Danial Abed [5474914]
//////////////////////////////
#include <iostream>
#include "computer.h"
#include "program.h"

using namespace std;

int main() {
    Computer computer1(1, 2, 2, 3, 4); // 1 GHz, 2 arith cy, 2 store cy, 3 load cy, 4 branch cy
    Computer computer2(1.2, 2, 3, 4, 3);
    Computer computer3(2, 2, 2, 4, 6);
    Computer CompArray[3] = {computer1, computer2, computer3};

    Program Pr_A(1000, 50, 50, 20);
    Program Pr_B(2000, 100, 100, 40);
    Program Pr_C(2000, 0.1, 0.4, 0.25);
    Program ProgramArray[3] = {Pr_A, Pr_B, Pr_C};
    string Pr_Array[3] = {"A", "B", "C"};

    for (int i = 0; i < sizeof(CompArray) / sizeof(*CompArray); i++) {
        cout << "Computer " << i + 1 << endl;
        CompArray[i].printStats();
        cout << "Global CPI PC_" << i + 1 << "= " << CompArray[i].calculateGlobalCPI() << std::endl;
        cout << "Global MIPS= " << CompArray[i].calculateMIPS() << std::endl;
        cout << endl;

        for (int j = 0; j < sizeof(ProgramArray) / sizeof(*ProgramArray); j++) {
            cout << "Program " << Pr_Array[j] << endl;
            cout << "Execution Time " << CompArray[i].calculateExecutionTime(ProgramArray[j]) << endl;
            cout << "MIPS " << CompArray[i].calculateMIPS(ProgramArray[j]) << endl;
            cout << endl;
        }
    }

    return 0;
}
