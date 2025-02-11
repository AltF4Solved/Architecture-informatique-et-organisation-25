//////////////////////////////
// By Waris Ibrahimi [5550343]
//  & Danial Abed [5474914]
//////////////////////////////
#ifndef PROGRAM_H
#define PROGRAM_H

class Program {
public:
    Program(int arith,
            int store,
            int load,
            int branch);

    Program(int instrtot,
            double arithfrac,
            double storefrac,
            double loadfrac);

    int numTot();

    int getnumTotal(); // new
    int getnumArith();
    int getnumStore();
    int getnumLoad();
    int getnumBranch(); // new

    void printStats();

private:
    int numArith;
    int numStore;
    int numLoad;
    int numBranch;
    int numTotal;
};

#endif // PROGRAM_H
