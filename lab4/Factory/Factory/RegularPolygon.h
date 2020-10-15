#pragma once
#include "Shape.h"
#include "Point.h"

class CRegularPolygon final : public CShape
{
public:
	void Draw(ICanvas& canvas) const;
	size_t GetVertexCount() const;
	CPoint GetCenter() const;
	double GetRadius() const;
	CRegularPolygon(CPoint const& center, double radius, size_t vertexCount, Color color);
private:
	CPoint m_center;
	double m_radius;
	size_t m_vertexCount;
};