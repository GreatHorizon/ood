#pragma once

#include "IShape.h"
#include "IDrawable.h"

#include <vector>
#include <memory>

class ISlide : public IDrawable
{
public:
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;
	virtual ~ISlide() = default;
};