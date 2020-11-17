#pragma once
#include "stdafx.h"
#include "../MultiGumballMachine/MultiGumballMachineWithState.h"

std::string GetGumballMachineExpectedOut(std::string const& expectedInvertoryString,
	std::string const& expectedStateString, unsigned expectedQuarterCount)
{
	std::stringstream ss;

	ss << "\nMighty Gumball, Inc.\n" <<
		"C++-enabled Standing Gumball Model #2016 (with state)\n" <<
		"Inventory: " << expectedInvertoryString << "\n"
		"Quarters: " << expectedQuarterCount << "\n" <<
		"Machine is " << expectedStateString << "\n";

	return ss.str();
}
struct EmptyGumballMachineWithState
{
	with_state::CGumballMachine machine;
	EmptyGumballMachineWithState()
		: machine(0)
	{
	}
};
BOOST_FIXTURE_TEST_SUITE(empty_gumball_machine_with_state_test, EmptyGumballMachineWithState)
	BOOST_AUTO_TEST_CASE(should_be_in_sold_out_state)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(cant_eject_quarter)
	{
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("0 gumballs", "sold out", 0));
	}
	
	BOOST_AUTO_TEST_CASE(can_refill)
	{
		machine.Refill(5);
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("5 gumballs", "waiting for quarter", 0));
	}

BOOST_AUTO_TEST_SUITE_END()

struct GumballMachineWithState
{
	with_state::CGumballMachine machine;
	GumballMachineWithState()
		: machine(3)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(multi_gumball_machine_with_state_test, GumballMachineWithState)

	BOOST_AUTO_TEST_CASE(first_machine_should_be_in_no_quater_state_with_zero_quarters)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("3 gumballs", "waiting for quarter", 0));
	}

	BOOST_AUTO_TEST_CASE(can_insert_more_than_1_quarter)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("3 gumballs", "waiting for turn of crank", 1));
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("3 gumballs", "waiting for turn of crank", 2));
	}


	BOOST_AUTO_TEST_CASE(cant_insert_more_than_5_quarters)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("3 gumballs", "waiting for turn of crank", 5));
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("3 gumballs", "waiting for turn of crank", 5));
	}

	
	BOOST_AUTO_TEST_CASE(should_return_all_quarters_when_enject)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("3 gumballs", "waiting for quarter", 0));
	}

	BOOST_AUTO_TEST_CASE(can_return_quarters_in_soldout_state)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		machine.TurnCrank();
		machine.TurnCrank();

		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();

		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("0 gumballs", "sold out", 3));
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(state_should_became_no_quarters_when_use_last_quarter)
	{
		machine.InsertQuarter();
		machine.TurnCrank();
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("2 gumballs", "waiting for quarter", 0));
	}

	BOOST_AUTO_TEST_CASE(quarters_should_not_be_lost_when_refill)
	{
		machine.InsertQuarter();
		machine.Refill(10);

		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("10 gumballs", "waiting for turn of crank", 1));
	}


	BOOST_AUTO_TEST_CASE(in_sold_out_state_with_quarter_should_change_state_to_has_quarter_after_refill)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		machine.TurnCrank();
		machine.TurnCrank();
		machine.TurnCrank();

		machine.Refill(10);

		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("10 gumballs", "waiting for turn of crank", 1));
	}

	BOOST_AUTO_TEST_CASE(in_sold_out_state_with_no_quarter_should_change_state_to_no_quarter_after_refill)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		machine.TurnCrank();
		machine.TurnCrank();
		machine.TurnCrank();

		machine.Refill(10);

		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("10 gumballs", "waiting for quarter", 0));
	}

	BOOST_AUTO_TEST_CASE(can_refil_in_no_quarter_state)
	{
		machine.Refill(15);
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("15 gumballs", "waiting for quarter", 0));
	}

	BOOST_AUTO_TEST_CASE(can_refil_to_0_balls_state_should_became_sold_out)
	{
		machine.Refill(0);
		BOOST_CHECK_EQUAL(machine.ToString(), GetGumballMachineExpectedOut("0 gumballs", "sold out", 0));
	}

BOOST_AUTO_TEST_SUITE_END()
