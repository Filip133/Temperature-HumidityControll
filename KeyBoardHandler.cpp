#include "KeyBoardHandler.h"
#include "Arduino.h"

KeyBoardHandler::KeyBoardHandler(uint8_t inPin)
{
	keyPin = inPin;
	pinMode(keyPin, INPUT);
}

KeyBoardHandler::KeyBoardHandler()
{
}

int KeyBoardHandler::readKey()
{
	btnPressed = analogRead(keyPin);
	delay(75);
	if (btnPressed == analogRead(keyPin)) {
		if (btnPressed < 50)   return 1; // right
		if (btnPressed < 195)  return 2; // up
		if (btnPressed < 380)  return 3; // down
		if (btnPressed < 555)  return 4; // left
		if (btnPressed < 790)  return 5; // select
	}
	return 0; // if nathing
}
