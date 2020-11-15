#pragma once
#include "IShape.h"
#include <memory>
#include <limits>
#include "ICanvas.h"
#include "IStyleEnumerator.h"

class IGroup : public IShape
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IGroup() = default;
};