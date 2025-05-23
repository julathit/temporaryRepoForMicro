#include <avr/io.h>
#include <util/delay.h>

// Function to initialize UART
void usart_init(void) {
    UCSR0B = (1<<TXEN0);            // Enable USART transmitter
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // Async, 8 bits
    UBRR0L = 103;                   // Baud rate = 9600
}

void pin_setup(void) {
    DDRD &= ~(1<<PD2);              // Set PD2 as input (Switch 0)
    PORTD |= (1<<PD2);              // Enable pull-up for Switch 0
}

int main(void) {
    pin_setup();
    usart_init();

    while(1) {
        // Check if Switch 0 is pressed (PD2 is LOW)
        if (!(PIND & (1<<PD2))) {
            while (!(UCSR0A & (1<<UDRE0))); // Wait until UDRO is empty
            UDR0 = '1';                    // Send data
        }

        _delay_ms(50);              // Small polling delay
    }
    return 0;
}