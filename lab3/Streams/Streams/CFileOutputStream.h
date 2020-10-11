#pragma once
#include "OStream.h"

class CFileOutputStream : public IOutputStream
{
public:
	CFileOutputStream(std::string fileName)
		: m_stream(fileName, std::ios::binary)
	{
	}

	void WriteByte(uint8_t data) override
	{
		m_stream.put(data);

		if (m_stream.fail() || m_stream.bad())
		{
			throw std::ios_base::failure("Failed to write data into file\n");
		}
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
	std::ofstream m_stream;
};