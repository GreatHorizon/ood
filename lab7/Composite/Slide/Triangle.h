#pragma once
#include "Shape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	std::optional<RectD> GetFrame() const;
	void SetFrame(const RectD& rect);
	CTriangle(CPoint const& firstVertex, CPoint const& secondVertex, CPoint const& thirdVertex);
	void CurrentShapeDrawing(ICanvas& canvas) const override;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};

