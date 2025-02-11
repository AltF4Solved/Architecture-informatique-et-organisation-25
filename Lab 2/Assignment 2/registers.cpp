#include "registers.h"
#include <iostream>


using namespace std;


Registers::Registers ()
{
    for(int i = 0; i < 32; i++)
    {
        rgs[i] = 0;
    }
    pcCount = 0;
}

void Registers::setRegister(int regNum, int value)
{
    if (regNum == 0)
    {
        rgs[regNum] = 0;
    }
    else
    {
        rgs[regNum] = value;
    }
}

int Registers::getRegister(int regNum)
{
    return rgs[regNum];
}

void Registers::setPC(int value)
{
    pcCount = value;
}

int Registers::getPC()
{
    return pcCount;
}

void Registers::print()
{
    for(int i = 0; i < 32; i++){
        cout << "Value Register : " << i << "\t" << rgs[i] << "\n";
    }
    cout << "Program Count :\t" << pcCount << "\n";

}
