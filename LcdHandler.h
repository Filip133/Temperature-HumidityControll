#pragma once

#include "LiquidCrystal.h"
#include "Menu.h"
class LcdHandler {
public:
	void printMessage(char* message);
	void printHomeScreen();
	void refrashScreen(int menuPosittion,double *setParameters, Menu *menu);
	LcdHandler();
	LcdHandler(double* temperatuere, double* humidity);
private:
	double* temp;
	double* hum;
};

