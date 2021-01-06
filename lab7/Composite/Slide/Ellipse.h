#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;
	CPoint GetCenter() const;
	CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius);
	std::optional<RectD> GetFrame() const;
	void SetFrame(const RectD& rect);
protected:
	void CurrentShapeDrawing(ICanvas& canvas) const override;
private:
	double m_horizontalRadius;
	double m_verticalRadius;
	CPoint m_center;
};

