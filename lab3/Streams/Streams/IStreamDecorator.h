#pragma once

#include "RLEPacket.h"
#include "IStream.h"
#include <memory>

class IStreamDecorator : public IInputStream
{
public:
	bool IsEOF() const
	{
		return m_stream->IsEOF();
	}

protected:
	IStreamDecorator(std::unique_ptr<IInputStream>&& stream)
		: m_stream(std::move(stream))
	{
	}

	std::unique_ptr<IInputStream> m_stream;
};
