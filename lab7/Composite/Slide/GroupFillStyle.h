#pragma once
#include <memory>
#include "IStyle.h"
#include "IStyleEnumerator.h"

typedef std::function<void(std::function<void(IStyle&)>)> FillStyleEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillStyleEnumerator enumerator);
	std::optional<bool> IsEnabled() const;
	void Enable(bool enable);

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);
private:
	FillStyleEnumerator m_enumerator;
};

