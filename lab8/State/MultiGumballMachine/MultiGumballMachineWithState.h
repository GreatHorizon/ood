#pragma once
#include <string>
#include <iostream>
#include "boost/format.hpp"

namespace with_state
{
	class IGumballMachine
	{
	public:
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallCount() const = 0;
		virtual unsigned GetQuarterCount() const = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;
		virtual void AddQuarter() = 0;
		virtual void ReturnQuarters() = 0;

		virtual ~IGumballMachine() = default;
	};

	class IState
	{
	public:
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual std::string ToString() const = 0;
		virtual ~IState() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball\n";
		}

		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank\n";
		}

		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball\n";
		}

		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				m_gumballMachine.GetQuarterCount() == 0 ?
					m_gumballMachine.SetNoQuarterState() : m_gumballMachine.SetHasQuarterState();
			}
		}

		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}

		void EjectQuarter() override
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
			{
				m_gumballMachine.ReturnQuarters();
			}
			else
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
		}

		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}

		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}

		std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			if (m_gumballMachine.GetQuarterCount() < 5)
			{
				m_gumballMachine.AddQuarter();
				std::cout << "You inserted a quarter\n";
			}
			else
			{
				std::cout << "You can't insert another quarter\n";
			}
		}

		void EjectQuarter() override
		{
			m_gumballMachine.ReturnQuarters();
			m_gumballMachine.SetNoQuarterState();
		}

		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}

		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}

		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}

		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}

		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}

		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}

		std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_ballCount(numBalls)
		{
			if (m_ballCount > 0)
			{
				m_state = &m_noQuarterState;
			}
		}

		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}

		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}

		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}

		std::string ToString() const
		{
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quarters: %3%
Machine is %4%
)");
			return (fmt % m_ballCount % (m_ballCount != 1 ? "s" : "") % m_quarterCount % m_state->ToString()).str();
		}
	private:
		unsigned GetBallCount() const override
		{
			return m_ballCount;
		}

		unsigned GetQuarterCount() const override
		{
			return m_quarterCount;
		}

		virtual void ReleaseBall() override
		{
			if (m_ballCount != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_ballCount;
				--m_quarterCount;
			}
		}

		void ReturnQuarters() override
		{
			if (m_quarterCount != 0)
			{
				std::cout << m_quarterCount << "quarter" << (m_quarterCount > 1 ? "s" : "") << " returned\n";
				m_quarterCount = 0;
			}
		}

		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}

		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}

		void SetSoldState() override
		{
			m_state = &m_soldState;
		}

		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}

		void AddQuarter() override
		{
			m_quarterCount++;
		}
	private:
		unsigned m_ballCount = 0;
		unsigned m_quarterCount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
	};
}