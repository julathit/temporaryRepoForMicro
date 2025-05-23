#include <DHT.h>

#define SOIL_MOISTURE_ANALOG_PIN A0
#define SOIL_MOISTURE_DIGITAL_PIN 2
#define DHT_PIN                   3
#define PUMP_RELAY_PIN            4
#define STATUS_LED_PIN            5

#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

const int DRY_SOIL_THRESHOLD = 600;
const int WET_SOIL_THRESHOLD = 300;

const long WATERING_DURATION_MS = 2000;
const long SENSOR_READ_INTERVAL_MS = 5000;

int soilMoistureValue = 0;
float temperatureC = 0.0;
float humidity = 0.0;

unsigned long previousMillisSensor = 0;
unsigned long previousMillisWatering = 0;

bool isWatering = false;

void setup() {
    pinMode(SOIL_MOISTURE_ANALOG_PIN, INPUT);
    pinMode(SOIL_MOISTURE_DIGITAL_PIN, INPUT);
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);

    digitalWrite(PUMP_RELAY_PIN, HIGH);
    digitalWrite(STATUS_LED_PIN, LOW);

    dht.begin();
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillisSensor >= SENSOR_READ_INTERVAL_MS) {
        previousMillisSensor = currentMillis;

        soilMoistureValue = analogRead(SOIL_MOISTURE_ANALOG_PIN);

        humidity = dht.readHumidity();
        temperatureC = dht.readTemperature();

        if (isnan(humidity) || isnan(temperatureC)) {
            return;
        }

        if (soilMoistureValue >= DRY_SOIL_THRESHOLD && !isWatering) {
            startWatering();
        }
    }

    if (isWatering) {
        if (currentMillis - previousMillisWatering >= WATERING_DURATION_MS) {
            stopWatering();
        }
    }
}

void startWatering() {
    isWatering = true;
    digitalWrite(PUMP_RELAY_PIN, LOW);
    digitalWrite(STATUS_LED_PIN, HIGH);
    previousMillisWatering = millis();
}

void stopWatering() {
    isWatering = false;
    digitalWrite(PUMP_RELAY_PIN, HIGH);
    digitalWrite(STATUS_LED_PIN, LOW);
}