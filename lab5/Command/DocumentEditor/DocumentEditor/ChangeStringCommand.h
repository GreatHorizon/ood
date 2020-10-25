#pragma once
#include "AbstractCommand.h"

class CChangeStringCommand : public CAbstractCommand
{
public:
	CChangeStringCommand(std::string& target, std::string const& newValue);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::string m_newValue;
	std::string& m_target;
};