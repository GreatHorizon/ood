#pragma once
#include "IParagraph.h"
#include "ICommandSink.h"
#include "HistoryAdapter.h"

class CParagraph : public IParagraph
{
public:
	std::string GetText() const;
	void SetText(const std::string& text);
	CParagraph(std::unique_ptr<ICommandSink>&& history, std::string const& text);
private:
	std::unique_ptr<ICommandSink> m_historyAdapter;
	std::string m_text;
};

