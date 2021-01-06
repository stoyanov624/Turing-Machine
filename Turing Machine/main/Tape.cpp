#include "Tape.h"
Tape::Tape() {
	tape.push_back('_');
	current = tape.begin();
}

Tape::Tape(const std::string& input) {
	initializeTape(input);
}

void Tape::initializeTape(const std::string& input) {
	tape.clear();
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

Tape& Tape::operator=(const Tape& other_tape) {
	if (this != &other_tape) {
		tape.clear();
		tape = other_tape.tape;
		current = tape.begin();

		for (DLList<char>::Iterator it = other_tape.tape.const_begin(); it != other_tape.tape.const_end(); ++it, ++current) {
			if (it == other_tape.current) {
				break;
			}
		}
	}
	
	return *this;
}

void Tape::show_tape() const {
	std::cout << '[';
	for (DLList<char>::Iterator cell = tape.const_begin(); cell != tape.const_end(); ++cell) {
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

void Tape::move_to_beginning() {
	current = tape.begin();
}

void Tape::write(const char symbol) {
	*current = symbol;
}

const char Tape::read() const { 
	return *current;
}

void Tape::saveTape(std::ofstream& out) const {
	for (DLList<char>::Iterator it = tape.const_begin(); it != tape.const_end(); ++it)
	{
		if (it == current) {
			out << "{" << *it << "}";
			continue;
		}
		out << *it;
	}
	out << "\n";
}

void Tape::deserializer(const std::string& input) {
	unsigned length = input.length();
	bool stop_current = false;
	for (unsigned i = 0; i < length; i++) {
		if (input[i] == '{' || input[i] == '}') {
			if (input[i] == '}') {
				stop_current = true;
			}
			continue;
		}

		tape.push_back(input[i]);
		if (!stop_current) {
			move_right();
		}
	}
}

void Tape::loadTape(std::ifstream& in) {
	*this = Tape();
	std::string input;
	std::getline(in, input);
	deserializer(input);

}

