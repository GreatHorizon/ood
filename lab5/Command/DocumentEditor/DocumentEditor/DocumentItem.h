#pragma once

#include "ConstDocumentItem.h"
#include <memory>


class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IParagraph> const& paragraph);

	CDocumentItem(std::shared_ptr<IImage> const& image);

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};