#include "RegularPolygon.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	std::vector<CPoint> vertices;
	double angle = 2.0 * M_PI / m_vertexCount;
	for (size_t i = 0; i < m_vertexCount; i++)
	{
		vertices.push_back(CPoint(m_center.GetX() + m_radius * cos(angle * i), m_center.GetY() + m_radius * sin(angle * i)));
	}

	for (size_t i = 0; i < vertices.size() - 1; i++)
	{
		canvas.DrawLine(vertices[i], vertices[i + 1]);
	}

	canvas.DrawLine(vertices[0], vertices[vertices.size() - 1]);
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

CRegularPolygon::CRegularPolygon(CPoint const& center, double radius, size_t vertexCount, Color color)
	: m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
	, CShape(color)
{
}
