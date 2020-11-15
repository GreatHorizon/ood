#include "Group.h"
#include "GroupFillStyle.h"
#include "GroupOutlineStyle.h"

#include <algorithm>
#include <stdexcept>

CGroup::CGroup()
{
	auto outlineStyleEnumerator = [&] (std::function<void(IOutlineStyle&)> callback) {
		for (auto& shape : m_shapes)
		{
			callback(*shape->GetOutlineStyle());
		}
	};

	auto fillStyleEnumerator = [&](std::function<void(IStyle&)> callback) {
		for (auto& shape : m_shapes)
		{
			callback(*shape->GetFillStyle());
		}
	};

	m_outlineStyle = std::make_shared<CGroupOutlineStyle>(outlineStyleEnumerator);
	m_fillStyle = std::make_shared<CGroupFillStyle>(fillStyleEnumerator);
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroup::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(shape);
	}
	else if (position >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + position, shape);
	}
}

std::shared_ptr<IShape> CGroup::GetShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_shapes.at(index);
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

std::optional<RectD> CGroup::GetFrame() const
{
	bool isInitialized = false;
	double minX, maxX, minY, maxY;

	if (m_shapes.empty())
	{
		return std::nullopt;
	}

	for (auto& shape : m_shapes)
	{
		if (shape->GetFrame().has_value())
		{
			auto shapeFrame = shape->GetFrame().value();

			if (!isInitialized)
			{
				minX = shapeFrame.m_leftTop.m_x;
				maxY = shapeFrame.m_leftTop.m_y;
				maxX = shapeFrame.m_leftTop.m_x + shapeFrame.m_width;
				minY = shapeFrame.m_leftTop.m_y - shapeFrame.m_height;
				isInitialized = true;
			}
			else
			{
				minX = std::min({ minX, shapeFrame.m_leftTop.m_x });
				maxY = std::max({ maxY, shapeFrame.m_leftTop.m_y });
				maxX = std::max({ maxX, shapeFrame.m_leftTop.m_x + shapeFrame.m_width });
				minY = std::min({ minY, shapeFrame.m_leftTop.m_y - shapeFrame.m_height });
			}
		}
	}

	if (!isInitialized)
	{
		return std::nullopt;
	}

	return RectD(minX, maxY, maxX - minX, maxY - minY);
}

void CGroup::SetFrame(const RectD& rect)
{
	if (!GetFrame().has_value())
	{
		return;
	}

	auto currentFrame = GetFrame().value();
	double leftTopX, leftTopY, height, width;

	for (auto& shape : m_shapes)
	{
		if (shape->GetFrame().has_value())
		{
			auto shapeFrame = shape->GetFrame().value();

			leftTopX = rect.m_leftTop.m_x - (currentFrame.m_leftTop.m_x - shapeFrame.m_leftTop.m_x) * rect.m_width / currentFrame.m_width;
			leftTopY = rect.m_leftTop.m_y - (currentFrame.m_leftTop.m_y - shapeFrame.m_leftTop.m_y) * rect.m_height / currentFrame.m_height;
			height = shapeFrame.m_height * rect.m_height / currentFrame.m_height;
			width = shapeFrame.m_width * rect.m_width / currentFrame.m_width;

			shape->SetFrame(RectD(leftTopX, leftTopY, width, height));
		}
	}
}

std::shared_ptr<IOutlineStyle> CGroup::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CGroup::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroup> CGroup::GetGroup()
{
	return shared_from_this();
}


void CGroup::Draw(ICanvas& canvas) const
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
