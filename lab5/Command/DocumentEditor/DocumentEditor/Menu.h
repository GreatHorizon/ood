#pragma once

class CMenu
{
public:
	CMenu(std::istream& in, std::ostream& out);
	typedef std::function<void(std::istream& args)> Command;
	void AddItem(const std::string& shortcut, const std::string& description, const Command& command);

	void Run();

	void ShowInstructions()const;

	void Exit();

private:
	bool ExecuteCommand(const std::string& command);

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{}

		std::string shortcut;
		std::string description;
		Command command;
	};

	std::vector<Item> m_items;
	bool m_exit = false;

	std::istream& m_in;
	std::ostream& m_out;
};