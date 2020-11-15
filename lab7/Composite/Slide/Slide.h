#pragma once
#include "ISlide.h"

class CSlide : public ISlide
{
public:
	CSlide(double m_width, double m_height);
	double GetWidth() const override;
	double GetHeight() const override;

	void Draw(ICanvas& canvas) const override;

	size_t GetShapesCount()const;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);
private:
	double m_width;
	double m_height;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

