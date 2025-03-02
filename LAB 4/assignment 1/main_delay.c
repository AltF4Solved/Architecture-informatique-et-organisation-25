
#include <stdint.h>
#include "LPC13xx.h"    // Assuming the LPC13xx.h is the MCU-specific header file provided in the assignment
#include "delay.h"      // Including the delay functions provided by the user


#define LED_PORT LPC_GPIO3       // Assuming LEDs are connected to Port 3
#define LED_PIN  (1 << 3)        // LED3 is connected to the third pin (P3_3) of the respective port

// Function prototypes
void init_led(void);
void led_on(void);
void led_off(void);
void blink(void);

// LED initialization function
void init_led(void) {
     LPC_GPIO3->DIR |= (1 << 0); // Set the direction of the LED pin to output
}

void led_on(void) {
    LPC_GPIO3->DATA &= ~(1 << 0); // Set the LED pin low to turn the LED on
}

void led_off(void) {
    LPC_GPIO3->DATA |= (1 << 0); // Set the LED pin high to turn the LED off
}

// Initialize the button using CMSIS
void init_button(void) {
    LPC_GPIO0->DIR &= ~BUTTON_PIN; // Set the button pin as input
}

// Check if button 1 is pressed
bool but1_pressed(void) {
    return !(LPC_GPIO0->DATA & BUTTON_PIN); // Return true if button is pressed
}

void blink(void) {
            // Turn the LED on
        led_on();
        // Wait for 500ms
       delay_ms(500);
        // Turn the LED off
        led_off();
        //Wait for 500ms
        delay_ms(500);
}
// Main function
int main(void) {
    // Initialize the LED
    init_led();

    // Infinite loop
    while (1) {
        // Blink
        blink();
    }
}
