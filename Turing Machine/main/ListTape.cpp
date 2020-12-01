#include "ListTape.h"

ListTape::ListTape() {
	head = new Cell {'_',nullptr,nullptr};
	current = head;
	last = head;
}

ListTape::ListTape(const std::string& input) : ListTape() {
	
	unsigned input_len = input.length();
	for (unsigned i = 0; i < input_len; i++) {
		push_back(input[i]);
	}

	if (input_len > 0) {
		current = head->right;
	}
}

void ListTape::push_back(const char element) {
	Cell* temp = new Cell{ element,last,nullptr };
	last->right = temp;
	last = temp;
	current = temp;
}

void ListTape::push_front(const char element) {
	Cell* temp = new Cell{ element,nullptr,head };
	head->left = temp;
	head = temp;
	current = temp;
}

void ListTape::show_tape() const {
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

void ListTape::move_right() {
	if (current->right == nullptr) {
		push_back('_');
		return;
	}
	current = current->right;
}

void ListTape::move_left() {
	if (current->left == nullptr) {
		push_front('_');
		return;
	}
	current = current->left;
}

void ListTape::write(const char symbol) {
	current->data = symbol;
}

const char ListTape::read() const {
	return current->data;
}

