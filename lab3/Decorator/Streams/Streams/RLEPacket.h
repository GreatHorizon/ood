#pragma once
#include <cstdint>

struct RLEPacket
{
	uint8_t byteCount = 0;
	uint8_t currentByte = 0;
};