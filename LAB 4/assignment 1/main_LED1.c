
#include "LPC13xx.h" // Device header

#define LED_PIN (1 << 0) // LED connected to P3_0

// Timer register definitions
#define IOCON_PIO1_6 (*((volatile unsigned long *)(0x400440A4)))
#define TMR32B1TCR (*((volatile unsigned long *)(0x40018004)))
#define TMR32B1PR (*((volatile unsigned long *)(0x4001800C)))
#define TMR32B1MR0 (*((volatile unsigned long *)(0x40018018)))
#define TMR32B1MR3 (*((volatile unsigned long *)(0x40018024)))
#define TMR32B1MCR (*((volatile unsigned long *)(0x40018014)))
#define TMR32B1PWMC (*((volatile unsigned long *)(0x40018074)))

// GPIO register definitions for Port 3
#define GPIO3DIR (*((volatile unsigned long *)(0x50038000))) // GPIO3 Direction Register
#define GPIO3DATA (*((volatile unsigned long *)(0x50033FFC))) // GPIO3 Data Register

// PWM and timer settings
#define TIMER_ENABLE (1 << 0)
#define TIMER_RESET (1 << 1)
#define PWM_CHANNEL_ENABLE (1 << 0) // Enable PWM for channel 0

// Initialize the LED pin as output and turn it on
void init_led(void) {
    GPIO3DIR |= LED_PIN; // Set the direction of the LED pin to output
    GPIO3DATA &= ~LED_PIN; // Turn the LED on by setting the pin low
}

// Timer initialization for PWM
void init_timer_for_pwm(void) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10); // Enable clock for CT32B1
    LPC_IOCON->PIO1_6 &= ~0x07;           // Clear function bits
    LPC_IOCON->PIO1_6 |= 0x02;            // Set P1_6 as CT32B1_MAT0
    LPC_TMR32B1->PR = 0;                  // No prescale
    LPC_TMR32B1->MR3 = 71000000 - 1; // Match Register 3 for 0.1Hz (10 seconds period)
    LPC_TMR32B1->MR0 = (LPC_TMR32B1->MR3 + 1) * 0.8; // Match Register 0 for 80% duty cycle
    LPC_TMR32B1->MCR = (1 << 10);         // Reset on MR3
    LPC_TMR32B1->PWMC = PWM_CHANNEL_ENABLE; // PWM mode enabled for CT32B1_MAT0
}

// Start PWM function
void start_pwm(void) {
    TMR32B1TCR |= TIMER_ENABLE; // Enable timer
}

// Main function
int main(void) {
    init_led();       // Initialize the LED and turn it on
    init_timer_for_pwm(); // Initialize the timer for PWM
    start_pwm();      // Start PWM output

    while(1) {
        // The PWM signal is maintained by the timer, no software loop required.
    }

    return 0; // Return from main
}
