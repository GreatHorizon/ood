#include "Ellipse.h"


CPoint CEllipse::GetCenter() const
{
	return m_center;
}

double CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

double CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}

CEllipse::CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

std::optional<RectD> CEllipse::GetFrame() const
{
	return RectD(m_center.GetX() - m_horizontalRadius, m_center.GetY() + m_verticalRadius, m_horizontalRadius * 2, m_verticalRadius * 2);
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_horizontalRadius = rect.m_width / 2;
	m_verticalRadius = rect.m_height / 2;
	m_center = CPoint(rect.m_leftTop.m_x + m_horizontalRadius, rect.m_leftTop.m_y - m_verticalRadius);
}

void CEllipse::CurrentShapeDrawing(ICanvas& canvas) const
{
	if (GetFillStyle()->IsEnabled().value())
	{
		canvas.FillEllipse(m_center, m_horizontalRadius, m_verticalRadius);
	}

	if (GetOutlineStyle()->IsEnabled().value())
	{
		canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
	}
}
