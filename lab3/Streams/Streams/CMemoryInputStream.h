#pragma once
#include "IStream.h"
#include <vector>

class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& buffer)
		: m_buffer(buffer)
	{
	}

	bool IsEOF() override
	{
		return m_buffer.size() == m_position;
	};

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Fail to read data. Out of range");
		}

		return m_buffer[m_position++];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (m_buffer.size() - m_position < static_cast<size_t>(size))
		{
			size = m_buffer.size() - m_position;
		}

		auto data = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			data[i] = ReadByte();
		}

		return size;
	}

private:
	std::vector<uint8_t>& m_buffer;
	size_t m_position = 0;
};