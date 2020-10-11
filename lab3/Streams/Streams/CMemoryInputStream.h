#pragma once
#include "IStream.h"
#include <vector>

class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& memoryStream)
		: m_memoryStream(memoryStream)
	{
	}

	bool IsEOF() const override
	{
		return m_memoryStream.size() == m_position;
	};

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Fail to read data. Out of range");
		}

		return m_memoryStream[m_position++];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (m_memoryStream.size() - m_position < size)
		{
			size = m_memoryStream.size() - m_position;
		}

		auto data = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			data[i] = ReadByte();
		}

		return size;
	}

private:
	std::vector<uint8_t>& m_memoryStream;
	unsigned m_position = 0;
};