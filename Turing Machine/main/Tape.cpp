#include "Tape.h"

Tape::Tape() {
	tape.push_back(' ');
	current = tape.begin();
}

Tape::Tape(const std::string& input) {
	unsigned length = input.length();
	if (length == 0) {
		tape.push_back(' ');
	}
	else {
		for (unsigned i = 0; i < length; i++) {
			tape.push_back(input[i]);
		}
	}
	current = tape.begin();
}


void Tape::show_tape() {
	std::cout << '[';
	for (DLList<char>::Iterator cell = tape.begin(); cell != tape.end(); ++cell) {
		if (cell == current) {
			std::cout << "{" << *cell << "} ";
		}
		else {
			std::cout << *cell << " ";
		}
	}
	std::cout << "\b]\n";
}

void Tape::move_right() {
	if (current == nullptr) {
		tape.push_back('_');
	}
	++current;
}

void Tape::move_left() {
	if (current == tape.begin()) {
		tape.push_front('_');
	}
	--current;
}

void Tape::write(const char symbol) {
	*current = symbol;
}

const char Tape::read() { 
	return *current;
}

