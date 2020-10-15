#include "ShapeFactory.h"

using namespace std::placeholders;

CShapeFactory::CShapeFactory()
	: m_actionMap(
		{
			{"triangle", std::bind(&CShapeFactory::MakeTriantle, this, _1)},
			{"rectangle", bind(&CShapeFactory::MakeRectangle, this, _1)},
			{"regularPolygon", bind(&CShapeFactory::MakeRegularPolygon, this, _1)},
			{"ellipse", bind(&CShapeFactory::MakeEllipse, this, _1)},
		})
{
}

inline CPoint ParseCoords(std::string const& xValue, std::string const& yValue)
{
	double x = std::stod(xValue);
	double y = std::stod(yValue);

	return CPoint(x, y);
}

Color CShapeFactory::GetColor(std::string const& color)
{
	if (color == "green")
	{
		return Color::GREEN;
	}
	else if (color == "red")
	{
		return Color::RED;
	}

	else if (color == "blue")
	{
		return Color::BLUE;
	}
	else if (color == "yellow")
	{
		return Color::YELLOW;
	}
	else if (color == "pink")
	{
		return Color::PINK;
	}
	else if (color == "black")
	{
		return Color::BLACK;
	}
	else
	{
		throw std::invalid_argument("Invalid color");
	}
}

std::unique_ptr<CShape> CShapeFactory::MakeTriantle(CShapeFactory::ShapeInfo const& info) const
{
	if (info.size() != 7)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	auto firstVertex = ParseCoords(info[0], info[1]);
	auto secondVertex = ParseCoords(info[2], info[3]);
	auto thirdVertex = ParseCoords(info[4], info[5]);
	auto color = GetColor(info[6]);

	return std::make_unique<CTriangle>(firstVertex, secondVertex, thirdVertex, color);
}

std::unique_ptr<CShape> CShapeFactory::MakeRectangle(CShapeFactory::ShapeInfo const& info) const
{
	if (info.size() != 5)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	auto leftTopPoint = ParseCoords(info[0], info[1]);
	double width = std::stod(info[2]);
	double height = std::stod(info[3]);
	auto color = GetColor(info[4]);

	return std::make_unique<CRectangle>(leftTopPoint, width, height, color);
}

std::unique_ptr<CShape> CShapeFactory::MakeEllipse(CShapeFactory::ShapeInfo const& info) const
{
	if (info.size() != 5)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	auto center = ParseCoords(info[0], info[1]);
	double verticalRadius = std::stod(info[2]);
	double horizontalRadius = std::stod(info[3]);
	auto color = GetColor(info[4]);

	return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, color);
}

std::unique_ptr<CShape> CShapeFactory::MakeRegularPolygon(CShapeFactory::ShapeInfo const& info) const
{
	if (info.size() != 5)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	auto center = ParseCoords(info[0], info[1]);
	double radius = std::stod(info[2]);
	auto vertexCount = std::stoul(info[3]);
	auto color = GetColor(info[4]);

	return std::make_unique<CRegularPolygon>(center, radius, vertexCount, color);
}

CShapeFactory::ShapeInfo CShapeFactory::GetShapeInfo(std::istream& stream)
{
	std::vector<std::string> info;
	std::string parameter;

	while (stream >> parameter)
	{
		info.push_back(parameter);
	}

	return info;
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description)
{
	std::istringstream stream(description);
	std::string command;
	stream >> command;

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.end())
	{
		return it->second(GetShapeInfo(stream));
	}
	else
	{
		throw std::invalid_argument("Invalid command");
	}
}

