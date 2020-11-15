#include "Triangle.h"
#include <vector>
#include <algorithm>

CPoint RecalculateVertex(RectD const& newFrame, RectD const& currentFrame, CPoint const& vertex)
{
	auto x = newFrame.m_leftTop.m_x - (currentFrame.m_leftTop.m_x - vertex.GetX()) * newFrame.m_width / currentFrame.m_width;
	auto y = newFrame.m_leftTop.m_y - (currentFrame.m_leftTop.m_y - vertex.GetY()) * newFrame.m_height / currentFrame.m_height;	

	return CPoint(x, y);
}

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

std::optional<RectD> CTriangle::GetFrame() const
{
	auto minX = std::min({ m_vertex1.GetX(), m_vertex2.GetX(), m_vertex3.GetX() });
	auto minY = std::min({ m_vertex1.GetY(), m_vertex2.GetY(), m_vertex3.GetY() });
	auto maxX = std::max({ m_vertex1.GetX(), m_vertex2.GetX(), m_vertex3.GetX() });
	auto maxY = std::max({ m_vertex1.GetY(), m_vertex2.GetY(), m_vertex3.GetY() });

	return RectD(minX, maxY, maxX - minX, maxY - minY);
}

void CTriangle::SetFrame(const RectD& rect)
{
	m_vertex1 = RecalculateVertex(rect, GetFrame().value(), m_vertex1);
	m_vertex2 = RecalculateVertex(rect, GetFrame().value(), m_vertex2);
	m_vertex3 = RecalculateVertex(rect, GetFrame().value(), m_vertex3);
}

CTriangle::CTriangle(CPoint const& firstVertex, CPoint const& secondVertex, CPoint const& thirdVertex)
	: m_vertex1(firstVertex)
	, m_vertex2(secondVertex)
	, m_vertex3(thirdVertex)
{
}

void CTriangle::CurrentShapeDrawing(ICanvas& canvas) const
{
	if (GetFillStyle()->IsEnabled().value())
	{
		canvas.FillPolygon({m_vertex1, m_vertex2, m_vertex3});
	}

	if (GetOutlineStyle()->IsEnabled().value())
	{
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}
}

