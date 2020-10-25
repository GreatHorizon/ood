#pragma once

#include "IDocument.h"
#include "History.h"
#include <memory>


class CDocument : public IDocument
{
public:

	void SetTitle(const std::string& title) override;

	std::string GetTitle() const override;

	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
	boost::optional<size_t> position = boost::none);
	
	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images 
	// под автоматически сгенерированным именем
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		boost::optional<size_t> position = boost::none);

	// Возвращает количество элементов в документе
	size_t GetItemsCount() const;

	// Доступ к элементам изображения
	CConstDocumentItem GetItem(size_t index) const;
	CDocumentItem GetItem(size_t index);

	// Удаляет элемент из документа
	void DeleteItem(size_t index);

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	std::string m_title;
	std::vector<std::shared_ptr<CDocumentItem>> m_items;
	CHistory m_history;
};