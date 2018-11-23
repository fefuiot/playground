#include "Arduino.h"
#include "Relay.h"

// On esp8266 HIGH mode acts as "Off" state
#define _OFF HIGH
#define _ON LOW

/// Initial state for relay signal pins: off
Relay::Relay(byte inOne, byte inTwo)
{
  _inPinOne = inOne;
  _inPinTwo = inTwo;

  if (_inPinOne != NULL)
  {
    pinMode(_inPinOne, OUTPUT);
    digitalWrite(_inPinOne, _OFF);
  }

  if (_inPinTwo != NULL)
  {
    pinMode(_inPinTwo, OUTPUT);
    digitalWrite(_inPinTwo, _OFF);
  }

  _isOnOne = false;
  _isOnTwo = false;
}

bool Relay::IsOnOne()
{
  return _isOnOne;
}

bool Relay::IsOnTwo()
{
  return _isOnTwo;
}

void Relay::SetOnOne()
{
  if (_inPinOne != NULL && !_isOnOne)
  {
    digitalWrite(_inPinOne, _ON);
    _isOnOne = true;
  }
}

void Relay::SetOnTwo()
{
  if (_inPinTwo != NULL && !_isOnTwo)
  {
    digitalWrite(_inPinTwo, _ON);
    _isOnTwo = true;
  }
}

void Relay::SetOffOne()
{
  if (_inPinOne != NULL && _isOnOne)
  {
    digitalWrite(_inPinOne, _OFF);
    _isOnOne = false;
  }
}

void Relay::SetOffTwo()
{
  if (_inPinTwo != NULL && _isOnTwo)
  {
    digitalWrite(_inPinTwo, _OFF);
    _isOnTwo = false;
  }
}

void Relay::ToggleOne()
{
  if (_isOnOne)
    SetOffOne();
  else
    SetOnOne();
}

void Relay::ToggleTwo()
{
  if (_isOnTwo)
    SetOffTwo();
  else
    SetOnTwo();
}
