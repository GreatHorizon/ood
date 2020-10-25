#include "DeleteItemCommand.h"
#include "stdafx.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& m_items, size_t position)
	: m_items(m_items)
	, m_position(position)
{
	if (m_position >= m_items.size())
	{
		throw std::out_of_range("Position is out of range");
	}

	m_documentItem = m_items.at(m_position);
}

void CDeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin() + m_position, m_documentItem);
}
