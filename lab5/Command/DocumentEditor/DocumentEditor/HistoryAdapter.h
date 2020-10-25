#pragma once
#include "ICommandSink.h"
#include "History.h"

class CHistoryAdapter : public ICommandSink
{ 
public:
	void SaveCommand(std::unique_ptr<ICommand>&& command);
	CHistoryAdapter(CHistory& history);
private:
	CHistory& m_history;
};

