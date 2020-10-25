#include "HistoryAdapter.h"

void CHistoryAdapter::SaveCommand(std::unique_ptr<ICommand>&& command)
{
	m_history.AddAndExecuteCommand(std::move(command));
}

CHistoryAdapter::CHistoryAdapter(CHistory& history)
	: m_history(history)
{
}
