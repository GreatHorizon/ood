#include "Menu.h"
#include "MultiGumballMachineWithState.h"
#include "NaiveMultiGumballMachine.h"

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType& machine)
{
	CMenu menu;
	menu.AddItem("help", "Shows instructions", [&] {
		menu.ShowInstructions();
	});

	menu.AddItem("exit", "Exit", [&] {
		menu.Exit();
	});

	menu.AddItem("insertQuarter", "Inserting one quarter", [&] {
		machine.InsertQuarter();
	});
	menu.AddItem("turnCrank", "Turning crank to get gumball", [&] {
		machine.TurnCrank();
	});
	menu.AddItem("ejectQuarter", "Return back your quarter", [&] {
		machine.EjectQuarter();
	});
	menu.AddItem("toString", "Shows info about machine", [&] {
		std::cout << machine.ToString();
	});

	menu.AddItem("refill", "Refill machine by gumballs", [&] {
		size_t count;
		std::cout << "How many balls?\n>";
		std::cin >> count;

		machine.Refill(count);
	});

	menu.Run();
}

void TestNaiveGumballMachine()
{
	naive::CGumballMachine m(5);
	TestGumballMachine(m);
}

void TestGumballMachineWithState()
{
	with_state::CGumballMachine m(5);
	TestGumballMachine(m);
}

int main()
{
	std::cout << "\n-----------------\n";
	std::cout << "Naive gumball machine";
	std::cout << "\n-----------------\n";
	TestNaiveGumballMachine();

	std::cout << "\n-----------------\n";
	std::cout << "Gumbal machine with state";
	std::cout << "\n-----------------\n";
	TestGumballMachineWithState();

	return 0;
}