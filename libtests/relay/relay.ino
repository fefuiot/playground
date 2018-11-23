#include "Relay.h"

Relay relay(D0, NULL);

void setup() {
  relay.SetOnOne();
  
}

void loop() {
  relay.ToggleOne();
  delay(500);
}
