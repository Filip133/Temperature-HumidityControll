#include "Menu.h"
char* Menu::getItem(int poss)
{
	return items[poss];
}

char * Menu::getOtherWord(int poss)
{
	return otherWords[poss];
}
