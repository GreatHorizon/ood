#pragma once
#include "Color.h"
#include "Canvas.h"

class CShape
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

	virtual Color GetColor() const
	{
		return m_color;
	}

	virtual ~CShape() = default;

	CShape(Color color)
		: m_color(color)
	{
	}
private:
	Color m_color;
};