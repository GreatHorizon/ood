#include "stdafx.h"
#include "Editor.h"

using namespace std::placeholders;

CEditor::CEditor(std::istream& in, std::ostream& out)
	: m_menu(in, out)
	, m_document(std::make_unique<CDocument>())
	, m_out(out)
{
	m_menu.AddItem("help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](std::istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
	m_menu.AddItem("list", "Show document", std::bind(&CEditor::List, this, _1));
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
	AddMenuItem("insertParagraph", "Inserts paragraph. Args: <position> | end <text>", &CEditor::InsertParagraph);
	AddMenuItem("insertImage", "Inserts image. Args: <position> | end <width> <height> <path>", &CEditor::InsertImage);
	AddMenuItem("replaceText", "Replace text. Args: <position> <text>", &CEditor::ReplaceText);
	AddMenuItem("deleteItem", "Delete item. Args: <position>", &CEditor::DeleteItem);
	AddMenuItem("resizeImage", "Resize image. Args: <position> <width> <height>", &CEditor::ResizeImage);
	AddMenuItem("save", "Save document. Args: <path>", &CEditor::SaveDocument);

	if (!std::filesystem::exists(IMAGES_DIRECTORY))
	{
		std::filesystem::create_directory(IMAGES_DIRECTORY);
	}
}

void CEditor::Start()
{
	m_menu.Run();
}

std::string RemoveLeadingSpaces(std::string const& text)
{
	std::stringstream in(text);
	std::string head;
	std::string tail;

	if (in >> head)
	{
		getline(in, tail);
	}

	return head + tail;
}

void CEditor::ReplaceText(std::istream& in)
{
	size_t position;
	std::string text;

	if (!(in >> position) || !(std::getline(in, text)))
	{
		m_out << "Incorrect arguments\n";
		return;
	}

	text = RemoveLeadingSpaces(text);

	try
	{
		auto paragraph = m_document->GetItem(position);

		if (!paragraph.GetParagraph())
		{
			m_out << "Item in this position is not paragraph\n";
			return;
		}

		paragraph.GetParagraph()->SetText(text);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::DeleteItem(std::istream& in)
{
	size_t position;

	if (!(in >> position))
	{
		m_out << "Incorrect argument\n";
		return;
	}

	m_document->DeleteItem(position);
}

void CEditor::ResizeImage(std::istream& in)
{
	size_t position;
	int width, height;

	if (!(in >> position) || !(in >> width) || !(in >> height))
	{
		m_out << "Incorrect arguments" << "\n";
		return;
	}

	try
	{
		auto image = m_document->GetItem(position);
		if (!image.GetImage())
		{
			m_out << "Item in this position is not image\n";
			return;
		}

		image.GetImage()->Resize(width, height);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}

}

std::string GetTextEncodeHTMLEntities(std::string const& text)
{
	std::string result;

	for (auto &symbol : text)
	{
		if (symbol == '\"')
		{
			result += "&quot;";
		}
		else if (symbol == '`')
		{
			result += "&apos;";
		}
		else if (symbol == '<')
		{
			result += "&lt;";
		}
		else if (symbol == '>')
		{
			result += "&gt;";
		}
		else if (symbol == '&')
		{
			result += "&amp;";
		}
		else
		{
			result += symbol;
		}
	}

	return result;
}

void CEditor::SaveDocument(std::istream& in)
{
	std::string path;
	std::getline(in, path);
	path = RemoveLeadingSpaces(path);

	if (path.back() != '/')
	{
		path += '/';
	}

	if (!std::filesystem::exists(path))
	{
		m_out << "Invalid path\n";
		return;
	}

	if (!std::filesystem::exists(path + IMAGES_DIRECTORY))
	{
		std::filesystem::create_directory(path + IMAGES_DIRECTORY);
	}

	std::ofstream documentFile(path + "index.html");
	documentFile << "<!DOCTYPE html><html><head>" << "<title>"<< GetTextEncodeHTMLEntities(m_document->GetTitle()) << "</title><body>";

	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		auto item = m_document->GetItem(i);
		if (item.GetImage())
		{
			std::filesystem::copy_file(item.GetImage()->GetPath().string(), path + item.GetImage()->GetPath().string());
			documentFile << "<img src="<< item.GetImage()->GetPath()<< "width=" << item.GetImage()->GetWidth() 
				<< " height=" << item.GetImage()->GetHeight() << ">";
		}
		else
		{
			documentFile << "<p>" << GetTextEncodeHTMLEntities(item.GetParagraph()->GetText()) << "</p>";
		}
	}

	documentFile << "<body></html>";
}

void CEditor::AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

boost::optional<size_t> GetPosition(std::istream& in)
{
	std::string posLine;
	size_t position;
	in >> posLine;

	if (posLine != "end")
	{
		std::istringstream stream(posLine);
		stream >> position;
		return position;
	}

	return boost::none;
}

void CEditor::InsertImage(std::istream& in)
{
	auto position = GetPosition(in);
	int height = 0;
	int width = 0;
	std::string path;

	if (!(in >> height) || !(in >> width) || !(in >> path))
	{
		m_out << "Incorrect arguments\n";
		return;
	}

	try
	{
		m_document->InsertImage(Path(path), width, height, position);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::InsertParagraph(std::istream& in)
{
	auto position = GetPosition(in);
	std::string text;
	std::getline(in, text);
	text = RemoveLeadingSpaces(text);

	try
	{
		m_document->InsertParagraph(text, position);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::SetTitle(std::istream& in)
{
	std::string title;

	if (!std::getline(in, title))
	{
		m_out << "Command arguments should not be empty\n";
	}
	
	title = RemoveLeadingSpaces(title);
	m_document->SetTitle(title);
}

void CEditor::List(std::istream&)
{
	if (m_document->GetTitle() != "")
	{
		m_out << "Title: " << m_document->GetTitle() << "\n";
	}

	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		auto item = m_document->GetItem(i);
		if (item.GetParagraph())
		{
			m_out << i << ". Paragraph: " << item.GetParagraph()->GetText() << "\n";
		}

		if (item.GetImage())
		{
			m_out << i << ". Image: " << item.GetImage()->GetWidth()
				<< " " << item.GetImage()->GetHeight() << " " << item.GetImage()->GetPath() << "\n";
		}
	}
}

void CEditor::Undo(std::istream&)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		m_out << "Can't undo" << "\n";
	}
}

void CEditor::Redo(std::istream&)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		m_out << "Can't redo\n";
	}
}