// MQ135 Smoke/Gas Sensor with Arduino
const int mq135Pin = A0;
const int ledPin = 11;
const int buzzerPin = 12;  // Connect the buzzer to digital pin 12
int baseline = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
  Serial.begin(9600);

  long total = 0;
  Serial.println("Calibrating MQ135 sensor... Please ensure clean air.");
  for (int i = 0; i < 20; i++) {
    int reading = analogRead(mq135Pin);
    total += reading;
    delay(100);
  }

  baseline = total / 20;
  Serial.print("Calibration complete. Baseline value: ");
  Serial.println(baseline);
}

void loop() {
  int sensorValue = analogRead(mq135Pin);
  Serial.print("Current MQ135 reading: ");
  Serial.println(sensorValue);

  if (sensorValue > baseline + 30) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
    Serial.println("⚠️ Smoke or Gas Detected!");
    Serial.println("LED ON, Buzzer ON");
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);   // Turn off buzzer
    Serial.println("LED OFF, Buzzer OFF");
  }

  delay(500);
}
