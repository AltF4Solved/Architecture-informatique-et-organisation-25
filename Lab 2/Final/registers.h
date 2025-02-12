


#ifndef _REGISTERS_H_
#define _REGISTERS_H_

class Registers
{

    public:
        Registers();
        void    setRegister(int regNum, int value);
        int     getRegister(int regNum);
        void    setPC(int value);
        int     getPC();
        void    print();


    int rgs[32];
    int pcCount;

};

#endif	/* _REGISTERS_H_ */
