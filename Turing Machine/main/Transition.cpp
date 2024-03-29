#include "Transition.h"
Transition::Transition() {}

Transition::Transition(const std::string& _current_t, const std::string& _current_cell,
	const std::string& _change_cell, const std::string& _move_direction)
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

const std::string& Transition::getCurrentCell() const {
	return current_cell;
}

const std::string& Transition::getChangeCell() const {
	return change_cell;
}

const std::string& Transition::getMoveDirection() const {
	return move_direction;
}

void Transition::setCurrentCell(const std::string& _current_cell ) {
	current_cell = _current_cell;
}

void Transition::setChangeCell(const std::string& _change_cell) {
	change_cell = _change_cell;
}

void Transition::setMoveDirection(const std::string& _move_direction) {
	move_direction = _move_direction;
}

void Transition::setCurrentTransition(const std::string& _current_transition) {
	current_t = _current_transition;
}

bool Transition::isValid() const {
	return current_cell.length() == change_cell.length()
		&& current_cell.length() == move_direction.length()
		&& change_cell.length() == move_direction.length();
}

bool Transition::canWorkWith(const Transition& other) const {
	return isValid() && other.isValid() &&
		current_cell.length() == other.current_cell.length()
		&& change_cell.length() == other.change_cell.length()
		&& move_direction.length() == other.move_direction.length();
}

bool Transition::isGoodForSingleTape() const {
	return current_cell.length() == 1
			&& change_cell.length() == 1 
			&& move_direction.length() == 1;
}