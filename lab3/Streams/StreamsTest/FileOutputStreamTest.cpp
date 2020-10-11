#include "stdafx.h"
#include "../Streams/CFileOutputStream.h"
#include "AdditionalFunctions.h"

const std::string outputPath = std::filesystem::temp_directory_path().string() + "output.bin";

BOOST_AUTO_TEST_SUITE(output_file_stream_test)
	BOOST_AUTO_TEST_CASE(can_put_byte)
	{
		{
			CFileOutputStream oStream(outputPath);
			oStream.WriteByte('a');
			oStream.WriteByte('v');
			oStream.WriteByte('9');
		}
		
		BOOST_CHECK_EQUAL(GetStringFromStream(outputPath), "av9");
	}

	BOOST_AUTO_TEST_CASE(can_put_block)
	{
		{
			CFileOutputStream oStream(outputPath);
			char block[5] = { 'a', 'b', '0', '_', '&' };
			oStream.WriteBlock(block, 5);
		}

		BOOST_CHECK_EQUAL(GetStringFromStream(outputPath), "ab0_&");
	}
BOOST_AUTO_TEST_SUITE_END();