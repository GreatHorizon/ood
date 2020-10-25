#include "stdafx.h"
#include "../DocumentEditor/Menu.h"

struct MenuFixture
{
	std::stringstream in;
	std::stringstream out;
	CMenu menu;

	MenuFixture()
		: menu(in, out)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(MenuTest, MenuFixture)
	BOOST_AUTO_TEST_CASE(can_add_command_and_show_in_instructions_list)
	{
		menu.AddItem("command1", "some description for command1", [this](std::istream&) {out << "command1 is executing\n"; });
		menu.ShowInstructions();

		BOOST_CHECK_EQUAL(out.str(), "Commands list:\n  command1: some description for command1\n");
	}

	BOOST_AUTO_TEST_CASE(can_execute_command)
	{
		menu.AddItem("command1", "some description for command1", [this](std::istream&) {out << "command1 is executing\n"; });
		in << "command1";
		menu.Run();
		BOOST_CHECK_EQUAL(out.str(), "Commands list:\n  command1: some description for command1\n>command1 is executing\n>");
	}


	BOOST_AUTO_TEST_CASE(cant_execute_unknown_command)
	{
		in << "command1";
		menu.Run();
		BOOST_CHECK_EQUAL(out.str(), "Commands list:\n>Unknown command\n>");
	}

	BOOST_AUTO_TEST_CASE(can_execute_exit_command)
	{
		menu.AddItem("exit", "command to exit menu", [this](std::istream&) {out << "exit command is executing\n"; menu.Exit();});
		in << "exit";
		menu.Run();
		BOOST_CHECK_EQUAL(out.str(), "Commands list:\n  exit: command to exit menu\n>exit command is executing\n");
	}

BOOST_AUTO_TEST_SUITE_END()