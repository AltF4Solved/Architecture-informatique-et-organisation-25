//////////////////////////////
// By Waris Ibrahimi [5550343]
//  & Danial Abed [5474914]
//////////////////////////////
#ifndef COMPUTER_H
#define COMPUTER_H

class Program; // forward declaration of Program class

class Computer {
public:
    Computer(double clockRate,
             double arithcpi,
             double storecpi,
             double loadcpi,
             double branchcpi);

    void printStats();
    double calculateGlobalCPI();
    double calculateExecutionTime(Program program); // new
    double calculateMIPS(void);
    double calculateMIPS(Program program); // new

private:
    double clockRateGHz;
    double cpiArith;
    double cpiStore;
    double cpiLoad;
    double cpiBranch;
};

#endif // COMPUTER_H
