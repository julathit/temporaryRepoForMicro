#include <avr/io.h>

void usart_init(void) {
    UCSR0B = (1<<RXEN0);    //Enable USART receiver
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //Async, 8 bits,
    UBRR0L = 103;           //Baud rate = 9600
}

void pin_setup(void) {  //Set output pins
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;
}

int main(void) {

    usart_init();
    pin_setup();
    while (1) {         //Receive the input and show it on output pins
        while (!(UCSR0A&(1<<RXC0)));  //Wait until RXC0 flag = 1
        
        if (UDR0 == 0b0001010){
            PORTB = 0b10000000;  
            PORTD = 0b00100010; 
        }
        else if (UDR0 == 0b0000011){
            PORTB = 0b10000000;  
            PORTD = 0b00001001;  
        }

    }
    return 0;
}