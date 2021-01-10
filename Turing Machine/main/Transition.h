#pragma once
#include <string>
class Transition
{
private:
	std::string current_t;
	std::string current_cell;
	std::string change_cell;
	std::string move_direction;
public:
	Transition();
	Transition(const std::string&, const std::string&, const std::string&, const std::string&);
	bool operator==(const Transition&) const;
	bool operator!=(const Transition&) const;

	const std::string& getCurrentTransition() const;
	const std::string& getCurrentCell() const;
	const std::string& getChangeCell() const;
	const std::string& getMoveDirection() const;

	void setCurrentTransition(const std::string&);
	void setCurrentCell(const std::string&);
	void setChangeCell(const std::string&);
	void setMoveDirection(const std::string&);

	bool isValid() const;
	bool canWorkWith(const Transition&) const;
	bool isGoodForSingleTape() const;
};

