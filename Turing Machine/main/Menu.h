#pragma once
#include <iostream>
#include <vector>
#include <string>
class Menu
{
private:
	std::vector<std::string> items;
public:
	Menu();
	Menu(const std::vector <std::string>&);
	void printItems() const;
	void addChoice(const std::string&);
	int getIndexChoice() const;
	const std::string& getChoice() const;
	bool hasNoItems() const;
};

