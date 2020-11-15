#include "stdafx.h"
#include "../Streams/CFileInputStream.h"
#include "../Streams/CFileOutputStream.h"
#include "../Streams/CMemoryInputStream.h"
#include "../Streams/CMemoryOutputStream.h"
#include "../Streams/COutputStreamCompressor.h"
#include "../Streams/CInputStreamDecompressor.h"
#include "AdditionalFunctions.h"

const std::string filePath = std::filesystem::temp_directory_path().string() + "output.bin";

BOOST_AUTO_TEST_SUITE(memory_stream_compression_test)

	BOOST_AUTO_TEST_CASE(can_compress_and_decompress_byte)
	{
		std::vector<uint8_t> memory;
		{
			auto stream = std::make_unique<CMemoryOutputStream>(memory);
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
			compressedStream->WriteByte('a');
			compressedStream->WriteByte('b');
			compressedStream->WriteByte('b');
		}

		BOOST_CHECK_EQUAL(memory[0], 1);
		BOOST_CHECK_EQUAL(memory[1], 'a');
		BOOST_CHECK_EQUAL(memory[2], 2);
		BOOST_CHECK_EQUAL(memory[3], 'b');

		auto stream = std::make_unique<CMemoryInputStream>(memory);
		auto compressedStream = std::make_unique<CInputStreamDecompressor>(std::move(stream));
		BOOST_CHECK_EQUAL(compressedStream->ReadByte(), 'a');
		BOOST_CHECK_EQUAL(compressedStream->ReadByte(), 'b');
		BOOST_CHECK_EQUAL(compressedStream->ReadByte(), 'b');
	}

	BOOST_AUTO_TEST_CASE(can_compress_and_decompress_block)
	{
		std::vector<uint8_t> memory;
		{
			uint8_t block[] = { 'f', 'f', 'f', 'c'};
			auto stream = std::make_unique<CMemoryOutputStream>(memory);
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
			compressedStream->WriteBlock(block, 4);
		}

		BOOST_CHECK_EQUAL(memory[0], 3);
		BOOST_CHECK_EQUAL(memory[1], 'f');
		BOOST_CHECK_EQUAL(memory[2], 1);
		BOOST_CHECK_EQUAL(memory[3], 'c');

		auto stream = std::make_unique<CMemoryInputStream>(memory);
		auto compressedStream = std::make_unique<CInputStreamDecompressor>(std::move(stream));
		uint8_t block[4];
		compressedStream->ReadBlock(block, 4);
		BOOST_CHECK_EQUAL(block[0], 'f');
		BOOST_CHECK_EQUAL(block[1], 'f');
		BOOST_CHECK_EQUAL(block[2], 'f');
		BOOST_CHECK_EQUAL(block[3], 'c');
	}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(file_stream_compression_test)
	BOOST_AUTO_TEST_CASE(can_compress_and_decompress_byte)
	{		
		{
			auto stream = std::make_unique<CFileOutputStream>(filePath);
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));

			compressedStream->WriteByte('a');
			compressedStream->WriteByte('b');
			compressedStream->WriteByte('b');
		}

		BOOST_CHECK_EQUAL(GetStringFromStream(filePath), "\1a\2b");

		auto stream = std::make_unique<CFileInputStream>(filePath);
		auto compressedStream = std::make_unique<CInputStreamDecompressor>(std::move(stream));
		BOOST_CHECK_EQUAL(compressedStream->ReadByte(), 'a');
		BOOST_CHECK_EQUAL(compressedStream->ReadByte(), 'b');
		BOOST_CHECK_EQUAL(compressedStream->ReadByte(), 'b');
	}

	BOOST_AUTO_TEST_CASE(can_compress_and_decompress_block)
	{
		{
			uint8_t block[] = { 'f', 'f', 'f', 'c' };
			auto stream = std::make_unique<CFileOutputStream>(filePath);
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
			compressedStream->WriteBlock(block, 4);
		}

		BOOST_CHECK_EQUAL(GetStringFromStream(filePath), "\3f\1c");

		auto stream = std::make_unique<CFileInputStream>(filePath);
		auto compressedStream = std::make_unique<CInputStreamDecompressor>(std::move(stream));
		uint8_t block[4];
		compressedStream->ReadBlock(block, 4);
		BOOST_CHECK_EQUAL(block[0], 'f');
		BOOST_CHECK_EQUAL(block[1], 'f');
		BOOST_CHECK_EQUAL(block[2], 'f');
		BOOST_CHECK_EQUAL(block[3], 'c');
	}

	BOOST_AUTO_TEST_CASE(can_compress_empty_file)
	{
		{
			auto stream = std::make_unique<CFileOutputStream>(filePath);
			auto compressedStream = std::make_unique<COutputStreamCompressor>(std::move(stream));
		}
	
		BOOST_CHECK(GetStringFromStream(filePath) == "");
	}


BOOST_AUTO_TEST_SUITE_END();
