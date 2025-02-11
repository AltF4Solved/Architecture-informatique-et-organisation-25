#ifndef REGISTERS_H
#define REGISTERS_H

class Registers {
private:
    int registers[32];
    int PC;

public:
    Registers();
    void setRegister(int regNum, int value);
    int getRegister(int regNum);
    void setPC(int value);
    int getPC();
    void print();
};

#endif
