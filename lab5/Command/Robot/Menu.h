#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <boost/range/algorithm/find_if.hpp>
#include "ICommand.h"
#include "Commands.h"

inline std::string GetDesctiption(std::istream& in)
{
	std::string head;
	std::string tail;

	if (in >> head)
	{
		getline(in, tail);
	}

	return head + tail;
}

class CMenu
{
public:

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, std::shared_ptr<ICommand> const& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{}

		std::string shortcut;
		std::string description;
		std::shared_ptr<ICommand> command;
	};

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		std::shared_ptr<ICommand> command)
	{
		m_items.emplace_back(shortcut, description, std::move(command));
	}

	void CreateMacroCommand()
	{
		std::cout << "Enter macros name an its description\n";
		std::string macrosName, macrosDescription;
		std::cin >> macrosName;
		macrosDescription = GetDesctiption(std::cin);

		AddItem(macrosName, macrosDescription, GetMacrosWithCommands());
	}

	void Run()
	{
		ShowInstructions();

		std::string command;
		while ((std::cout << ">")
			&& (std::cin >> command)
			&& ExecuteCommand(command))
		{
		}
	}

	void ShowInstructions()const
	{
		std::cout << "Commands list:\n";
		for (auto& item : m_items)
		{
			std::cout << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

	std::vector<Item> const& GetCommands() const
	{
		return m_items;
	}

private:
	bool ExecuteCommand(const std::string& command)
	{
		m_exit = false;

		auto it = boost::find_if(m_items, [&](const Item& item) {
			return item.shortcut == command;
			});
		if (it != m_items.end())
		{
			it->command->Execute();
		}
		else
		{
			std::cout << "Unknown command\n";
		}

		return !m_exit;
	}

	std::shared_ptr<ICommand> GetMacrosWithCommands() const
	{
		std::string commandName;
		auto macros = std::make_shared<CMacroCommand>();
		auto existingCommands = GetCommands();
		
		std::cout << "Enter list of commands\n";
		std::cout << "  > ";
		std::cin >> commandName;

		while (commandName != "end_macro")
		{
			auto command = std::find_if(existingCommands.begin(), existingCommands.end(), [commandName](CMenu::Item const& item)
				{
					return item.shortcut == commandName;
				});

			if (command != existingCommands.end())
			{
				macros->AddCommand(command->command);
			}
			else
			{
				std::cout << "Unknown command\n";
			}

			std::cout << "  > ";
			std::cin >> commandName;
		}

		return macros;
	}

	std::vector<Item> m_items;
	bool m_exit = false;
};

