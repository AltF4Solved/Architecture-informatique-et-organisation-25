
#define IOCON_PIO1_6 (*((volatile unsigned long *)(0x400440A4))) // Corrected address for IOCON register for PIO1_6
#define TMR32B1TCR (*((volatile unsigned long *)(0x40018004))) // Timer Control Register
#define TMR32B1TC (*((volatile unsigned long *)(0x40018008))) // Timer Counter
#define TMR32B1PR (*((volatile unsigned long *)(0x4001800C))) // Prescale Register
#define TMR32B1PC (*((volatile unsigned long *)(0x40018010))) // Prescale Counter
#define TMR32B1MCR (*((volatile unsigned long *)(0x40018014))) // Match Control Register
#define TMR32B1MR0 (*((volatile unsigned long *)(0x40018018))) // Match Register 0
#define TMR32B1MR3 (*((volatile unsigned long *)(0x40018024))) // Match Register 3
#define TMR32B1IR (*((volatile unsigned long *)(0x40018000))) // Interrupt Register
#define TMR32B1PWMC (*((volatile unsigned long *)(0x40018074))) // PWM Control Register
#define GPIO1DIR (*((volatile unsigned long *)(0x50018000))) // GPIO1 Direction Register
#define GPIO1DATA (*((volatile unsigned long *)(0x50013FFC))) // GPIO1 Data Register with mask 0x3FFC

#define TIMER_ENABLE (1 << 0)
#define TIMER_RESET (1 << 1)
#define PWM_CHANNEL_ENABLE (1 << 0) // Enable PWM for channel 0
#define MR0_INTERRUPT (1 << 0) // Match Register 0 interrupt
#define MR3_INTERRUPT (1 << 3) // Match Register 3 interrupt
#define PIN_NUMBER 6 // Pin number for PIO1_6

void initialize_pin_for_pwm(void) {
    // Set IOCON register for PIO1_6 to enable CT32B0_MAT0
    IOCON_PIO1_6 = 0x2; // Set pin function to CT32B0_MAT0 for PWM output
    // Set GPIO1_6 to output
    GPIO1DIR |= (1 << PIN_NUMBER);
}

void initialize_timer_for_pwm(void) {
    // Reset Timer
    TMR32B1TCR |= TIMER_RESET;
    // Wait for a short period to ensure reset is effective
    for (volatile int i = 0; i < 1000; i++);
    TMR32B1TCR &= ~TIMER_RESET;

    // No prescaler, increment TC on every counter clock
    TMR32B1PR = 0;

    // Set match value for 100 Hz PWM frequency
    TMR32B1MR3 = 719999;

    // Set duty cycle to 80%
    TMR32B1MR0 = 576000;

    // Configure match control register to reset on MR3 and enable interrupt on MR0 and MR3
    TMR32B1MCR = (1 << 10) | (MR0_INTERRUPT | MR3_INTERRUPT);

    // Enable PWM mode for Match Register 0
    TMR32B1PWMC = PWM_CHANNEL_ENABLE;

    // Enable Timer
    TMR32B1TCR |= TIMER_ENABLE;
}

void pin_low(void) {
    GPIO1DATA &= ~(1 << PIN_NUMBER); // Set pin PIO1_6 low
}

void pin_high(void) {
    GPIO1DATA |= (1 << PIN_NUMBER); // Set pin PIO1_6 high
}

void timer_start(void) {
    TMR32B1TCR |= TIMER_ENABLE; // Enable the timer
}

void timer_stop(void) {
    TMR32B1TCR &= ~TIMER_ENABLE; // Disable the timer
}

void clear_MR0_flag(void) {
    TMR32B1IR = MR0_INTERRUPT; // Clear match register 0 interrupt
}

void clear_MR3_flag(void) {
    TMR32B1IR = MR3_INTERRUPT; // Clear match register 3 interrupt
}

int main(void) {
    initialize_pin_for_pwm();
    initialize_timer_for_pwm();
    timer_start();

    while(1) {
        // Polling MR0 and MR3 for generating PWM
        if (TMR32B1IR & MR0_INTERRUPT) {
            pin_low();
            clear_MR0_flag();
        }
        if (TMR32B1IR & MR3_INTERRUPT) {
            pin_high();
            clear_MR3_flag();
        }
    }

    // Return from main
    return 0;
}
