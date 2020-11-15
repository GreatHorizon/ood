#include <functional>
#include <iostream>

typedef std::function<void()> FlyBehavior;

FlyBehavior FlyWithWings()
{
	int flightCount = 0;
	return [flightCount]() mutable
	{
		++flightCount;
		std::cout << "Im flying with wings!\n";
		std::cout << "Flight count: " << flightCount << "\n";
	};
}

void FlyNoWay()
{
	std::cout << "Cant fly!\n";
}