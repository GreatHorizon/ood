#include "Rectangle.h"

void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint rightTopPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY());
	CPoint leftBottomPoint(m_leftTopPoint.GetX(), m_leftTopPoint.GetY() - m_height);

	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTopPoint, leftBottomPoint);
	canvas.DrawLine(leftBottomPoint, GetRightBottom());
	canvas.DrawLine(GetRightBottom(), rightTopPoint);
	canvas.DrawLine(rightTopPoint, m_leftTopPoint);

}

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

CRectangle::CRectangle(const CPoint& leftTop, double width, double height, Color color)
	: m_leftTopPoint(leftTop)
	, m_width(width)
	, m_height(height)
	, CShape(color)
{
}
