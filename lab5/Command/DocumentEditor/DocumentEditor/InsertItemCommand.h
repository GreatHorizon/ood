#pragma once
#include "AbstractCommand.h"
#include <boost\optional\optional.hpp>
#include "Document.h"

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items,
		std::shared_ptr<CDocumentItem> const& documentItem, boost::optional<size_t> position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	boost::optional<size_t> m_position;
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_documentItem;
};