#pragma once

#include <memory>
#include <optional>
#include "IDrawable.h"
#include "IStyle.h"
#include "IOutlineStyle.h"
#include "CommonTypes.h"

class IGroup;

class IShape : public IDrawable
{
public:
	virtual std::optional<RectD> GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<IOutlineStyle> GetOutlineStyle() const = 0;
	virtual std::shared_ptr<IStyle> GetFillStyle() const = 0;
	virtual std::shared_ptr<IGroup> GetGroup() = 0;

	virtual ~IShape() = default;
};
