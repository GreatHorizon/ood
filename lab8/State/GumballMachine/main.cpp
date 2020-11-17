#include "GumballMachine.h"

int main()
{
	CGumballMachine machine(4);
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.ToString();
	return 0;
}