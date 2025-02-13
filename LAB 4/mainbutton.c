#include "delay.h"
#include <stdbool.h>

static void init(void) {
    *(volatile uint32_t *)0x50000000 = 0x00000001;  // Set direction to output for LED (adjust register address)
}

static void led_off(void) {
    *(volatile uint32_t *)0x50000014 = 0x00000000;
}

static void led_on(void) {
    *(volatile uint32_t *)0x50000014 = 0x00000001;

static void init_button(void) {
    *(volatile uint32_t *)0x50000000 = 0x00000000;
}

static bool but1_pressed(void) {
    return (*(volatile uint32_t *)0x50000010 & 0x00000001) == 0;
}

int main(void) {
    init();
    init_button();

    bool led_state = false

    while (1) {
        if (but1_pressed()) {
            led_state = !led_state;
            if (led_state) {
                led_on();
            } else {
                led_off();
            }
            delay_ms(250); //debounce
        }
    }
}
