#include <iostream>
#include "Tape.h"
#include "DLList.h"

int main()
{
	Tape t1("12");
	t1.move_left();
	t1.move_left();
	
	t1.show_tape();
}
