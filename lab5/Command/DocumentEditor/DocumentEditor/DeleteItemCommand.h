#pragma once
#include "AbstractCommand.h"
#include <boost\optional\optional.hpp>
#include "Document.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& m_items, size_t position);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	size_t m_position;
	std::shared_ptr<CDocumentItem> m_documentItem;
};
