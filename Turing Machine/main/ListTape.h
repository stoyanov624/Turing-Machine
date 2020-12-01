#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#pragma once
class ListTape
{
private:

	struct Cell {
		char data;
		Cell* left;
		Cell* right;
	};

	Cell* head, *last, *current;
	void push_back(const char element);
	void push_front(const char element);
public:
	ListTape();
	ListTape(const std::string& input);
	void show_tape() const;
	void move_right();
	void move_left();
	void write(const char symbol);
	const char read() const;
};

