#pragma once
#pragma once

#include "RLEPacket.h"
#include "IStream.h"
#include <memory>

class CInputStreamDecorator : public IInputStream
{
public:
	bool IsEOF()
	{
		return m_stream->IsEOF();
	}

protected:
	CInputStreamDecorator(std::unique_ptr<IInputStream>&& stream)
		: m_stream(std::move(stream))
	{
	}

	std::unique_ptr<IInputStream> m_stream;
};
