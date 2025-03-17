#include "LPC13xx.h"
#include "leddriver.h"


void init(void)
{
    init_leds();

    LPC_IOCON->PIO0_4 = 0x01; // SCL
    LPC_IOCON->PIO0_5 = 0x01; // SDA

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5); // enable I2C clock
    LPC_SYSCON->PRESETCTRL |= (1<<1); // de-assert I2C reset

    LPC_I2C->CONCLR = 0xFF; // clear all
    LPC_I2C->SCLH = 720; // 100 kHz
    LPC_I2C->SCLL = 720;

    LPC_I2C->CONSET |= (1<<6); // I2C interface enable

    NVIC_EnableIRQ(I2C_IRQn);
}


void start(void)
{
    LPC_I2C->CONCLR = 0xFF; // clear all
    LPC_I2C->CONSET |= (1<<6); // I2C interface enable
    LPC_I2C->CONSET |= (1<<5);  // start

    while(!(LPC_I2C->CONSET & (1<<3))); // wait for interrupt
}

void stop(void)
{
    LPC_I2C->CONCLR = ((1<<5)|(1<<3)|(1<<2)); // start, SI, AACK
    LPC_I2C->CONSET |= (1<<4); // set stop
}



void I2C_Handler(void)
{
    int data;
    switch(LPC_I2C->STAT)
    {
    case 0x08: //start
        send(0b10010001);
        break;

    case 0x40: //send slave read address
        data = receive();
        break;

    case 0x58: // receive data
        set_leds(data);
        start();
        break;
    }
}


void send(int data)
{
    LPC_I2C->DAT = data;
    LPC_I2C->CONCLR = (1<<5); // clear start and stop
    LPC_I2C->CONCLR = (1<<3); // clear interrupt
    while(!(LPC_I2C->CONSET & (1<<3))); // wait for interrupt
}

int receive(void)
{
    LPC_I2C->CONCLR = (1<<5); // clear start and stop
    LPC_I2C->CONCLR = (1<<3); // clear interrupt
    LPC_I2C->CONCLR = (1<<2); // clear AACK
    //LPC_I2C->CONSET = (1<<2); // AACK to continue
    while(!(LPC_I2C->CONSET & (1<<3))); // wait for interrupt
    return LPC_I2C->DAT;
}

// I2C with interrupts

int main(void)
{
    init();

    start();

    send(0b10010000); // send slave write address

    start();
    send(0b00000000); // send register number

    while(1)
    {

    }
}



/*

//I2C with polling:
int main(void)
{
    init();
    start();
    send(0b10010000);
    start();
    send(0b00000000); // set register number
    while(1)
    {

        start();

        send(0b10010001);


        set_leds(receive());

    }

}
*/
