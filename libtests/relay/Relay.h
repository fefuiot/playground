#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay
{
public:
  Relay(byte inOne, byte inTwo);

  bool IsOnOne();
  bool IsOnTwo();

  void SetOnOne();
  void SetOnTwo();

  void SetOffOne();
  void SetOffTwo();

  void ToggleOne();
  void ToggleTwo();
private:
  byte _inPinOne, _inPinTwo;
  bool _isOnOne, _isOnTwo;
};

#endif
