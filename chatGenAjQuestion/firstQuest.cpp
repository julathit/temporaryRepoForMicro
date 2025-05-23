#define LED_PIN_B0 0
#define LED_PIN_B1 1
#define BUTTON_PIN_D4 4

volatile int r21_counter = 200;

void setup() {
  pinMode(LED_PIN_B0, OUTPUT);
  pinMode(LED_PIN_B1, OUTPUT);
  pinMode(BUTTON_PIN_D4, INPUT_PULLUP);

  cli();
  TCCR0A = 0;
  TCCR0B = (1 << CS02) | (1 << CS00);
  TCNT0 = 177;
  TIMSK0 |= (1 << TOIE0);
  sei();
}

void loop() {
  if (digitalRead(BUTTON_PIN_D4) == LOW) {
    digitalWrite(LED_PIN_B0, LOW);
  } else {
    digitalWrite(LED_PIN_B0, HIGH);
  }
}

ISR(TIMER0_OVF_vect) {
  r21_counter--;
  if (r21_counter == 0) {
    r21_counter = 200;
    digitalWrite(LED_PIN_B1, !digitalRead(LED_PIN_B1));
  }
  TCNT0 = 177;
}