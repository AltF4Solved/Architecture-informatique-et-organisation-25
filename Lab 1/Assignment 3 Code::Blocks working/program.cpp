//////////////////////////////
// By Waris Ibrahimi [5550343]
//  & Danial Abed [5474914]
//////////////////////////////
#include <iostream>
#include "program.h"

using namespace std;

// Constructor with instruction counts
Program::Program(int arith,
                 int store,
                 int load,
                 int branch) {
    numArith = arith;
    numStore = store;
    numLoad = load;
    numBranch = branch;
    numTotal = numArith + numStore + numLoad + numBranch;
}

// Overloaded constructor using fractions
Program::Program(int instrtot,
                 double arithfrac,
                 double storefrac,
                 double loadfrac) {
    numArith = instrtot * arithfrac;
    numStore = instrtot * storefrac;
    numLoad = instrtot * loadfrac;
    numBranch = instrtot - (numArith + numStore + numLoad);
    numTotal = instrtot;
}

// Print program stats
void Program::printStats() {
    cout << "Arithmetic and Logic calculations: " << numArith << endl;
    cout << "Store instructions: " << numStore << endl;
    cout << "Load instructions: " << numLoad << endl;
    cout << "Branch instructions: " << numBranch << endl;
    cout << "Total instructions: " << numTotal << endl;
}

// Getter methods
int Program::getnumTotal() { return numTotal; }
int Program::getnumArith() { return numArith; }
int Program::getnumStore() { return numStore; }
int Program::getnumLoad() { return numLoad; }
int Program::getnumBranch() { return numBranch; }
