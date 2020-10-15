#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>

class CRectangle final : public CShape
{
public:
	void Draw(ICanvas& canvas) const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;

	CRectangle(const CPoint& leftTop, double width, double height, Color color);
private:
	CPoint m_leftTopPoint;
	double m_width;
	double m_height;
};