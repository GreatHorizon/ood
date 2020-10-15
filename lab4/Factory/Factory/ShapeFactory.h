#pragma once
#include "IShapeFactory.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include <sstream>
#include <functional>
#include <map>

class CShapeFactory : public IShapeFactory
{
public:
	typedef std::vector<std::string> ShapeInfo;
	std::unique_ptr<CShape> CreateShape(std::string const& description);
	CShapeFactory();
private:
	static ShapeInfo GetShapeInfo(std::istream& stream);
	static Color GetColor(std::string const& color);
	std::unique_ptr<CShape> MakeTriantle(CShapeFactory::ShapeInfo const& info) const;
	std::unique_ptr<CShape> MakeRectangle(CShapeFactory::ShapeInfo const& info) const;
	std::unique_ptr<CShape> MakeEllipse(CShapeFactory::ShapeInfo const& info) const;
	std::unique_ptr<CShape> MakeRegularPolygon(CShapeFactory::ShapeInfo const& info) const;
private:
	typedef std::function<std::unique_ptr<CShape>(ShapeInfo stream)> Handler;
	typedef std::map<std::string, Handler> ActionMap;
	const ActionMap m_actionMap;
};