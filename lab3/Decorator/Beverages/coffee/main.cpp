#include "Condiments.h"
#include "Beverages.h"
#include <memory>
#include <iostream>

int main()
{
	std::cout << std::endl;
	{
		// Наливаем чашечку латте
		auto latte = std::make_unique<CLatte>(CoffeeSize::STANDARD);
		// добавляем корицы
		auto cinnamon = std::make_unique<CCinnamon>(move(latte));
		// добавляем пару долек лимона
		auto lemon = std::make_unique<CLemon>(move(cinnamon), 2);
		// добавляем пару кубиков льда
		auto iceCubes = std::make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// добавляем 2 грамма шоколадной крошки
		auto beverage = std::make_unique<CChocolateCrumbs>(move(iceCubes), 2);

		// Выписываем счет покупателю
		std::cout << beverage->GetDescription() << " costs " << beverage->GetCost() << std::endl;
	}

	std::cout << std::endl;
	{
		// Наливаем чашечку черного чая
		auto blackTea = std::make_unique<CTea>();
		// добавляем ореховый ликер
		auto teaWithLiquor = std::make_unique<Liquor>(move(blackTea), LiquorType::Nut);

		// Выписываем счет покупателю
		std::cout << teaWithLiquor->GetDescription() << " costs " << teaWithLiquor->GetCost() << std::endl;
	}


	std::cout << std::endl;
	{
		// Наливаем чашечку капучино
		auto сappuccino = std::make_unique<CCappuccino>(CoffeeSize::DOUBLE);
		// добавляем 5 кусочков шоколада
		auto chocolate = std::make_unique<CChocolate>(move(сappuccino), 5);
		//добавляем сливки
		auto beverage = std::make_unique<CCream>(move(chocolate));

		// Выписываем счет покупателю
		std::cout << beverage->GetDescription() << " costs " << beverage->GetCost() << std::endl;
	}	

	std::cout << std::endl;
	{
		// Наливаем средник милкшейк
		auto milkShake = std::make_unique<CMilkshake>(MilkshakeSize::MEDIUM);

		// Выписываем счет покупателю
		std::cout << milkShake->GetDescription() << " costs " << milkShake->GetCost() << std::endl;
	}

	return 0;
}