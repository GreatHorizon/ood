#include "stdafx.h"
#include "../Streams/CMemoryInputStream.h"

std::vector<uint8_t> memoryStream;

struct OFileStreamFixture
{
	CMemoryInputStream oStream;

	OFileStreamFixture()
		: oStream(memoryStream)
	{
	}
};

BOOST_AUTO_TEST_SUITE(memory_stream_test)

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_read_eof)
	{
		std::vector<uint8_t> memoryStream = {};
		auto stream = std::make_unique<CMemoryInputStream>(memoryStream);

		BOOST_CHECK_THROW(stream->ReadByte(), std::ios_base::failure);
	}

	BOOST_AUTO_TEST_CASE(can_read_byte)
	{
		std::vector<uint8_t> memoryStream = {'a', 'b', 'c'};
		auto stream = std::make_unique<CMemoryInputStream>(memoryStream);
		
		BOOST_CHECK_EQUAL(stream->ReadByte(), 'a');
		BOOST_CHECK_EQUAL(stream->ReadByte(), 'b');
		BOOST_CHECK_EQUAL(stream->ReadByte(), 'c');
	}

	BOOST_AUTO_TEST_CASE(can_read_block)
	{
		std::vector<uint8_t> memoryStream = { 'a', 'b', 'c' };
		auto stream = std::make_unique<CMemoryInputStream>(memoryStream);
		uint8_t block[2];

		stream->ReadBlock(block, 2);
		BOOST_CHECK_EQUAL(block[0], 'a');
		BOOST_CHECK_EQUAL(block[1], 'b');
	}

	BOOST_AUTO_TEST_CASE(can_read_into_block_more_than_stream_size)
	{
		std::vector<uint8_t> memoryStream = { 'a', 'b', 'c' };
		auto stream = std::make_unique<CMemoryInputStream>(memoryStream);
		uint8_t block[5];

		stream->ReadBlock(block, 5);
		BOOST_CHECK_EQUAL(block[0], 'a');
		BOOST_CHECK_EQUAL(block[1], 'b');
	}

BOOST_AUTO_TEST_SUITE_END();