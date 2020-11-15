#include <assert.h>
#include <iostream>
#include <functional>

typedef std::function<void()> FlyBehavior;
typedef std::function<void()> QuackBehavior;
typedef std::function<void()> DanceBehavior;

FlyBehavior MakeFlyWithWings()
{	
	int flightCount = 0;
	return [flightCount]() mutable 
	{
		++flightCount;
		std::cout << "Is flying with wings!\n";
		std::cout << "Flight count: " << flightCount << "\n";
	};
}

void FlyNoWay()
{
	std::cout << "Cant fly!\n";
}


void Quack() 
{
	std::cout << "Quack!\n";
}

void Squeak()
{
	std::cout << "Squeak!\n";
}	

void MuteQuack()
{
	std::cout << "Cant quack\n";
}


void DanceMinuet()
{
	std::cout << "Is dancing minuet!\n";
}

void DanceWaltz()
{
	std::cout << "Is dancing waltz\n";
}

void DanceNoWay()
{
	std::cout << "Cant dancing\n";
}


class CDuck
{
public:
	void PerformQuack() const
	{
		if (m_quackBehavior)
		{
			m_quackBehavior();
		}
	}

	void PerformDance() const
	{
		if (m_danceBehavior)
		{
			m_danceBehavior();
		}
	}

	void Swim() const
	{
		std::cout << "Is swimming!\n";
	}

	void PerformFly() const
	{
		if (m_flyBehavior)
		{
			m_flyBehavior();
		}
	}

	void SetFlyBehavior(const FlyBehavior& strategy)
	{
		m_flyBehavior = strategy;
	}

	virtual void Display() const = 0;
	virtual ~CDuck() {}

protected:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;

	CDuck(FlyBehavior flyStrategy , QuackBehavior quackStrategy, DanceBehavior danceStrategy)
		: m_flyBehavior(flyStrategy)
		, m_quackBehavior(quackStrategy)
		, m_danceBehavior(danceStrategy)
	{
		assert(m_flyBehavior);
		assert(m_quackBehavior);
		assert(m_danceBehavior);
	}
};

class CRedHeadDuck : public CDuck
{
public:
	CRedHeadDuck()
		: CDuck(MakeFlyWithWings(), Quack, DanceMinuet)
	{
	}

	void Display() const override
	{
		std::cout << "Im ReadHead duck!\n";
	}
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(MakeFlyWithWings(), Quack, DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "Im Mallard duck!\n";
	}
};

class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck()
		: CDuck(FlyNoWay, MuteQuack, DanceNoWay)
	{
	}

	void Display() const override
	{
		std::cout << "Im Decoy duck!\n";
	}
};

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(FlyNoWay, Squeak, DanceNoWay)
	{
	}

	void Display() const override
	{
		std::cout << "Im Rubber duck!\n";
	}
};

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck& duck)
{
	DrawDuck(duck);
	duck.PerformQuack();
	duck.PerformFly();
	duck.PerformDance();
	std::cout << "\n";
}

int main() 
{
	CRedHeadDuck a;
	CMallardDuck b;
	CDecoyDuck c;
	CRubberDuck d;

	PlayWithDuck(a);
	PlayWithDuck(a);
	PlayWithDuck(b);
	PlayWithDuck(c);
	PlayWithDuck(d);

	a.SetFlyBehavior(FlyNoWay);
	PlayWithDuck(a);

	c.SetFlyBehavior(MakeFlyWithWings());
	PlayWithDuck(c);
	return 0;
}