#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include "DLList.h"
#pragma once
class Tape
{
private:
	DLList<char> tape;
	DLList<char>::Iterator current;

	void deserializer(const std::string&);
public:
	Tape();
	Tape(const std::string&);
	void show_tape();
	void move_right();
	void move_left();
	void write(const char);
	const char read();
	void saveTape(std::ofstream&);
	void loadTape(std::ifstream&);
};
