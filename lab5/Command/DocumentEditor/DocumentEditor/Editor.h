#pragma once
#include "Menu.h"
#include "Document.h"

class CEditor
{
public:
	CEditor(std::istream& in, std::ostream& out);

	void Start();
private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::* MenuHandler)(std::istream& in);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);

	void InsertParagraph(std::istream& in);
	void InsertImage(std::istream& in);
	void ReplaceText(std::istream& in);
	void DeleteItem(std::istream& in);
	void ResizeImage(std::istream& in);
	void SaveDocument(std::istream& in);
	void SetTitle(std::istream& in);
	
	void List(std::istream&);
	void Undo(std::istream&);
	void Redo(std::istream&);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
	std::ostream& m_out;
};

