#pragma once
#include <string>
class Transition
{
private:
	std::string current_t;
	char current_cell;
	char change_cell;
	char move_direction;
public:
	Transition();
	Transition(const std::string&, char, char, char);
	bool operator==(const Transition&) const;
	bool operator!=(const Transition&) const;
	const std::string& getCurrentTransition() const;
	char getCurrentCell() const;
	char getChangeCell() const;
	char getMoveDirection() const;
};

