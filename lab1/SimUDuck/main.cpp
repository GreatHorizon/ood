#include <memory>
#include <iostream>
#include <assert.h>

class IFlyBehavior
{
public:
	virtual void Fly() = 0;
	virtual ~IFlyBehavior() {};
};

class CFlyNoWay : public IFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "I cant fly\n";
	}
};

class CFlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "Im flying with wings!\n";
		m_flightCount++;
		std::cout << "Flights number: " << m_flightCount << "\n";
	}
private:
	int m_flightCount = 0;
};


class IQuackBehavior
{
public:
	virtual void Quack() const = 0;
	virtual ~IQuackBehavior() {};
};

class CQuack : public IQuackBehavior
{
public:
	void Quack() const override
	{
		std::cout << "Quack!\n";
	}
};

class CSqueak : public IQuackBehavior
{
public:
	void Quack() const override
	{
		std::cout << "Squeak!\n";
	}
};

class CMuteQuack : public IQuackBehavior
{
public:
	void Quack() const override
	{
		std::cout << "Cant quack\n";
	}
};

class IDanceBehavior
{
public:
	virtual void Dance() const = 0;
	virtual ~IDanceBehavior() {}
};

class CDanceMinuet : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "Is dancing minuet!\n";
	}
};

class CDanceWaltz : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "Is dancing waltz\n";
	}
};

class CDanceNoWay : public IDanceBehavior
{
public:
	void Dance() const override	
	{
		std::cout << "Cant dancing\n";
	}
};


class CDuck
{
public:
	void PerformQuack() const
	{
		m_quackBehavior->Quack();
	}

	void PerformFly() const 
	{
		m_flyBehavior->Fly();
	}

	void PerformDance() const 
	{
		m_danceBehavior->Dance();
	}

	void Swim() const 
	{
		std::cout << "Im swimming\n";
	}

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~CDuck() {}

protected:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;

	CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_flyBehavior(std::move(flyBehavior))
		, m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(std::move(danceBehavior))
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
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuack>(), std::make_unique<CDanceMinuet>())
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
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuack>(), std::make_unique<CDanceWaltz>())
	{
	}

	void Display() const override
	{
		std::cout << "Im Mallard duck!\n";
	}
};

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(std::make_unique<CFlyNoWay>(), std::make_unique<CSqueak>(), std::make_unique<CDanceNoWay>())
	{
	}

	void Display() const override
	{
		std::cout << "Im Rubber duck!\n";
	}
};

class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck()
		: CDuck(std::make_unique<CFlyNoWay>(), std::make_unique<CMuteQuack>(), std::make_unique<CDanceNoWay>())
	{
	}

	void Display() const override
	{
		std::cout << "Im Decoy duck!\n";
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

	a.SetFlyBehavior(std::make_unique<CFlyNoWay>());
	PlayWithDuck(a);

	c.SetFlyBehavior(std::make_unique<CFlyWithWings>());
	PlayWithDuck(c);

	return 0;
}