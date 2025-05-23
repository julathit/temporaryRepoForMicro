#define SWITCH0_PIN 2

void setup() {
  pinMode(SWITCH0_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(SWITCH0_PIN) == LOW) {
    Serial.write('1');
  }
  delay(50);
}