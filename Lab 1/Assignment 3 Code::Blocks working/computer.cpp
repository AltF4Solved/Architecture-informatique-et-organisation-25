//////////////////////////////
// By Waris Ibrahimi [5550343]
//  & Danial Abed [5474914]
//////////////////////////////
#include <iostream>
#include "computer.h"
#include "program.h"

using namespace std;

Computer::Computer(double clockRate,
                   double arithcpi,
                   double storecpi,
                   double loadcpi,
                   double branchcpi) {
    clockRateGHz = clockRate;
    cpiArith = arithcpi;
    cpiStore = storecpi;
    cpiLoad = loadcpi;
    cpiBranch = branchcpi;
}

void Computer::printStats() {
    cout << "Clock rate: " << clockRateGHz << " GHz" << endl;
    cout << "Arithmetic CPI: " << cpiArith << endl;
    cout << "Store CPI: " << cpiStore << endl;
    cout << "Load CPI: " << cpiLoad << endl;
    cout << "Branch CPI: " << cpiBranch << endl;
}

double Computer::calculateGlobalCPI() {
    double globalCPI = (cpiArith + cpiStore + cpiLoad + cpiBranch) / 4.0;
    return globalCPI;
}

double Computer::calculateExecutionTime(Program program) {
    double ExecTime = (cpiArith * program.getnumArith() + cpiStore * program.getnumStore() + cpiLoad * program.getnumLoad() + cpiBranch * program.getnumBranch()) / (clockRateGHz * 1e9);
    return ExecTime;
}

double Computer::calculateMIPS() {
    double MipsAns = (clockRateGHz * 1e3) / calculateGlobalCPI();
    return MipsAns;
}

double Computer::calculateMIPS(Program program) {
    double MipsAns = (program.getnumArith() + program.getnumStore() + program.getnumLoad() + program.getnumBranch()) / (calculateExecutionTime(program) * 1e6);
    return MipsAns;
}
