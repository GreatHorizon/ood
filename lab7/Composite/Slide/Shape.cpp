#include "Shape.h"

CShape::CShape()
    : m_fillStyle(std::make_shared<CShapeFillStyle>())
    , m_outlineStyle(std::make_shared<CShapeOutlineStyle>())
{
}

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle() const
{
    return m_outlineStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle() const
{
    return m_fillStyle;
}

std::shared_ptr<IGroup> CShape::GetGroup()
{
    return nullptr;
}

void CShape::Draw(ICanvas& canvas) const
{
    if (GetFillStyle()->IsEnabled().value())
    {
        canvas.SetFillColor(m_fillStyle->GetColor().value());
    }

    if (GetOutlineStyle()->IsEnabled().value())
    {
        canvas.SetOutlineColor(m_outlineStyle->GetColor().value());
        canvas.SetLineWidth(m_outlineStyle->GetThickness().value());
    }

    CurrentShapeDrawing(canvas);
}
