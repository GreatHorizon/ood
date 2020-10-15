#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>

class CTriangle final : public CShape
{
public:
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	void Draw(ICanvas& canvas) const override;
	CTriangle(CPoint const& firstVertex, CPoint const& secondVertex, CPoint const& thirdVertex, Color color);

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};