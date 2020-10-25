#pragma once

#include "ConstDocumentItem.h"
#include <memory>


class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IParagraph> const& paragraph);

	CDocumentItem(std::shared_ptr<IImage> const& image);

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();
};