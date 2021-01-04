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
	Tape& operator=(const Tape& other);
	void show_tape() const;
	void move_right();
	void move_left();
	void move_to_beginning();
	void write(const char);
	const char read() const;
	void saveTape(std::ofstream&) const;
	void loadTape(std::ifstream&);
};
