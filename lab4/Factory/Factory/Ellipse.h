#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse final : public CShape
{
public:
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;
	CPoint GetCenter() const;
	void Draw(ICanvas& canvas) const;
	CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius, Color color);
private:
	double m_horizontalRadius;
	double m_verticalRadius;
	CPoint m_center;
};