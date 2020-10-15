#pragma once
#include "../Factory/ICanvas.h"	

class MockCanvas : public ICanvas
{
public:
	void SetColor(Color color)
	{
		m_color = color;
	};
	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint)
	{
		m_lineCount++;
	}

	void DrawEllipse(CPoint const& center, double horizontalRadius, double verticalRadius)
	{
		m_ellipseCount++;
	}

	unsigned m_ellipseCount = 0;
	unsigned m_lineCount = 0;
private:
	Color m_color;
};