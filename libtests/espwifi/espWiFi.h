#ifndef espWiFi_h
#define espWiFi_h

#include "Arduino.h"

#include <ESP8266WiFi.h>

class espWiFi
{
public:
  espWiFi(bool serialIsEnabled=true);

  void StartAsClient(const char *ssid="IoT_Lab", const char *password="nopython", bool waitForConnection=true);
  void WaitForConnection();

  bool IsConnected();

private:
  String _ssid, _password;
  bool _serialIsEnabled;
};


#endif
