// Photo resistor sends data to analog input. 
// We print data to serial port

#define SENSOR_PIN A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(SENSOR_PIN));
  delay(1000);
}
