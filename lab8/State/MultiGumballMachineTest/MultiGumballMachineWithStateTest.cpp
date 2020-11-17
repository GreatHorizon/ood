#pragma once
#include "stdafx.h"
#include "Utils.h"
#include "../MultiGumballMachine/MultiGumballMachineWithState.h"

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
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(cant_eject_quarter)
	{
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out", 0));
	}
BOOST_AUTO_TEST_SUITE_END()


struct GumballMachineWithState
{
	with_state::CGumballMachine machine;
	GumballMachineWithState()
		: machine(5)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(multi_gumball_machine_with_state_test, GumballMachineWithState)

	BOOST_AUTO_TEST_CASE(first_machine_should_be_in_no_quater_state_with_zero_quarters)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for quarter", 0));
	}

	BOOST_AUTO_TEST_CASE(can_insert_more_than_1_quarter)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for turn of crank", 1));
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for turn of crank", 2));
	}


	BOOST_AUTO_TEST_CASE(cant_insert_more_than_5_quarters)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for turn of crank", 5));
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for turn of crank", 5));
	}

	
	BOOST_AUTO_TEST_CASE(should_return_all_quarters_when_enject)
	{
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();

		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("5 gumballs", "waiting for quarter", 0));
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

		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out", 2));
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("0 gumballs", "sold out", 0));
	}

	BOOST_AUTO_TEST_CASE(state_should_became_no_quarters_when_use_last_quarter)
	{
		machine.InsertQuarter();
		machine.TurnCrank();
		BOOST_CHECK_EQUAL(machine.ToString(), GetToStringExpectedOutput("4 gumballs", "waiting for quarter", 0));
	}

BOOST_AUTO_TEST_SUITE_END()
