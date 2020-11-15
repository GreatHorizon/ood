#pragma once

#include "CInputStreamDecorator.h"
#include "CEncoder.h"

class CInputStreamDectyptor : public CInputStreamDecorator
{
public:
	CInputStreamDectyptor(std::unique_ptr<IInputStream>&& stream, unsigned key)
		: CInputStreamDecorator(std::move(stream))
		, m_decoder(CEncoder(key))
	{
	}

	uint8_t ReadByte() override
	{
		return m_decoder.GetDecryptedByte(m_stream->ReadByte());
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto data = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			try
			{
				data[i] = ReadByte();
			}
			catch (std::ios_base::failure&)
			{
				return i;
			}
		}

		return size;
	}

private:
	CEncoder m_decoder;
};