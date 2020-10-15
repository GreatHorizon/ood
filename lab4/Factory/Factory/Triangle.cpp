#include "Triangle.h"

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

CTriangle::CTriangle(CPoint const& firstVertex, CPoint const& secondVertex, CPoint const& thirdVertex, Color color)
	: m_vertex1(firstVertex)
	, m_vertex2(secondVertex)
	, m_vertex3(thirdVertex)
	, CShape(color)
{
}