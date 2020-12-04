#pragma once
#include <string>
class Transition
{
private:
	std::string current_t;
	char current_cell;
	char change_cell;
	char move_direction;
	std::string next_t;
public:
	Transition();
	Transition(const std::string&, char, char, char, const std::string&);
	const std::string& getCurrentTransition() const;
	const std::string& getNextTransition() const;
	char getCurrentCell() const;
	char getChangeCell() const;
	char getMoveDirection() const;
};

