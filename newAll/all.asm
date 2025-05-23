.ORG 0x0
    JMP MAIN
.ORG 0x04
    JMP INT1_ISR
.ORG 0x8A
    JMP PCINTB_ISR
.ORG 0x20
    JMP TO_OV_ISR

.ORG 0x100
MAIN:
    LDI     R16, HIGH(RAMEND)
    OUT     SPH, R16
    LDI     R16, LOW(RAMEND)
    OUT     SPL, R16

    CALL    PIN_SETUP

    LDI     R16, (1<<TOIEO)      ; enable Timer0 overflow interrupt
    STS     TIMSKO, R16

    LDI     R16, (1<<INT1)       ; enable the external interrupt INT1
    OUT     EIMSK, R16
    LDI     R16, (1<<ISC11)
    STS     EICRA, R16

    LDI     R16, (1<<PCIE2)      ; enable pin change interrupt PORTD
    STS     PCICR, R16
    LDI     R16, 0x20
    STS     PCMSK2, R16

    SEI
    CALL    TIMERO_SETUP
    LDI     R21, 200
    LDI     R20, 2

LOOP:
    SBIC    PIND, 4
    RJMP    L_OFF
    RJMP    L_ON
L_OFF: CBI     PORTB, 0
    RJMP    LOOP
L_ON: SBI     PORTB, 0
    RJMP    LOOP

PIN_SETUP:
    SBI     DDRB, 0
    CBI     PORTB, 0
    SBI     DDRB, 1
    CBI     PORTB, 1
    CBI     DDRD, 5
    CBI     DDRD, 4
    CBI     DDRD, 3
    SBI     PORTD, 5
    SBI     PORTD, 4
    SBI     PORTD, 3
    RET

TIMERO_SETUP:
    LDI     R20, 177
    OUT     TCNT0, R20
    LDI     R20, 0x00
    OUT     TCCROA, R20
    LDI     R20, 0x05
    OUT     TCCR0B, R20
    RET

.ORG 0x200
T0_OV_ISR:
    DEC     R21
    BRNE    HERE1
    LDI     R21, 200
    IN      R17, PORTB
    LDI     R18, (1<<1)
    EOR     R17, R18
    OUT     PORTB, R17
HERE1:
    LDI     R18, 177
    OUT     TCNT0, R18
    RETI

INT1_ISR:
    IN      R17, PORTB
    LDI     R18, (1<<2)
    EOR     R17, R18
    OUT     PORTB, R17
    RETI

PCINTB_ISR:
    DEC     R20
    BRNE    HERE
    IN      R17, PORTB
    LDI     R18, (1<<3)
    EOR     R17, R18
    OUT     PORTB, R17
    LDI     R20, 2
HERE:
    RETI