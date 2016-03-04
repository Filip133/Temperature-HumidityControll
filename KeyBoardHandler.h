#pragma once
#include <stdint.h>

class KeyBoardHandler
{
public:
	KeyBoardHandler(uint8_t inPin);
	KeyBoardHandler();
	int readKey();
private:
	uint8_t keyPin;
	int btnPressed;
};


