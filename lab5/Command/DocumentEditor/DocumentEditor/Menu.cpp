#include "stdafx.h"
#include "Menu.h"

CMenu::CMenu(std::istream& in, std::ostream& out)
	: m_in(in)
	, m_out(out)
{
}

void CMenu::AddItem(const std::string& shortcut, const std::string& description, const Command& command)
{
	m_items.emplace_back(shortcut, description, command);
}

void CMenu::Run()
{
	ShowInstructions();

	std::string command;

	while ((m_out << ">")
		&& getline(m_in, command)
		&& ExecuteCommand(command))
	{
	}
}

void CMenu::ShowInstructions() const
{
	m_out << "Commands list:\n";
	for (auto& item : m_items)
	{
		m_out << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const std::string& command)
{
	std::istringstream iss(command);
	std::string name;
	iss >> name;

	m_exit = false;
	auto it = boost::find_if(m_items, [&](const Item& item) {
		return item.shortcut == name;
		});
	if (it != m_items.end())
	{
		it->command(iss);
	}
	else
	{
		m_out << "Unknown command\n";
	}
	return !m_exit;
}