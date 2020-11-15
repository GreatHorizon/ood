#include "ShapeFillStyle.h"

CShapeFillStyle::CShapeFillStyle()
    : m_color(0xFFFFFFFF)
    , m_isEnabled(true)
{
}

std::optional<bool> CShapeFillStyle::IsEnabled() const
{
    return m_isEnabled;
}

void CShapeFillStyle::Enable(bool enable)
{
    m_isEnabled = enable;
}

std::optional<RGBAColor> CShapeFillStyle::GetColor() const
{
    return m_color;
}

void CShapeFillStyle::SetColor(RGBAColor color)
{
    m_color = color;
}
