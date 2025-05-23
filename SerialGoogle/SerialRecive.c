#include <avr/io.h>
#include <util/delay.h>

void usart_init(void) {
    UCSR0B = (1<<RXEN0);            // Enable USART receiver
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // Async, 8 bits
    UBRR0L = 103;                   // Baud rate = 9600
}

void pin_setup(void) {
    DDRB |= (1<<0);                 // Set PB0 as output (LED0)
    PORTB &= ~(1<<0);               // Set LED0 initial state to OFF
    DDRB |= (1<<1);                 // Set PB1 as output (LED1)
    PORTB &= ~(1<<1);               // Set LED1 initial state to OFF
}

int main(void) {
    unsigned char received_data;
    pin_setup();
    usart_init();

    while(1) {
        // Wait until data is received
        while (!(UCSR0A & (1<<RXC0))); // Check if data is available

        // Read the received data
        received_data = UDR0;

        // Process received commands
        if (received_data == '1') {    // Toggle LED0
            PORTB ^= (1<<0);
        } else if (received_data == '2') { // Toggle LED1
            PORTB ^= (1<<1);
        }
    }
    return 0;
}