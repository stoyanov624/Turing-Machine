#include "Tape.h"

Tape::Tape() {
	current = '_';
}

Tape::Tape(const std::string& input) {
	unsigned input_lenght = input.length();

	for (unsigned i = 0; i < input_lenght; i++) {
		right.push_back(input[input_lenght - i - 1]);
	}

	current = right.back();
	right.pop_back();
}

void Tape::move_right() {
	if (right.empty()) {
		right.push_back('_');
	}
	left.push_back(current);
	current = right.back();
	right.pop_back();
}

void Tape::move_left() {
	if (left.empty()) {
		left.push_back('_');
	}
	right.push_back(current);
	current = left.back();
	left.pop_back();
}

void Tape::write(char symbol) {
	current = symbol;
}

const char Tape::read() const {
	return current;
}

void Tape::showTape()  {

	std::cout << "[";
	for (auto element : left) {
		std::cout << element << " ";
	}

	std::cout << "{";
	std::cout << current;
	std::cout << "}";

	for (std::vector<char>::reverse_iterator it = right.rbegin(); it != right.rend(); it++) {
		std::cout << *it << " ";
	}

	std::cout << "]\n";
}