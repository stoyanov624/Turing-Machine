#include "Menu.h"
#include <conio.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

Menu::Menu() :items() {}

Menu::Menu(const std::vector<std::string>& _items) {
	items = _items;
}

void Menu::addChoice(const std::string& choice) {
	items.push_back(choice);
}

void Menu::printItems() const {
	int start = 0;
	unsigned items_count = items.size();
	
	for (unsigned i = 0; i < items_count; i++) {
		gotoXY(2, i);  std::cout << items[i];
	}
	std::cout << std::endl;
}

int Menu::getIndexChoice() const {
	bool running = true;
	unsigned menu_item = 0;
	unsigned x = 0;
	int key = 0;
	unsigned items_count = items.size();
	gotoXY(0, 0); std::cout << "->";
	while (running) {
		printItems();

		key = _getch();
		if (key == 80 && x != items_count - 1) //down button pressed
		{
			gotoXY(0, x); std::cout << "  ";
			x++;
			gotoXY(0, x); std::cout << "->";
			menu_item++;
			continue;
		}

		if (key == 72 && x != 0) //up button pressed
		{
			gotoXY(0, x); std::cout << "  ";
			x--;
			gotoXY(0, x); std::cout << "->";
			menu_item--;
			continue;
		}

		if (key == 13) {
			system("cls");
			return menu_item;
		}
	}
}

const std::string& Menu::getChoice() const {
	return items[getIndexChoice()];
}

bool Menu::hasNoItems() const {
	return items.empty();
}