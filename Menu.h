#pragma once
class Menu
{
public:
	char* getItem(int poss);
	char* getOtherWord(int poss);
	const static int menuItems = 6;
private:
	char* items[menuItems]{ "Temperatura","Vlaga","Tolerancija temp","Tolerancija vlag",
		"Grij 1,Hladj 0","Ovlaz 1,Odvlaz 0" };
	char* otherWords[]{ "Spremljeno!" };
};