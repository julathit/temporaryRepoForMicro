#include <avr/io.h>
#include <avr/interrupt.h>

void usart_inint(){
    UCSR0B=(1<<TXEN0);
    UCSR0C = ((1<<UCSZ01)|(1<<UCSZ00));
    UBRR0L = 103;
}

void pin_setup(){
    DDRB = 0;
    PORTB = 0;
    DDRD = 0;
    PORTB = 0;
}

int main(){
    usart_inint();
    pin_setup();
    while (true)
    {
        while (!){}
        
    }
    
}
