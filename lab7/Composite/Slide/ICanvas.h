#pragma once
#include "CommonTypes.h"
#include "Point.h"
#include <vector>

class ICanvas
{
public:
	virtual void SetFillColor(RGBAColor color) = 0;
	virtual void SetOutlineColor(RGBAColor color) = 0;
	virtual void SetLineWidth(float thickness) = 0;
	virtual void FillPolygon(const std::vector<CPoint>& vertices) = 0;
	virtual void FillEllipse(const CPoint& center, double horizontalRadius, double verticalRadius) = 0;

	virtual void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) = 0;
	virtual void DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius) = 0;
	virtual ~ICanvas() = default;
};