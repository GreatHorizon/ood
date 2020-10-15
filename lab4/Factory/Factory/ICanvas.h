#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) = 0;
	virtual void DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius) = 0;
	virtual ~ICanvas() = default;
};