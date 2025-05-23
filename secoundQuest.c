#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char z = 8;

void PIN_SETUP(){
    DDRD |= (1<<6)|(1<<5);
    PORTD &= ~((1<<6)|(1<<5));
    DDRC &= ~(1<<2);
    PORTC |= (1<<2);
    PORTD |= (1<<3);
}

int main(){
    PIN_SETUP();
    //set ext Interrupt Setup
    EIMSK = (1<<INT1); // or you can use 0x2 just set the int1 or (1<<INT1)
    EIRCA = (1<<ISC11)|(1<<ISC10); // or use 0xC set use falling edge

    // Pin Change Interupt
    PCICR = (1<<PCIE1);
    PCMSK1 = 0b100; //start with 0 2,1,0

    sei();  //enable interupt
    while (true){}
    return 0;
}

ISR(INT1_vect){
    PORTD ^= (1<<5);
}

ISR(PCINT1_vect){
    z--;
    if (z==0){
        PORTD ^= (1<<6);
        z = 8;// for press 4 time
    }
}