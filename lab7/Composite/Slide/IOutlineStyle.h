#pragma once
#include "IStyle.h"
#include <optional>

class IOutlineStyle : public IStyle
{
public:
	virtual std::optional<float> GetThickness() const = 0;
	virtual void SetThickness(float thickness) = 0;
};