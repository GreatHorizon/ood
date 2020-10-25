#include "stdafx.h"
#include "../DocumentEditor/ICommandSink.h"


class CMockHistoryAdapter : public ICommandSink
{
public:
	void SaveCommand(std::unique_ptr<ICommand>&& command)
	{
		m_stream << "Command saved and executed\n";
	}

	CMockHistoryAdapter(std::stringstream& stream)
		: m_stream(stream)
	{
	}


private:
	std::stringstream& m_stream;
};