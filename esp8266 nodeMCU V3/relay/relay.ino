// Test of LED tape connected to simple 2 relay module

#define SIGNAL_PIN 5  // D1

void setup() {
  pinMode(SIGNAL_PIN, OUTPUT);
}

void loop() {
  digitalWrite(SIGNAL_PIN, HIGH);
  delay(1000);
  digitalWrite(SIGNAL_PIN, LOW);
  delay(1000);
}


