#include "LPC1343.h"

void init_timer(void) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);

    LPC_TMR32B0->TCR = 0x02;
    LPC_TMR32B0->TC = 0;
    LPC_TMR32B0->PR = 0;
    LPC_TMR32B0->MR3 = 1000000;
    LPC_TMR32B0->MR0 = 800000;
    LPC_TMR32B0->MCR = (1 << 0);
    LPC_TMR32B0->MCR |= (1 << 3);
}

void timer_start(void) {
    LPC_TMR32B0->TCR = 0x01;
}

void timer_stop(void) {
    LPC_TMR32B0->TCR = 0x00;
}

int main(void) {
    init_timer();
    NVIC_EnableIRQ(TMR32B0_IRQn);
    LPC_IOCON->PIO1_6 = 0x01;
    pin_low();
    timer_start();
    while (1) {
        __WFI();
    }
}
