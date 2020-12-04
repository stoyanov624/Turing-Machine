#include <iostream>
#include "Tape.h"
#include "DLList.h"
#include <map>
#include "Transition.h"


void go_to_next_transition(Transition*& current, std::map<std::string, std::vector<std::pair<Transition*, char>>> graph) {

	for(auto t : graph[current->getCurrentTransition()]) {
		if (current->getCurrentCell() == t.second) {
			current = t.first;
			return;
		}
	}
}

int main()
{
	Transition t1("t1", '1', '0', 'L', "t2");
	Transition t2("t2", '0', '0', 'R', "t3");
	Transition t3("t3", '0', '0', 'R', "t2");
	Transition halt("halt", ' ', ' ', ' ', "");

	std::map<std::string, std::vector<std::pair<Transition*, char>>> graph;
	Transition* current = &t1;
	graph["t1"].push_back(std::make_pair(&t2, '0'));
	graph["t1"].push_back(std::make_pair(&t3, '1'));
	graph["t2"].push_back(std::make_pair(&t3, '1'));
	graph["t3"].push_back(std::make_pair(&halt, '0'));
	
	go_to_next_transition(current, graph);
	go_to_next_transition(current, graph);

	std::cout << current->getCurrentTransition();

	
}
