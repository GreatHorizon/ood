#include "stdafx.h"
#include "History.h"
#include "ICommand.h"

bool CHistory::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool CHistory::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute(); // может выбросить исключение
		--m_nextCommandIndex;
	}
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute(); // может выбросить исключение
		++m_nextCommandIndex;
	}
}

void CHistory::AddAndExecuteCommand(std::unique_ptr<ICommand>&& command)
{
	if (m_nextCommandIndex < m_commands.size()) // Не происходит расширения истории команд
	{
		command->Execute();	// может бросить исключение
		++m_nextCommandIndex;
		m_commands.resize(m_nextCommandIndex);	// исключение выброшено не будет, т.к. размер <= текущему
		m_commands.back() = move(command);
	}
	else // будет происходить расширение истории команд
	{
		assert(m_nextCommandIndex == m_commands.size()); 
		m_commands.emplace_back(nullptr);

		try
		{
			command->Execute(); // может выбросить исключение
			m_commands.back() = move(command); // не бросает исключений
			++m_nextCommandIndex; // теперь можно обновить индекс следующей команды
		}
		catch (...)
		{
			m_commands.pop_back(); // не бросает исключений
			throw;
		}

		if (m_commands.size() > MAX_HISTORY_DEPTH)
		{
			m_commands.erase(m_commands.begin());
			--m_nextCommandIndex;
		}
	}
}