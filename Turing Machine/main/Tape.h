#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "DLList.h"
#pragma once
class Tape
{
private:
	DLList<char> tape;
	DLList<char>::Iterator current;
public:
	Tape();
	Tape(const std::string&);
	void show_tape();
	void move_right();
	void move_left();
	void write(const char);
	const char read();
};
