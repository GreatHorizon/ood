#pragma once
#include "COStreamDecorator.h"
#include "CEncoder.h"

class COutputStreamEncryptor : public COStreamDecorator
{
public:
	COutputStreamEncryptor(std::unique_ptr<IOutputStream>&& stream, unsigned key)
		: COStreamDecorator(std::move(stream))
		, m_encoder(CEncoder(key))
	{
	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(m_encoder.GetEncryptedByte(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(data[i]);
		}
	}

private:
	CEncoder m_encoder;
};
