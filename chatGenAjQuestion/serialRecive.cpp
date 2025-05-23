#define LED0_PIN 8 // Corresponds to PB0 on ATmega328P (Digital Pin 8 on Uno)
#define LED1_PIN 9 // Corresponds to PB1 on ATmega328P (Digital Pin 9 on Uno)

void setup() {
  // Pin Setup
  pinMode(LED0_PIN, OUTPUT);
  digitalWrite(LED0_PIN, LOW); // LED0 initial state OFF
  pinMode(LED1_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW); // LED1 initial state OFF

  // USART (Serial) Initialization
  // Corresponds to UCSR0B, UCSR0C, UBRR0L setup for 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Wait until data is received
  if (Serial.available()) {
    // Read the received data
    char received_data = Serial.read();

    // Process received commands
    if (received_data == '1') { // Toggle LED0 and LED1
      digitalWrite(LED0_PIN, !digitalRead(LED0_PIN)); // Toggle LED0
      digitalWrite(LED1_PIN, !digitalRead(LED1_PIN)); // Toggle LED1
    }
  }
}