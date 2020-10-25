#include "stdafx.h"
#include "InsertItemCommand.h"
#include "Document.h"
#include "Paragraph.h"

CInsertItemCommand::CInsertItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items,
	std::shared_ptr<CDocumentItem> const& documentItem, boost::optional<size_t> position)
	: m_items(items)
	, m_position(position)
	, m_documentItem(documentItem)
{
	if (m_position.has_value() && m_position.value() >= m_items.size())
	{
		throw std::out_of_range("Position is out of range");
	}
}

void CInsertItemCommand::DoExecute()
{
	if (m_position.has_value())
	{
		m_items.insert(m_items.begin() + m_position.value(), m_documentItem);
	}
	else
	{
		m_items.push_back(m_documentItem);
	}

}

void CInsertItemCommand::DoUnexecute()
{
	if (m_position.has_value())
	{
		m_items.erase(m_items.begin() + m_position.value());
	}
	else
	{
		m_items.pop_back();
	}
}
