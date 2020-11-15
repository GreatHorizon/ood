#include "ShapeOutlineStyle.h"

CShapeOutlineStyle::CShapeOutlineStyle()
	: m_color(0xFF0000FF)
	, m_isEnabled(false)
	, m_thickness(2.f)

{
}

std::optional<bool> CShapeOutlineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CShapeOutlineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

std::optional<RGBAColor> CShapeOutlineStyle::GetColor() const
{
	return m_color;
}

void CShapeOutlineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

std::optional<float> CShapeOutlineStyle::GetThickness() const
{
	return m_thickness;
}

void CShapeOutlineStyle::SetThickness(float thickness)
{
	m_thickness = thickness;
}
