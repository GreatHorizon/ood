#pragma once
#include "ICommand.h"
#include <vector>

class CHistory
{
public:
	bool CanUndo()const;
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command);

private:
	const size_t MAX_HISTORY_DEPTH = 10;
	std::vector<std::unique_ptr<ICommand>> m_commands;
	size_t m_nextCommandIndex = 0;
};
