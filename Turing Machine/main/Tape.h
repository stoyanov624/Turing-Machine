#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#pragma once

class Tape
{
private:
	std::vector<char> left;
	std::vector<char> right;
	char current;

public:
	Tape();
	Tape(const std::string& input);
	void move_right();
	void move_left();
	void write(char symbol);
	const char read() const;
	void showTape();
};

