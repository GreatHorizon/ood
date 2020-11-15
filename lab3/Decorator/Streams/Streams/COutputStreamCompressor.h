#pragma once
#include "OStream.h"
#include "COutputStreamDecorator.h"

class COutputStreamCompressor : public COutputStreamDecorator
{
public:
	~COutputStreamCompressor()
	{
		try
		{
			FlushPacket();
		}
		catch (std::exception e)
		{
		}
	
	}

	COutputStreamCompressor(std::unique_ptr<IOutputStream>&& stream)
		: COutputStreamDecorator(std::move(stream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_packet.byteCount == 0)
		{
			m_packet = { 1, data };
			return;
		}

		if (m_packet.currentByte == data && m_packet.byteCount < MAX_BYTE_AMOUNT)
		{
			m_packet.byteCount++;
			return;
		}

		FlushPacket();
		m_packet = { 1, data };
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto bytes = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(bytes[i]);
		}
	}

private:
	void FlushPacket()
	{
		if (m_packet.byteCount > 0)
		{
			uint8_t packet[] = { m_packet.byteCount, m_packet.currentByte };
			m_stream->WriteBlock(packet, 2);
			m_packet.byteCount = 0;
			m_packet.currentByte = 0;
		}
	}

	RLEPacket m_packet;
	const uint8_t MAX_BYTE_AMOUNT = 255;
};
