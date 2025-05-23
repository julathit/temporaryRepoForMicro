.ORG 0x0
    jmp MAIN
.ORG 0x20
    jmp T0_OV_ISR

.ORG 0x100
MAIN: LDI R16, HIGH(RAMEND)
    OUT SPH, R16
    LDI R16, LOW(RAMEND)
    OUT SPL, R16
    
    CALL PIN_SETUP
    LDI R16, (1<<TOIE0) ;set up pin mode
    STS TIMSK0, R16 ; Enable Timer0
    SEI ; Enable Interupt
    CALL TIMER0_SETUP
    LDI R21, 200 ; for loop inside interupt

LOOP: SBIC PIND, 4 ;for press pin4 to switch on and of sbic is skip bit if clear so if pind4 = 0 to on
    RJMP L_OFF
    RJMP L_ON
L_OFF: CBI PORTB, 0
    RJMP LOOP
L_ON: CBI L_ON
    RJMP LOOP

PIN_SETUP:
    SBI DDRB, 0
    SBI DDRB, 1
    CBI DDRD, 4
    SBI DDRB, 0
    SBI DDRB, 1
    CBI DDRD, 4
    RET

TIMER0_SETUP:
    LDI R20, 177
    OUT TCNT0, R20
    LDI R20, 0
    OUT TCCR0A, R20
    LDI R20, 5
    OUT TCCR0B, R20

.ORG 0x200
T0_OV_ISR:
    DEC R21 
    BRNE HERE ;jump if above < 0
    LDI R21, 200
    IN R17, PORTB
    LDI R18, (1<<1)
    EOR R17 ,R18
    OUT PORTB, R17
HERE: 
    LDI R18, 177
    OUT TCNT0, R18
    RETI
