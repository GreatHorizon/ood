#pragma once
#include "Point.h"
#include "IDrawable.h"
#include "Shape.h"

class CRectangle : public CShape
{
public:

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;

	std::optional<RectD> GetFrame() const;
	void SetFrame(const RectD& rect);

	CRectangle(const CPoint& leftTop, double width, double height);
protected:
	void CurrentShapeDrawing(ICanvas& canvas) const override;

private:
	CPoint m_leftTopPoint;
	double m_width;
	double m_height;
};

