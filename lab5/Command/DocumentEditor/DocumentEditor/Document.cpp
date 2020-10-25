#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "Paragraph.h"
#include "Image.h"
#include "DocumentItem.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "HistoryAdapter.h"

using namespace std;

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	auto historyAdapter = std::make_unique<CHistoryAdapter>(m_history);
	auto paragraph = std::make_shared<CParagraph>(std::move(historyAdapter), text);
	auto documentItem = std::make_shared<CDocumentItem>(paragraph);
	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, documentItem, position));
	return paragraph;

}

std::shared_ptr<IImage> CDocument::InsertImage(const Path& path, int width, int height, boost::optional<size_t> position)
{
	auto historyAdapter = std::make_unique<CHistoryAdapter>(m_history);
	auto image = std::make_shared<CImage>(std::move(historyAdapter), path, height, width);
	auto documentItem = std::make_shared<CDocumentItem>(image);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(m_items, documentItem, position));
	return image;
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Invalid item index");
	}

	return *m_items.at(index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Invalid item index");
	}

	return *m_items.at(index);
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}