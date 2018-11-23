#include "espWiFi.h"

espWiFi wifi(true);

void setup() {
  Serial.begin(115200);

  wifi.StartAsClient();
}

void loop() {
  Serial.println(wifi.IsConnected());
  delay(1000);
}
