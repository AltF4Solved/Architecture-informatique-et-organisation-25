#include "LPC13xx.h"

#define IOCON_PIO1_6 (*((volatile unsigned long *)(0x400440A4))) // Pin config register for PIO1_6
#define TMR32B0TCR (*((volatile unsigned long *)(0x40014004))) // Timer Control Register
#define TMR32B0TC (*((volatile unsigned long *)(0x40014008))) // Timer Counter
#define TMR32B0PR (*((volatile unsigned long *)(0x4001400C))) // Prescale Register
#define TMR32B0PC (*((volatile unsigned long *)(0x40014010))) // Prescale Counter
#define TMR32B0MCR (*((volatile unsigned long *)(0x40014014))) // Match Control Register
#define TMR32B0MR0 (*((volatile unsigned long *)(0x40014018))) // Match Register 0
#define TMR32B0MR3 (*((volatile unsigned long *)(0x40014024))) // Match Register 3
#define TMR32B0IR (*((volatile unsigned long *)(0x40014000))) // Interrupt Register
#define TMR32B0PWMC (*((volatile unsigned long *)(0x40014074))) // PWM Control Register
#define GPIO1DIR (*((volatile unsigned long *)(0x50018000))) // GPIO1 Direction Register
#define GPIO1DATA (*((volatile unsigned long *)(0x50013FFC))) // GPIO1 Data Register
#define SYSAHBCLKCTRL (*((volatile unsigned long *)(0x40048080))) // System AHB Clock Control Register
#define NVIC_ISER0 (*((volatile unsigned long *)(0xE000E100))) // Interrupt Set Enable Register

#define TIMER_ENABLE (1 << 0)
#define TIMER_RESET (1 << 1)
#define PWM_CHANNEL_ENABLE (1 << 0) // Enable PWM for channel 0
#define MR0_INTERRUPT (1 << 0) // Match Register 0 interrupt
#define MR3_INTERRUPT (1 << 3) // Match Register 3 interrupt
#define TIMER32_0_IRQ (1 << 18) // IRQ18 for Timer32_0
#define PIN_NUMBER 6 // Pin number for PIO1_6

void enable_timer_clock(void) {
    SYSAHBCLKCTRL |= (1 << 9); // Enable clock for 32-bit Timer 0
}

void initialize_pin_for_pwm(void) {
    IOCON_PIO1_6 = 0x2; // Set pin function to CT32B0_MAT0
    GPIO1DIR |= (1 << PIN_NUMBER);
}

void initialize_timer_for_pwm(void) {
    TMR32B0TCR |= TIMER_RESET;
    for (volatile int i = 0; i < 1000; i++);
    TMR32B0TCR &= ~TIMER_RESET;

    TMR32B0PR = 0; // No prescaler
    TMR32B0MR3 = 719999; // 100Hz period
    TMR32B0MR0 = 576000; // 80% duty cycle
    TMR32B0MCR = (1 << 10) | (MR0_INTERRUPT | MR3_INTERRUPT); // Reset on MR3, enable interrupts
    TMR32B0PWMC = PWM_CHANNEL_ENABLE;
}

void enable_timer_interrupt(void) {
    NVIC_ISER0 |= TIMER32_0_IRQ; // Enable Timer32_0 interrupt
}

void pin_low(void) { GPIO1DATA &= ~(1 << PIN_NUMBER); }
void pin_high(void) { GPIO1DATA |= (1 << PIN_NUMBER); }
void timer_start(void) { TMR32B0TCR |= TIMER_ENABLE; }
void timer_stop(void) { TMR32B0TCR &= ~TIMER_ENABLE; }
void clear_MR0_flag(void) { TMR32B0IR = MR0_INTERRUPT; }
void clear_MR3_flag(void) { TMR32B0IR = MR3_INTERRUPT; }

void TIMER32_0_IRQHandler(void) {
    if (TMR32B0IR & MR0_INTERRUPT) {
        pin_low();
        clear_MR0_flag();
    }
    if (TMR32B0IR & MR3_INTERRUPT) {
        pin_high();
        clear_MR3_flag();
    }
}

int main(void) {
    enable_timer_clock();
    initialize_pin_for_pwm();
    initialize_timer_for_pwm();
    enable_timer_interrupt();
    timer_start();

    while(1) {
        __WFI(); // Enter sleep mode until an interrupt occurs
    }
    return 0;
}
