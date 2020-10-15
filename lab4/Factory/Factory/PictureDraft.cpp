#include "PictureDraft.h"
#include <stdexcept>

bool CPictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

CPictureDraft::ConstIterator CPictureDraft::begin() const
{
	return m_shapes.begin();
}

CPictureDraft::ConstIterator CPictureDraft::end() const
{
	return m_shapes.end();
}

void CPictureDraft::AddShape(std::unique_ptr<CShape>&& shape)
{
	m_shapes.push_back(move(shape));
}

size_t CPictureDraft::GetShapesCount() const
{
	return m_shapes.size();
}

CShape& CPictureDraft::GetShape(size_t index) const
{
	if (m_shapes.size() <= index)
	{
		throw std::out_of_range("Index is out of range");
	}

	return *m_shapes[index].get();
}

CPictureDraft::CPictureDraft()
{
}