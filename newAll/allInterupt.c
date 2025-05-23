#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL //_delay_ms(100); // between line 49-50

unsigned char y = 200;
unsigned char z = 2;

void PIN_SETUP() {          //A function to set up the pin modes
    DDRB |= (1<<0);         //Set PB0 as an output -> LED0
    PORTB &= ~(1<<0);       //Set PB0 = 0
    DDRB |= (1<<1);         //Set PB1 as an output -> LED1
    PORTB &= ~(1<<1);       //Set PB1 = 0
    DDRB |= (1<<2);         //Set PB2 as an output -> LED2
    PORTB &= ~(1<<2);       //Set PB2 = 0
    DDRB |= (1<<3);         //Set PB3 as an output -> LED3
    PORTB &= ~(1<<3);       //Set PB3 = 0
    DDRD &= ~(1<<4);        //Set PD4 as an input -> SW
    PORTD |= (1<<4);        //Pull-up resistor for PD4
    PORTD |= (1<<3);        //Pull-up resistor for PD3(INT1)  (1<<3)
    PORTD |= (1<<5);        //Pull-up resistor for PD5(Pin Change)
}

void TIMERO_SETUP() {       //A function to set TIMER0
    TCNT0 = 0xB2;           //Set initial value of Timer0
    TCCR0A = 0x00;          //Set to normal mode
    TCCR0B = 0x05;          //Pre-scaling = 1024, start the timer
}

int main() {
    PIN_SETUP();            //Call the PIN_SETUP function
    TIMERO_SETUP();         //Call the TIMERO_SETUP function

    //INT0 Interrupt Setup
    EIMSK = 0x02;           //Enable the INT0 Interrupt
    EICRA = 0x00;           //Set the falling-edge trigger

    //PD5 Pin Change Interrupt
    PCICR = 0x04;           //Enable the PORTD Pin Change Interrupt
    PCMSK2 = 0x20;          //Enable the interrupt from PD5

    //TIMERO Overflow Interrupt
    TIMSK0 = 0x01;          //Enable the Timer0 Overflow Interrupt

    sei();                  //Enable the global interrupt

    while (1) {
        if (!(PIND & (1<<4))) { //Check PD4=0?
            PORTB |= (1<<0);    //Yes, PB0=1 -> LED0 on
        } else {
            PORTB &= ~(1<<0);   //No, PB0=0 -> LED0 off
        }
        _delay_ms(100);
    }
    return (0);
}

ISR(INT1_vect) {             //ISR
    PORTB ^= (1<<1);         //and toggle PB1
}

ISR(PCINT2_vect) {           //ISR
    z--;                     //Decrease z by 1
    if (z==0) {              //Check if z=0?
        PORTB ^= (1<<2);     //and toggle PB2
        z=2;
    }
}

ISR(TIMER0_OVF_vect) {       //ISR
    y--;                     //Decrease y by 1
    if (y==0) {              //Check y=0
        y = 200;             //Yes, reset y = 200
        PORTB ^= (1<<3);     //and toggle PB3
    }
    TCNT0 = 0xB2;            //Set TCNT0 = 0xB2
}