#pragma once
#include "OStream.h"
#include <vector>

class CMemoryOutputStream : public IOutputStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& memoryStream)
		: m_memoryStream(memoryStream)
	{
	}
	void WriteByte(uint8_t data) override
	{
		m_memoryStream.push_back(data);
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
	std::vector<uint8_t>& m_memoryStream;
	unsigned m_position = 0;

};