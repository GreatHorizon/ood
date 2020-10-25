#include "DocumentItem.h"

using namespace std;

CDocumentItem::CDocumentItem(std::shared_ptr<IParagraph> const& paragraph)
	: CConstDocumentItem(paragraph)
{
}

CDocumentItem::CDocumentItem(std::shared_ptr<IImage> const& image)
	: CConstDocumentItem(image)
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}