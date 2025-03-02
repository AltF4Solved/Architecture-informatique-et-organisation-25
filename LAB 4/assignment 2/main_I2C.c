#include "LPC13xx.h"
#include "leddriver.h"


void init(void)
{
    init_leds();

    LPC_IOCON->PIO0_4 = 0x01; // SCL
    LPC_IOCON->PIO0_5 = 0x01; // SDA

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5); // enable I2C clock
    LPC_SYSCON->PRESETCTRL |= (1<<1); // de-assert I2C reset

    LPC_I2C->SCLH = 360; // 100 kHz
    LPC_I2C->SCLL = 360;

    LPC_I2C->CONSET = (1<<6); // I2C interface enable

    NVIC_EnableIRQ(I2C_IRQn);
}


void start(void)
{
    LPC_I2C->CONSET = (1<<5);  // start
    LPC_I2C->CONCLR = (1<<3);
}

void stop(void)
{
    LPC_I2C->CONCLR = ((1<<3)|(1<<2)); // start, SI, AACK
    LPC_I2C->CONSET |= (1<<4); // set stop
}

void send(int data)
{
    LPC_I2C->DAT = data;
}

void I2C_Handler(void)
{
    int data;
    //set_leds(LPC_I2C->STAT & 0XFF);
    switch(LPC_I2C->STAT & 0XFF)
    {

    case 0x08: //start
        //start();
        send(0x90); // slave write adress
        LPC_I2C->CONCLR = (1<<3)|(1<<5);
        break;



    case 0x18: //send data
        send(0);
        LPC_I2C->CONCLR = (1<<3);
        break;

    case 0x28:
        LPC_I2C->CONSET = (1<<5);
        LPC_I2C->CONCLR = (1<<3);

        break;

      case 0x10: //repeat start
        send(0x91);//send slave read adress
        LPC_I2C->CONCLR = (1<<3)|(1<<5);

        break;




    case 0x40: // RECEIVE DATA SEND NOT ACK

        LPC_I2C->CONCLR = (1<<3)|(1<<2);

        break;

    /*case 0x48:
         LPC_I2C->CONCLR = (1<<3); // clear ACK and stop
        break;
*/
    case 0x58: // receive data
        set_leds(LPC_I2C->DAT);
        start();
        break;

    default:
            break;

    }
}



// I2C with interrupts

int main(void)
{
    init();

    start();

    while(1)
    {
        __WFI();
    }
}

