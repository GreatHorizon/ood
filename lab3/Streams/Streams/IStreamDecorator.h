#pragma once

#include "RLEPacket.h"
#include "IStream.h"
#include <memory>

class IStreamDecorator : public IInputStream
{

public:
	IStreamDecorator(std::unique_ptr<IInputStream>&& stream)
		: m_stream(std::move(stream))
	{
	}

	bool IsEOF() const
	{
		return m_stream->IsEOF();
	}

	uint8_t ReadByte() 
	{
		return m_stream->ReadByte();
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)
	{
		return m_stream->ReadBlock(dstBuffer, size);
	}

protected:
	std::unique_ptr<IInputStream> m_stream;
};
