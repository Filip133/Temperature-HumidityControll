#include "LcdHandler.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void LcdHandler::printMessage(char* message)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(message);
}

void LcdHandler::printHomeScreen()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Temp: ");
	lcd.print((int)*temp);
	lcd.print(" C");
	lcd.setCursor(0, 1);
	lcd.print("Hum: ");
	lcd.print((int)*hum);
	lcd.print(" %");
}

void LcdHandler::refrashScreen(int menuPosittion, double *setParameters, Menu *menu)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(menu->getItem(menuPosittion));
	lcd.setCursor(0, 1);
	lcd.print((int)setParameters[menuPosittion]);
}

LcdHandler::LcdHandler()
{
	lcd.begin(16, 2);
}

LcdHandler::LcdHandler(double * temperatuere, double * humidity)
{
	temp = temperatuere;
	hum = humidity;
}


