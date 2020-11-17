#include "stdafx.h"
#include "../GumballMachine/GumballMachine.h"
#include "../GumballMachine/State.h"

std::string GetToStringExpectedOutput(std::string const& expectedInvertoryString,
	std::string const& expectedStateString)
{
	std::stringstream ss;
	
	ss << "\nMighty Gumball, Inc.\n" <<
		"C++-enabled Standing Gumball Model #2016 (with state)\n" <<
		"Inventory: " << expectedInvertoryString << "\n"
		"Machine is " << expectedStateString << "\n";
	
	return ss.str();
}

struct GumballMachine
{
	CGumballMachine machine;
	GumballMachine()
		: machine(5)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(gumball_machine_test, GumballMachine)
	BOOST_AUTO_TEST_CASE(first_machine_should_be_in_no_quater_state)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for quarter"));
	}

	BOOST_AUTO_TEST_SUITE(no_quarter_state_test)
		BOOST_AUTO_TEST_CASE(should_not_change_state_when_trying_to_turn_crank)
		{
			machine.TurnCrank();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for quarter"));
		}

		BOOST_AUTO_TEST_CASE(should_not_change_state_when_trying_to_eject_quarter)
		{
			machine.EjectQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for quarter"));
		}

		BOOST_AUTO_TEST_CASE(should_change_state_to_has_quater)
		{
			machine.InsertQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for turn of crank"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(has_quarter_test)
		BOOST_AUTO_TEST_CASE(should_not_change_state_when_trying_to_insert_quarter)
		{
			machine.InsertQuarter();
			machine.InsertQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for turn of crank"));
		}

		BOOST_AUTO_TEST_CASE(should_change_state_to_has_no_quater_when_eject_quarter)
		{
			machine.InsertQuarter();
			machine.EjectQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for quarter"));
		}

		BOOST_AUTO_TEST_CASE(should_change_state_to_sold_when_turn_crank)
		{
			machine.InsertQuarter();
			machine.TurnCrank();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("4 gumballs", "waiting for quarter"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct SoldOutStateMachine
	{
		CGumballMachine machine;
		SoldOutStateMachine()
			: machine(1)
		{
		}
	};

	BOOST_FIXTURE_TEST_SUITE(sold_out_state_test, SoldOutStateMachine)
		BOOST_AUTO_TEST_CASE(should_state_should_be_sold_out_when_gumballs_ended)
		{
			machine.InsertQuarter();
			machine.TurnCrank();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out"));
		}

		BOOST_AUTO_TEST_CASE(should_not_change_state_when_insert_quarter)
		{
			machine.InsertQuarter();
			machine.TurnCrank();
			machine.InsertQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out"));
		}

		BOOST_AUTO_TEST_CASE(should_not_change_state_when_eject_quarter)
		{
			machine.InsertQuarter();
			machine.TurnCrank();
			machine.EjectQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out"));
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()