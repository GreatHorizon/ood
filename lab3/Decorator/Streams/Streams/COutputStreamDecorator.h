#pragma once
#include "RLEPacket.h"
#include "OStream.h"
#include <vector>
#include <memory>

class COutputStreamDecorator : public IOutputStream
{
protected:
	COutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream)
		: m_stream(std::move(stream))
	{
	}

	std::unique_ptr<IOutputStream> m_stream;
};



