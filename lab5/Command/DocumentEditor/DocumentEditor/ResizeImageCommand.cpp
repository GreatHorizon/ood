#include "ResizeImageCommand.h"
#include "Image.h"

CResizeImageCommand::CResizeImageCommand(int& width, int& height, int newWidth, int newHeight)
	: m_width(width)
	, m_height(height)
	, m_newHeight(newHeight)
	, m_newWidth(newWidth)
{
	if (!IsCorrectSizeParameter(newWidth) || !IsCorrectSizeParameter(newHeight))
	{
		throw std::invalid_argument("Incorrect image size");
	}
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_height, m_newHeight);
	std::swap(m_width, m_newWidth);
}

void CResizeImageCommand::DoUnexecute()
{
	std::swap(m_height, m_newHeight);
	std::swap(m_width, m_newWidth);
}
