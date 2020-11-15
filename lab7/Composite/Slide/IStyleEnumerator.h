#pragma once
#include "IOutlineStyle.h"
#include <functional>

class IStyleEnumerator
{
public:
	virtual void EnumerateFillStyles(std::function<void(IStyle&)> callback) = 0;
	virtual void EnumerateOutlineStyles(std::function<void(IOutlineStyle&)> callback) = 0;
};