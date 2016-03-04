#include <dht.h>
#include "LcdHandler.h"
#include "KeyBoardHandler.h"
#include <EEPROM\EEPROM.h>
#include "Menu.h"
#include "Timer-master\Timer.h"

#define DHTSENSORPIN A1 // pin of DHT11 sensor
#define KEYPADPIN A0 // keypad pin
#define RELAYTEMPPIN 12 // relay pin of heating or cooling
#define RELAYHUMPIN 13 // relay pin of humidification or dehumidification
#define HUMIDITYCORRECTION 31.00 // correction of humidity sensor(DHT11)
#define MENUTIME 10000 // time to menu autoclose
#define REFRASHINTERVAL 10000 // refrash interval for screen, relays ...

LcdHandler lcdHandler;
dht dhtSensor;
KeyBoardHandler keyboardHandler = KeyBoardHandler(A0);
Menu menu = Menu();
Timer t;
bool isHeating; // heating or cooling
bool isHumidification; // humidification or dehumidification
double temp, hum; // current temperature and humidity
double setParameters[6];//temp,hum,tempPrecission,humPrecission,isHeating,isHumitity
int pressedKey; // witch key is pressed
bool isMenuOpen = false;
int menuPossition = -1;
unsigned long buttonPressTime; // time in milis when is button pressed
int screenCorrector = 0; // correct blinking bug from timer

void setup()
{
	prepareRelays(); // set pins and default output for relays
	lcdHandler = LcdHandler(&temp,&hum);
	for (int i = 0; i < 6; i++) { // read and set values from EEPROM(permanent memory)
		setParameters[i] = EEPROM.read(i);
		if (setParameters[i] == 255)
			setParameters[i] = 0;
	}
	if (setParameters[4] == 0)
		isHeating = true;
	else(isHeating = false);
	if (setParameters[5] == 0)
		isHumidification = true;
	else
		isHumidification = false;
	delay(2000);
}
void loop()
{
	t.every(10000, doLogich);
	pressedKey = keyboardHandler.readKey();
	if (pressedKey != 0) {
		buttonPressed();
	}
	t.update();
	screenCorrector++;
	if (screenCorrector > 10)
		screenCorrector = 0;
	if (isMenuOpen && millis() - buttonPressTime > MENUTIME)
		isMenuOpen = false;
}

void doLogich() {
	if (!isMenuOpen && screenCorrector == 0) {
		dhtSensor.read11(DHTSENSORPIN);
		if (temp != dhtSensor.temperature || hum != (dhtSensor.humidity + HUMIDITYCORRECTION)) {
			temp = dhtSensor.temperature;
			hum = dhtSensor.humidity + HUMIDITYCORRECTION;
			if (hum > 100) {
				hum = 100;
			}
			lcdHandler.printHomeScreen();
			checkRelays();
		}
	}
}
void checkRelays() {
	if (temp + setParameters[2] > setParameters[0]) {
		if (isHeating == 0)
			digitalWrite(RELAYTEMPPIN, HIGH);
		else
			digitalWrite(RELAYTEMPPIN, LOW);
	}
	else if (temp - setParameters[2] < setParameters[0]) {
		if (isHeating == 0)
			digitalWrite(RELAYTEMPPIN, LOW);
		else
			digitalWrite(RELAYTEMPPIN, HIGH);
	}
	if (hum + setParameters[3] > setParameters[1]) {
		if (isHumidification == 0)
			digitalWrite(RELAYHUMPIN, HIGH);
		else
			digitalWrite(RELAYHUMPIN, LOW);
	}
	else if (hum - setParameters[3] < setParameters[1]) {
		if (isHumidification == 0)
			digitalWrite(RELAYHUMPIN, LOW);
		else
			digitalWrite(RELAYHUMPIN, HIGH);
	}
}
void prepareRelays() {
	pinMode(RELAYTEMPPIN, OUTPUT);
	digitalWrite(RELAYTEMPPIN, HIGH);
	pinMode(RELAYHUMPIN, OUTPUT);
	digitalWrite(RELAYHUMPIN, HIGH);
}
void buttonPressed() {
	buttonPressTime = millis();
	switch (pressedKey)
	{
	case(1) : {
		rightKey();
		break;
	}
	case(2) : {
		upKey();
		break;
	}
	case(3) : {
		downKey();
		break;
	}
	case(4) : {
		leftKey();
		break;
	}
	case(5):{
		selectKey();
		break;
	}
	default:
		break;
	}
	if (isMenuOpen) {
		lcdHandler.refrashScreen(menuPossition, setParameters, &menu);
		EEPROM.write(menuPossition, setParameters[menuPossition]);
	}
}
void rightKey() {
	if (!isMenuOpen)
		return;
	if (menuPossition == 4 || menuPossition == 5) // heating and humidity
		switchBooleans();
	else
	setParameters[menuPossition]++;
}
void leftKey() {
	if (!isMenuOpen)
		return;
	if (menuPossition == 4 || menuPossition == 5) // heating and humidity
		switchBooleans();
	else
	setParameters[menuPossition]--;
}
void upKey() {
	if (!isMenuOpen)
		return;
	if (menuPossition > 0) {
		menuPossition--;
	}
}
void downKey() {
	if (!isMenuOpen)
		return;
	if (menuPossition < menu.menuItems -1) {
		menuPossition++;
	}
}
void selectKey() {
	if (!isMenuOpen) {
		isMenuOpen = true;
		menuPossition = 0;
	}
	else {
		isMenuOpen = false;
		lcdHandler.printMessage(menu.getOtherWord(0));
		delay(5000);
		isMenuOpen = false;
		lcdHandler.printHomeScreen();
	}
}
void switchBooleans() {
	if (setParameters[menuPossition] == 1)
		setParameters[menuPossition] = 0;
	else {
		setParameters[menuPossition] = 1;
	}
}