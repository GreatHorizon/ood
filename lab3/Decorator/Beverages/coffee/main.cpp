#include "Condiments.h"
#include "Beverages.h"
#include <memory>
#include <iostream>

int main()
{
	std::cout << std::endl;
	{
		// �������� ������� �����
		auto latte = std::make_unique<CLatte>(CoffeeSize::STANDARD);
		// ��������� ������
		auto cinnamon = std::make_unique<CCinnamon>(move(latte));
		// ��������� ���� ����� ������
		auto lemon = std::make_unique<CLemon>(move(cinnamon), 2);
		// ��������� ���� ������� ����
		auto iceCubes = std::make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// ��������� 2 ������ ���������� ������
		auto beverage = std::make_unique<CChocolateCrumbs>(move(iceCubes), 2);

		// ���������� ���� ����������
		std::cout << beverage->GetDescription() << " costs " << beverage->GetCost() << std::endl;
	}

	std::cout << std::endl;
	{
		// �������� ������� ������� ���
		auto blackTea = std::make_unique<CTea>();
		// ��������� �������� �����
		auto teaWithLiquor = std::make_unique<Liquor>(move(blackTea), LiquorType::Nut);

		// ���������� ���� ����������
		std::cout << teaWithLiquor->GetDescription() << " costs " << teaWithLiquor->GetCost() << std::endl;
	}


	std::cout << std::endl;
	{
		// �������� ������� ��������
		auto �appuccino = std::make_unique<CCappuccino>(CoffeeSize::DOUBLE);
		// ��������� 5 �������� ��������
		auto chocolate = std::make_unique<CChocolate>(move(�appuccino), 5);
		//��������� ������
		auto beverage = std::make_unique<CCream>(move(chocolate));

		// ���������� ���� ����������
		std::cout << beverage->GetDescription() << " costs " << beverage->GetCost() << std::endl;
	}	

	std::cout << std::endl;
	{
		// �������� ������� ��������
		auto milkShake = std::make_unique<CMilkshake>(MilkshakeSize::MEDIUM);

		// ���������� ���� ����������
		std::cout << milkShake->GetDescription() << " costs " << milkShake->GetCost() << std::endl;
	}

	return 0;
}