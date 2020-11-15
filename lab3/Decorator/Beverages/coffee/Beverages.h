#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
protected:
	std::string m_description;
};

enum class CoffeeSize
{
	STANDARD, 
	DOUBLE
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(CoffeeSize size = CoffeeSize::STANDARD, const std::string& description = "Coffee")
		: CBeverage(description)
		, m_size(size)
	{
		m_description = size == CoffeeSize::STANDARD ? "Standard size " : "Double size ";
		m_description += description;
	}

	double GetCost() const override
	{
		return 60;
	}

	CoffeeSize GetSize() const
	{
		return m_size;
	}

private:
	CoffeeSize m_size;
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeSize size = CoffeeSize::STANDARD)
		: CCoffee(size, "Cappuccino")
	{}

	double GetCost() const override
	{
		return GetSize() == CoffeeSize::STANDARD ? 80 : 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeSize size = CoffeeSize::STANDARD)
		:CCoffee(size, "Latte")
	{}

	double GetCost() const override
	{
		return GetSize() == CoffeeSize::STANDARD ? 90 : 130;
	}
};

enum class TeaType
{
	BLACK_TEA,
	OOLONG_TEA,
	GREEN_TEA,
	WHITE_TEA
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType type = TeaType::BLACK_TEA, const std::string& description = "Tea")
		: CBeverage(description)
		, m_teaType(type)
	{
		switch (type)
		{
			case TeaType::BLACK_TEA:
				m_description = "Black tea";
				break;
			case TeaType::OOLONG_TEA:
				m_description = "Oolong tea";
				break;
			case TeaType::GREEN_TEA:
				m_description = "Green tea";
				break;
			case TeaType::WHITE_TEA:
				m_description = "White tea";
				break;
		}
	}

	double GetCost() const override
	{
		return 30;
	}

private:
	TeaType m_teaType;
};

enum class MilkshakeSize
{
	SMALL,
	MEDIUM,
	LARGE
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size = MilkshakeSize::SMALL)
		:CBeverage("Milkshake")
		, m_size(size)
	{
		switch (size)
		{
			case MilkshakeSize::SMALL:
				m_description = "Small Milkshake";
				break;
			case MilkshakeSize::MEDIUM:
				m_description = "Medium Milkshake";
				break;
			case MilkshakeSize::LARGE:
				m_description = "Large Milkshake";
				break;
		}
	}

	MilkshakeSize GetSize() const
	{
		return m_size;
	}

	double GetCost() const override
	{
		switch (m_size)
		{
			case MilkshakeSize::SMALL : return 50;
			case MilkshakeSize::MEDIUM : return 60;
			case MilkshakeSize::LARGE : return 80;
			default:
				return 50;
		}
	}

private:
	MilkshakeSize m_size;
};

