#pragma once
#include "IGroup.h"
#include "GroupFillStyle.h"
#include "GroupOutlineStyle.h"
#include <vector>
#include <memory>

class CGroup : public IGroup, public std::enable_shared_from_this<IGroup>
{
public:
	CGroup();
	size_t GetShapesCount() const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	std::optional<RectD> GetFrame() const;
	void SetFrame(const RectD& rect);

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() const override;

	std::shared_ptr<IGroup> GetGroup() override;

	void Draw(ICanvas& canvas) const override;
private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;

	std::vector<std::shared_ptr<IShape>> m_shapes;
};