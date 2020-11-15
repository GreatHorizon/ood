#include "stdafx.h"
#include "../Streams/CFileInputStream.h"

struct IFileStreamFixture
{
	CFileInputStream iStream;

	IFileStreamFixture()
		: iStream("input.dat")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(input_file_stream_test, IFileStreamFixture)
	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_cant_open_file)
	{
		BOOST_CHECK_THROW(CFileInputStream("nonexistent_file_name.dat"),
			std::ios_base::failure);
	}

	BOOST_AUTO_TEST_CASE(can_read_byte)
	{
		BOOST_CHECK_EQUAL(iStream.ReadByte(), ';');
		BOOST_CHECK_EQUAL(iStream.ReadByte(), 'A');
		BOOST_CHECK_EQUAL(iStream.ReadByte(), '^');
	}

	BOOST_AUTO_TEST_CASE(can_read_block)
	{
		char block[3];
		iStream.ReadBlock(block, 3);
		BOOST_CHECK_EQUAL(block[0], ';');
		BOOST_CHECK_EQUAL(block[1], 'A');
		BOOST_CHECK_EQUAL(block[2], '^');
	}

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_eof)
	{
		char block[3];
		iStream.ReadBlock(block, 3);
		BOOST_CHECK_THROW(iStream.ReadByte(), std::ios_base::failure);
	}

BOOST_AUTO_TEST_SUITE_END();