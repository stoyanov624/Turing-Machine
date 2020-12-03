#pragma once
#include <string>
class Transition
{
private:
	std::string current_t;
	std::string current_cell;
	std::string change_cell;
	char move_direction;
	std::string next_t;
public:
	Transition();
	Transition(const std::string&, const std::string&, const std::string&, char, const std::string&);
	const std::string& getCurrentTransition() const;
	const std::string& getNextTransition() const;
};

