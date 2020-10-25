#include "Paragraph.h"
#include "ICommandSink.h"
#include "ChangeStringCommand.h"

std::string CParagraph::GetText() const
{
    return m_text;
}

void CParagraph::SetText(const std::string& text)
{
    auto command = std::make_unique<CChangeStringCommand>(m_text, text);
    m_historyAdapter->SaveCommand(std::move(command));
}

CParagraph::CParagraph(std::unique_ptr<ICommandSink>&& history, std::string const& text)
    : m_historyAdapter(std::move(history))
    , m_text(text)
{
}

