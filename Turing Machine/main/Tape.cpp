#include "Tape.h"

Tape::Tape() {
	tape.push_back('_');
	current = tape.begin();
}

Tape::Tape(const std::string& input) {
	unsigned length = input.length();
	if (length == 0) {
		tape.push_back('_');
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
	if (current.isFirst() && current.isLast() && *current == '_') {
		return;
	}

	if (current.isLast()) {
		tape.push_back('_');
	}

	if (current.isFirst() && *current == '_') {
		++current;
		tape.pop_front();
		return;
	}

	++current;
}

void Tape::move_left() {
	if (current.isFirst() && current.isLast() && *current == '_') {
		return;
	}

	if (current.isFirst()) {
		tape.push_front('_');
	}

	if (current.isLast() && *current == '_') {
		--current;
		tape.pop_back();
		return;
	}
	--current;
}

void Tape::write(const char symbol) {
	*current = symbol;
}

const char Tape::read() { 
	return *current;
}

