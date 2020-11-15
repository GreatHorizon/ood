#pragma once
#include "IStyle.h"

class CShapeFillStyle : public IStyle
{
public:
	CShapeFillStyle();
	std::optional<bool> IsEnabled() const;
	void Enable(bool enable);

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);
private:
	RGBAColor m_color;
	bool m_isEnabled;
};

