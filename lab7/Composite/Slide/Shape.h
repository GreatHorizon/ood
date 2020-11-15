#pragma once
#include "IShape.h"
#include "ShapeOutlineStyle.h"
#include "ShapeFillStyle.h"
#include <functional>

typedef std::function<void(ICanvas& canvas, const IShape& shape)> DrawingStrategy;

class CShape : public IShape
{
public:
	CShape();
	std::shared_ptr<IOutlineStyle> GetOutlineStyle() const;
	std::shared_ptr<IStyle> GetFillStyle() const;
	std::shared_ptr<IGroup> GetGroup();
	void Draw(ICanvas& canvas) const override;
	virtual void CurrentShapeDrawing(ICanvas& canvas) const = 0;

private:
	std::shared_ptr<CShapeFillStyle> m_fillStyle;
	std::shared_ptr<CShapeOutlineStyle> m_outlineStyle;
};