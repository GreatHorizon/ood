#pragma once

#include <memory>
#include <functional>

#include "IStyle.h"
#include "IStyleEnumerator.h"
#include "IOutlineStyle.h"

typedef std::function<void(std::function<void(IOutlineStyle&)>)> OutlineStyleEnumerator;

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(OutlineStyleEnumerator function);
	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	std::optional<float> GetThickness() const override;
	void SetThickness(float thickness) override;
private:
	OutlineStyleEnumerator m_enumerator;
};

