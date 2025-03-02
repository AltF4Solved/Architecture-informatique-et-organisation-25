
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





// #include <stdint.h>
// #include <stdbool.h>
// #include "LPC13xx.h" // Device header

// void pin_low(void) {
//     LPC_GPIO1->DATA &= ~(1 << 6); // Set pin PIO1_6 low to match main2.c functionality
// }

// void pin_high(void) {
//     LPC_GPIO1->DATA |= (1 << 6); // Set pin PIO1_6 high to match main2.c functionality
// }

// void initialize(void) {
//     LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); // Enabling clock for CT32B0 as in main2.c
//     LPC_TMR32B0->TCR = 0; // Disable timer to setup
//     LPC_TMR32B0->TC = 0; // Reset timer counter
//     LPC_TMR32B0->PR = 0x0AFC80; // Prescale register for 1 Hz
//     LPC_TMR32B0->PC = 0; // Reset prescale counter
//     LPC_TMR32B0->MR0 = 0x50; // Match register 0
//     LPC_TMR32B0->MR3 = 0x64; // Match register 3
//     LPC_TMR32B0->MCR = (1<<0) | (1<<9) | (1<<10); // Configure match control register

//     LPC_GPIO1->DIR |= (1 << 6); // Set PIO1_6 as output
//     LPC_GPIO3->DIR |= 1; // Set GPIO3 as output for LED control
// }

// void timer_start(void) {
//     LPC_TMR32B0->TCR = (1<<0); // Enable timer
// }

// void timer_stop(void) {
//     LPC_TMR32B0->TCR &= ~(1<<0); // Disable timer
//     LPC_TMR32B0->TCR |= (1<<1); // Reset timer
// }

// int main(void) {
//     initialize();
//     timer_start();
//     while(1) {
//         if (LPC_TMR32B0->IR & (1<<3)) { // Check MR3 interrupt
//             pin_high();
//             LPC_TMR32B0->IR = (1<<3); // Clear MR3 interrupt
//         }

//         if ((LPC_TMR32B0->IR & (1<<0)) && !(LPC_TMR32B0->IR & (1<<3))) { // Check MR0 interrupt and ensure MR3 is not set
//             pin_low();
//             LPC_TMR32B0->IR = (1<<0); // Clear MR0 interrupt
//         }
//     }
//     return 0;
// }
