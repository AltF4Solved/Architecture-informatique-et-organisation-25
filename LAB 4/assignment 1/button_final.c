#include <stdbool.h>
#include <stdint.h>
#include "LPC13xx.h"
#include "delay.h"  // Assuming delay functions are correctly defined

#define LED_PORT LPC_GPIO3
#define LED_PIN  (1 << 0) // P3_0 for LED0 (adjust for your specific LED)
#define BUTTON_PORT LPC_GPIO2
#define BUTTON_PIN  (1 << 9) // P2_9 for BUT1 (USER button)

// Initialize the LED
void init_led(void) {
    LED_PORT->DIR |= LED_PIN; // Set the LED pin as output
    LED_PORT->DATA |= LED_PIN; // Turn the LED off (assuming active-low LED)
}

// Turn LED on
void led_on(void) {
    LED_PORT->DATA &= ~LED_PIN; // Set pin low to turn LED on
}

// Turn LED off
void led_off(void) {
    LED_PORT->DATA |= LED_PIN; // Set pin high to turn LED off
}

// Initialize the button
void init_button(void) {
    BUTTON_PORT->DIR &= ~BUTTON_PIN; // Set button pin as input
}

// Check if the button is pressed
bool button_pressed(void) {
    return !(BUTTON_PORT->DATA & BUTTON_PIN); // Return true if button is pressed (active-low)
}

int main(void) {
    init_led();     // Initialize LED
    init_button();  // Initialize Button

    // Infinite loop
    while (1) {
        if (button_pressed()) {
            led_on(); // Turn LED on when button is pressed
        } else {
            led_off(); // Turn LED off when button is not pressed
        }
    }
}
