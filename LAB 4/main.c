#include "delay.h"  // Assuming delay.c and delay.h are provided for the delay function

// Initialize GPIO for LED
static void init(void) {
    *(volatile uint32_t *)0x50000000 = 0x00000001;  // Set direction to output for LED (adjust the register address as needed)
}

// Turn LED off
static void led_off(void) {
    *(volatile uint32_t *)0x50000014 = 0x00000000;  // Set the correct bit to turn off the LED (adjust the register address)
}

// Turn LED on
static void led_on(void) {
    *(volatile uint32_t *)0x50000014 = 0x00000001;  // Set the correct bit to turn on the LED (adjust the register address)
}

int main(void) {
    init();  // Initialize LED pin

    while (1) {
        led_on();             // Turn LED on
        delay_ms(500);        // Wait for 500 ms
        led_off();            // Turn LED off
        delay_ms(500);        // Wait for 500 ms
    }
}
