#pragma once
#include "IStream.h"
#include "CInputStreamDecorator.h"

class CInputStreamDecompressor : public CInputStreamDecorator
{
public:
	CInputStreamDecompressor(std::unique_ptr<IInputStream>&& stream)
		: CInputStreamDecorator(std::move(stream))
	{
	}



	uint8_t ReadByte() override
	{
		if (m_packet.byteCount == 0)
		{
			m_packet.byteCount = m_stream->ReadByte();
			m_packet.currentByte = m_stream->ReadByte();
		}

		m_packet.byteCount--;
		return m_packet.currentByte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto data = static_cast<uint8_t*>(dstBuffer);

		for (std::streamsize i = 0; i < size; i++)
		{
			data[i] = ReadByte();
		}

		return size;
	}

private:
	RLEPacket m_packet;
};