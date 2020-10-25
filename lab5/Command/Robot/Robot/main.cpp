#include "Menu.h"
#include "MenuFP.h"
#include "Commands.h"

using namespace std;

class CMenuHelpCommand : public ICommand
{
public:
	CMenuHelpCommand(const CMenu& menu)
		:m_menu(menu)
	{}

	void Execute() override
	{
		m_menu.ShowInstructions();
	}
private:
	const CMenu& m_menu;
};

class CCreateMacroCommand : public ICommand
{
public:
	CCreateMacroCommand(CMenu& menu)
		: m_menu(menu)
	{
	}

	void Execute() override
	{
		m_menu.CreateMacroCommand();
	}
private:
	CMenu& m_menu;
};

class CExitMenuCommand : public ICommand
{
public:
	CExitMenuCommand(CMenu& menu)
		:m_menu(menu)
	{}

	void Execute() override
	{
		m_menu.Exit();
	}
private:
	CMenu& m_menu;
};

template <typename Commands>
CMenuFP::Command CreateMacroCommand(Commands&& commands)
{
	return [=] {
		for (auto& command : commands)
		{
			command();
		}
	};
}

void TestMenuWithClassicCommandPattern()
{
	Robot robot;
	CMenu menu;
	menu.AddItem("on", "Turns the Robot on",
		std::make_shared<CTurnOnCommand>(robot));
	menu.AddItem("off", "Turns the Robot off",
		make_unique<CTurnOffCommand>(robot));

	menu.AddItem("north", "Makes the Robot walk north",
		std::make_shared<CWalkCommand>(robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south",
		std::make_shared<CWalkCommand>(robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west",
		std::make_shared<CWalkCommand>(robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east",
		std::make_shared<CWalkCommand>(robot, WalkDirection::East));
	menu.AddItem("stop", "Stops the Robot",
		std::make_shared<CStopCommand>(robot));
	menu.AddItem("help", "Show instructions",
		std::make_shared<CMenuHelpCommand>(menu));
	menu.AddItem("exit", "Exit from this menu",
		std::make_shared<CExitMenuCommand>(menu));

	menu.AddItem("begin_macro", "Creatimg macros with several commands",
		std::make_shared<CCreateMacroCommand>(menu));

	menu.Run();
}



void TestMenuWithFunctionalCommandPattern()
{
	Robot robot;
	CMenuFP menu;

	menu.AddItem("on", "Turns the Robot on", [&] {
		robot.TurnOn();
		});

	menu.AddItem("off", "Turns the Robot off",
		bind(&Robot::TurnOff, &robot));

	menu.AddItem("north", "Makes the Robot walk north",
		bind(&Robot::Walk, &robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south",
		bind(&Robot::Walk, &robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west",
		bind(&Robot::Walk, &robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east",
		bind(&Robot::Walk, &robot, WalkDirection::East));

	menu.AddItem("stop", "Stops the Robot",
		bind(&Robot::Stop, &robot));

	menu.AddItem("help", "Show instructions",
		bind(&CMenuFP::ShowInstructions, &menu));

	menu.AddItem("exit", "Exit from this menu",
		bind(&CMenuFP::Exit, &menu));

	menu.AddItem("begin_macro", "Creating your own functions of existing", [&] 
	{
		std::string macrosName, macrosDescription;
		std::cout << "Enter macros name and its description\n";
		std::cin >> macrosName;
		macrosDescription = GetDesctiption(std::cin);
		std::cout << "Enter list of commands\n";
		menu.AddItem(macrosName, macrosDescription, CreateMacroCommand<std::vector<CMenuFP::Command>>
			(menu.GetMacrosFunctions<std::vector<CMenuFP::Command>>()));
	});

	menu.Run();
}



int main()
{
	CMenuFP menu;

	menu.AddItem("c", "Classic command pattern implementation", [&] {
		TestMenuWithClassicCommandPattern();
		menu.ShowInstructions();
		});

	menu.AddItem("f", "Functional command pattern implementation", [&] {
		TestMenuWithFunctionalCommandPattern();
		menu.ShowInstructions();
		});

	menu.AddItem("q", "Exit Program", bind(&CMenuFP::Exit, &menu));
	menu.Run();

	return 0;
}