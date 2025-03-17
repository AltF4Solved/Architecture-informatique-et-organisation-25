#include "LPC13xx.h"
#include "leddriver.h"

// Array to store status register values
#define MAX_STATUS_VALUES 10
uint8_t status_values[MAX_STATUS_VALUES];
uint8_t status_index = 0;

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

    // Initialize status array
    for (int i = 0; i < MAX_STATUS_VALUES; i++) {
        status_values[i] = 0;
    }

    NVIC_EnableIRQ(I2C_IRQn);
}

void start(void)
{
    LPC_I2C->CONSET = (1<<5);  // start
    LPC_I2C->CONCLR = (1<<3);  // clear SI
}

void stop(void)
{
    LPC_I2C->CONCLR = ((1<<3)|(1<<2)); // clear SI and AA
    LPC_I2C->CONSET |= (1<<4); // set stop
}

void send(int data)
{
    LPC_I2C->DAT = data;
}

void I2C_IRQHandler(void)  // Corrected function name
{
    // Store status register value
    if (status_index < MAX_STATUS_VALUES) {
        status_values[status_index++] = LPC_I2C->STAT & 0xFF;
    }
    
    switch(LPC_I2C->STAT & 0xFF)
    {
    case 0x08: // Start transmitted
        send(0x90); // Slave write address
        LPC_I2C->CONCLR = (1<<3)|(1<<5); // Clear SI and STA
        break;
        
    case 0x18: // SLA+W transmitted, ACK received
        send(0); // Send register address
        LPC_I2C->CONCLR = (1<<3); // Clear SI
        break;
        
    case 0x28: // Data transmitted, ACK received
        LPC_I2C->CONSET = (1<<5); // Set STA for repeated start
        LPC_I2C->CONCLR = (1<<3); // Clear SI
        break;
        
    case 0x10: // Repeated start transmitted
        send(0x91); // Slave read address
        LPC_I2C->CONCLR = (1<<3)|(1<<5); // Clear SI and STA
        break;
        
    case 0x40: // SLA+R transmitted, ACK received
        LPC_I2C->CONCLR = (1<<3)|(1<<2); // Clear SI and AA (NOT ACK)
        break;
        
    case 0x58: // Data received, NOT ACK sent
        set_leds(LPC_I2C->DAT); // Display received data on LEDs
        stop(); // Stop the transfer as we only want to read once
        break;
        
    default:
        stop(); // In case of unexpected status, stop the transfer
        break;
    }
}

// I2C with interrupts
int main(void)
{
    init();
    start(); // Start the I2C communication

    while(1)
    {
        __WFI(); // Wait for interrupt
    }
}
