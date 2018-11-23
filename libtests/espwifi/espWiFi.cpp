#include <ESP8266WiFi.h>

#include "Arduino.h"
#include "espWiFi.h"

espWiFi::espWiFi(bool serialIsEnabled)
{
  _serialIsEnabled = serialIsEnabled;
}

void espWiFi::StartAsClient(const char *ssid, const char *password, bool waitForConnection)
{
  _ssid = ssid;
  _password = password;

  WiFi.begin(ssid, password);
  if (waitForConnection)
    WaitForConnection();
}

void espWiFi::WaitForConnection()
{
  if (_serialIsEnabled)
    Serial.println("Connecting to \"" + _ssid + "\"");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    if (_serialIsEnabled)
      Serial.print(".");
  }

  if (_serialIsEnabled)
  {
    Serial.println("Done. Info:");
    WiFi.printDiag(Serial);   //Change this to IP only
  }
}

bool espWiFi::IsConnected()
{
  return WiFi.status() == WL_CONNECTED;
}
