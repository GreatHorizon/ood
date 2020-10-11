#pragma once
#include "vector"
#include <algorithm>
#include <random>
#include <numeric>

class CEncoder
{
public:
	CEncoder(unsigned key)
		: m_encryptedValues(std::vector<uint8_t>(256))
		, m_decryptedValues(std::vector<uint8_t>(256))
		, m_key(key)
	{
		GenerateTables(key);
	}

	uint8_t GetEncryptedByte(uint8_t byte) const
	{
		return m_encryptedValues[byte];
	}

	uint8_t GetDecryptedByte(uint8_t byte) const
	{
		return m_decryptedValues[byte];
	}

private:
	void GenerateTables(unsigned key)
	{
		std::iota(m_encryptedValues.begin(), m_encryptedValues.end(), 0);
		std::shuffle(m_encryptedValues.begin(), m_encryptedValues.end(), std::mt19937(key));
		for (size_t i = 0; i < m_encryptedValues.size(); i++)
		{
			m_decryptedValues[m_encryptedValues[i]] = static_cast<uint8_t>(i);
		}
	}

	std::vector<uint8_t> m_encryptedValues;
	std::vector<uint8_t> m_decryptedValues;
	unsigned m_key;
};