#define LED_PIN_D6 6
#define LED_PIN_D5 5
#define BUTTON_PIN_C2 A2 // Analog pin A2 is PC2 on Uno
#define PULLUP_PIN_D3 3

volatile unsigned char z_counter = 8;

void setup() {
  pinMode(LED_PIN_D6, OUTPUT);
  digitalWrite(LED_PIN_D6, LOW);
  pinMode(LED_PIN_D5, OUTPUT);
  digitalWrite(LED_PIN_D5, LOW);

  pinMode(BUTTON_PIN_C2, INPUT_PULLUP);
  pinMode(PULLUP_PIN_D3, OUTPUT);
  digitalWrite(PULLUP_PIN_D3, HIGH);

  // External Interrupt 1 (INT1) on Digital Pin 3 (PD3)
  attachInterrupt(digitalPinToInterrupt(PULLUP_PIN_D3), INT1_ISR, RISING);

  // Pin Change Interrupt for PC2 (PCINT10)
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT10);

  sei();
}

void loop() {
}

ISR(INT1_vect) {
  digitalWrite(LED_PIN_D5, !digitalRead(LED_PIN_D5));
}

ISR(PCINT1_vect) {
  z_counter--;
  if (z_counter == 0) {
    digitalWrite(LED_PIN_D6, !digitalRead(LED_PIN_D6));
    z_counter = 8;
  }
}