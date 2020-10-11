#pragma once
#include "IStream.h"

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(std::string fileName)
		: m_stream(fileName, std::ios::binary)
	{
		if (!m_stream.is_open())
		{
			throw std::ios_base::failure("Fail to open file to read\n");
		}
	}

	bool IsEOF() const override
	{
		return m_stream.eof();
	};

	uint8_t ReadByte() override
	{
		char currentByte;
		m_stream.get(currentByte);
		if (IsEOF())
		{
			throw std::ios_base::failure("Fail to read byte from file");
		}

		return (uint8_t)currentByte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto data = static_cast<uint8_t*>(dstBuffer);

		for (std::streamsize i = 0; i < size; i++)
		{
			*data = ReadByte();
			data++;
		}

		return size;
	}
private:
	std::ifstream m_stream;
};