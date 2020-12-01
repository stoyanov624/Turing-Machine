#include "Tape.h"

Tape::Tape() {
	head = new Cell{ '_',nullptr,nullptr };
	current = head;
	last = head;
}

Tape::Tape(const std::string& input) : Tape() {

	unsigned input_len = input.length();
	for (unsigned i = 0; i < input_len; i++) {
		push_back(input[i]);
	}

	if (input_len > 0) {
		current = head->right;
	}
}

void Tape::push_back(const char element) {
	Cell* temp = new Cell{ element,last,nullptr };
	last->right = temp;
	last = temp;
	current = temp;
}

void Tape::push_front(const char element) {
	Cell* temp = new Cell{ element,nullptr,head };
	head->left = temp;
	head = temp;
	current = temp;
}

void Tape::show_tape() const {
	Cell* crr = head;
	std::cout << '[';
	while (crr != nullptr) {
		if (crr == current) {
			std::cout << '{' << crr->data << '}';
		}
		else {
			std::cout << crr->data;
		}

		if (crr->right != nullptr) {
			std::cout << ' ';
		}
		crr = crr->right;
	}
	std::cout << ']';
	std::cout << std::endl;
}

void Tape::move_right() {
	if (current->right == nullptr) {
		push_back('_');
		return;
	}
	current = current->right;
}

void Tape::move_left() {
	if (current->left == nullptr) {
		push_front('_');
		return;
	}
	current = current->left;
}

void Tape::write(const char symbol) {
	current->data = symbol;
}

const char Tape::read() const {
	return current->data;
}

