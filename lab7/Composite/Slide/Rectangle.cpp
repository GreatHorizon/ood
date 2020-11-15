#include "Rectangle.h"

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTopPoint.GetX() + this->m_width, m_leftTopPoint.GetY() - this->m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::optional<RectD> CRectangle::GetFrame() const
{
	return RectD(m_leftTopPoint.GetX(), m_leftTopPoint.GetY(), m_width, m_height);
}

void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTopPoint = CPoint(rect.m_leftTop.m_x, rect.m_leftTop.m_y);
	m_height = rect.m_height;
	m_width = rect.m_width;
}

CRectangle::CRectangle(const CPoint& leftTop, double width, double height)
	: m_leftTopPoint(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::CurrentShapeDrawing(ICanvas& canvas) const
{
	if (GetFillStyle()->IsEnabled().value())
	{
		canvas.FillPolygon(
			{
				m_leftTopPoint,
				CPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY()),
				CPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY() - m_height),
				CPoint(m_leftTopPoint.GetX(), m_leftTopPoint.GetY() - m_height)
			});
	}

	if (GetOutlineStyle()->IsEnabled().value())
	{
		canvas.DrawLine(m_leftTopPoint, CPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY()));
		canvas.DrawLine(CPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY()),
			CPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY() - m_height));
		canvas.DrawLine(CPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY() - m_height), 
			CPoint(m_leftTopPoint.GetX(), m_leftTopPoint.GetY() - m_height));
		canvas.DrawLine(CPoint(m_leftTopPoint.GetX(), m_leftTopPoint.GetY() - m_height), m_leftTopPoint);
	}
}
