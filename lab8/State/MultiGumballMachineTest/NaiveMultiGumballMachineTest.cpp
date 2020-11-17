#pragma once
#include "stdafx.h"
#include "../MultiGumballMachine/NaiveMultiGumballMachine.h"


std::string GetMachineExpectedOut(std::string const& expectedInvertoryString,
	std::string const& expectedStateString, unsigned expectedQuarterCount)
{
	std::stringstream ss;

	ss << "\nMighty Gumball, Inc.\n" <<
		"C++-enabled Standing Gumball Model #2016\n" <<
		"Inventory: " << expectedInvertoryString << "\n"
		"Quarters: " << expectedQuarterCount << "\n" <<
		"Machine is " << expectedStateString << "\n";

	return ss.str();
}

struct NaiveEmptyGumballMachine
{
	naive::CGumballMachine machine;
	NaiveEmptyGumballMachine()
		: machine(0)
	{
	}
};
BOOST_FIXTURE_TEST_SUITE(empty_gumball_machine_test, NaiveEmptyGumballMachine)
	BOOST_AUTO_TEST_CASE(should_be_in_sold_out_state)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(cant_eject_quarter)
	{
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(cant_turn_ckank_quarter)
	{
		machine.TurnCrank();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(cant_insert_quarter)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("0 gumballs", "sold out", 0));
	}

BOOST_AUTO_TEST_SUITE_END()


struct NaiveGumballMachine
{
	naive::CGumballMachine machine;
	NaiveGumballMachine()
		: machine(5)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(naive_multi_gumball_machine_test, NaiveGumballMachine)
	BOOST_AUTO_TEST_CASE(first_machine_should_be_in_no_quater_state_with_zero_quarters)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for quarter", 0));
	}
	
	BOOST_AUTO_TEST_SUITE(no_quarters_state_test)
		BOOST_AUTO_TEST_CASE(can_turn_crank_in_no_quarters_state)
		{
			machine.TurnCrank();
			BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for quarter", 0));
		}

		BOOST_AUTO_TEST_CASE(can_eject_crank_in_no_quarters_state)
		{
			machine.EjectQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for quarter", 0));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_insert_more_than_1_quarter)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for turn of crank", 1));
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for turn of crank", 2));
	}

	BOOST_AUTO_TEST_CASE(cant_insert_more_than_5_quarters)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for turn of crank", 5));
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for turn of crank", 5));
	}
	
	BOOST_AUTO_TEST_CASE(should_return_all_quarters_when_enject)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
	
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("5 gumballs", "waiting for quarter", 0));
	}
	
	BOOST_AUTO_TEST_CASE(can_return_quarters_in_soldout_state)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
	
		machine.TurnCrank();
		machine.TurnCrank();
		machine.TurnCrank();
	
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		machine.TurnCrank();
	
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("0 gumballs", "sold out", 2));
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("0 gumballs", "sold out", 0));
	}
	
	BOOST_AUTO_TEST_CASE(state_should_became_no_quarters_when_use_last_quarter)
	{
		machine.InsertQuarter();
		machine.TurnCrank();
		BOOST_CHECK_EQUAL(machine.ToString(), GetMachineExpectedOut("4 gumballs", "waiting for quarter", 0));
	}
BOOST_AUTO_TEST_SUITE_END()
