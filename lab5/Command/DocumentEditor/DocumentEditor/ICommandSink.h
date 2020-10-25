#pragma once

#include "ICommand.h"
#include <memory>

class ICommandSink
{
public:
	virtual ~ICommandSink() = default;
	virtual void SaveCommand(std::unique_ptr<ICommand>&& command) = 0;
};