#include "Transition.h"
Transition::Transition() :move_direction(' '), current_cell(' '), change_cell(' ') {}

Transition::Transition(const std::string& _current_t, char _current_cell,
	char _change_cell, char _move_direction)
	:current_t(_current_t),current_cell(_current_cell),change_cell(_change_cell), move_direction(_move_direction) {}

const std::string& Transition::getCurrentTransition() const {
	return current_t;
}

bool Transition::operator==(const Transition& other) const {
	return current_t == other.current_t
		&& current_cell == other.current_cell
		&& change_cell == other.change_cell
		&& move_direction == other.move_direction;
}

bool Transition::operator!=(const Transition& other) const {
	return !(this == &other);
}

char Transition::getCurrentCell() const {
	return current_cell;
}

char Transition::getChangeCell() const {
	return change_cell;
}

char Transition::getMoveDirection() const {
	return move_direction;
}