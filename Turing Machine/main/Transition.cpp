#include "Transition.h"
Transition::Transition():move_direction(' ') {}

Transition::Transition(const std::string& _current_t, const std::string& _current_cell,
	const std::string& _change_cell, char _move_direction, const std::string& _next_t)
	:current_t(_current_t),current_cell(_current_cell),change_cell(_change_cell), move_direction(_move_direction),
	next_t(_next_t){}

const std::string& Transition::getCurrentTransition() const {
	return current_t;
}

const std::string& Transition::getNextTransition() const {
	return next_t;
}