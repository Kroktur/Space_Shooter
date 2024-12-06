#include "menuSpaceshooter.h"

int main() {
	Menu* menu = new Menu();
	menu->runMenu();
	delete menu;
	menu = nullptr;
	return EXIT_SUCCESS;
}

