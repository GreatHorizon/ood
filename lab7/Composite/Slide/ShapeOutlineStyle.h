#pragma once
#include "IStyle.h"
#include "IOutlineStyle.h"

class CShapeOutlineStyle : public IOutlineStyle
{
public:
	CShapeOutlineStyle();
	std::optional<bool> IsEnabled() const;
	void Enable(bool enable);

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);

	std::optional<float> GetThickness() const override;
	void SetThickness(float thickness) override;

private:
	RGBAColor m_color;
	float m_thickness;
	bool m_isEnabled;
};

