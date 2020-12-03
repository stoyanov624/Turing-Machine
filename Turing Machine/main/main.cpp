#include <iostream>
#include "Tape.h"
#include "DLList.h"
#include <map>
#include "Transition.h"


int main()
{
	Transition t1("t1", "1", "0", 'R', "t2");
	Transition t2("t2", "0", "0", 'R', "t3");
	Transition t3("t3", "0", "0", 'R', "t2");

	
	std::map <std::string, std::vector<Transition>> mapping;
	mapping["t1"].push_back(t2);
	mapping["t1"].push_back(t3);
	mapping["t2"].push_back(t1);
	
	for (std::map <std::string, std::vector<Transition>>::const_iterator it = mapping.begin(); it != mapping.end(); ++it) {
		std::cout << it->first << "-> ";
		for (auto t : it->second)
		{
			std::cout << t1.getCurrentTransition() << " ";
		}
		std::cout << std::endl;
	}
}
