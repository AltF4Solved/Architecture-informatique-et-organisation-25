#ifndef REGISTERS_H
#define REGISTERS_H

class Registers {
private:
    int rgs[32];  // Array to hold 32 general-purpose registers
    int PC;       // Program Counter

public:
    Registers();                // Constructor to initialize registers and PC
    void setRegister(int regNum, int value);  // Set the value of a specific register
    int getRegister(int regNum);              // Get the value of a specific register
    void setPC(int value);                   // Set the value of the Program Counter
    int getPC();                            // Get the value of the Program Counter
    void print();                           // Print all registers and the Program Counter
};

#endif
