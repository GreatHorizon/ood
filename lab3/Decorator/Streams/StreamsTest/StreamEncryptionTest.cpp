#include "stdafx.h"
#include "../Streams/COutputStreamEnctyptor.h"
#include "../Streams/CInputStreamDecryptor.h"
#include "../Streams/CMemoryInputStream.h"
#include "../Streams/CMemoryOutputStream.h"
#include "../Streams/CFileInputStream.h"
#include "../Streams/CFileOutputStream.h"
#include "AdditionalFunctions.h"

const std::string filePath = std::filesystem::temp_directory_path().string() + "output.bin";

BOOST_AUTO_TEST_SUITE(stream_enctyption_test)
	BOOST_AUTO_TEST_CASE(can_encrypt_and_decrypt_byte)
	{
		std::vector<uint8_t> memory;
		auto oStream = std::make_unique<CMemoryOutputStream>(memory);
		auto encryptedStream = std::make_unique<COutputStreamEncryptor>(std::move(oStream), 100500);

		encryptedStream->WriteByte('a');
		encryptedStream->WriteByte('b');
		encryptedStream->WriteByte(1);

		BOOST_CHECK_NE(memory[0], 'a');
		BOOST_CHECK_NE(memory[1], 'b');
		BOOST_CHECK_NE(memory[2], 1);

		auto iStream = std::make_unique<CMemoryInputStream>(memory);
		auto decryptedStream = std::make_unique<CInputStreamDectyptor>(std::move(iStream), 100500);

		BOOST_CHECK_EQUAL(decryptedStream->ReadByte(), 'a');
		BOOST_CHECK_EQUAL(decryptedStream->ReadByte(), 'b');
		BOOST_CHECK_EQUAL(decryptedStream->ReadByte(), 1);
	}

	BOOST_AUTO_TEST_CASE(can_encrypt_and_decrypt_block)
	{
		std::vector<uint8_t> memory;
		auto oStream = std::make_unique<CMemoryOutputStream>(memory);
		auto encryptedStream = std::make_unique<COutputStreamEncryptor>(std::move(oStream), 100500);

		uint8_t sourceBlock[] = {1, 2, 3, 4};
		encryptedStream->WriteBlock(sourceBlock, 4);

		BOOST_CHECK_NE(memory[0], 1);
		BOOST_CHECK_NE(memory[1], 2);
		BOOST_CHECK_NE(memory[2], 3);
		BOOST_CHECK_NE(memory[3], 4);

		auto iStream = std::make_unique<CMemoryInputStream>(memory);
		auto decryptedStream = std::make_unique<CInputStreamDectyptor>(std::move(iStream), 100500);
		
		uint8_t decryptedBlock[4];
		decryptedStream->ReadBlock(decryptedBlock, 4);

		BOOST_CHECK_EQUAL(decryptedBlock[0], 1);
		BOOST_CHECK_EQUAL(decryptedBlock[1], 2);
		BOOST_CHECK_EQUAL(decryptedBlock[2], 3);
		BOOST_CHECK_EQUAL(decryptedBlock[3], 4);
	}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(file_stream_compression_test)
	BOOST_AUTO_TEST_CASE(can_encrypt_and_decrypt_byte)
	{
		{
			auto oStream = std::make_unique<CFileOutputStream>(filePath);
			auto encryptedStream = std::make_unique<COutputStreamEncryptor>(std::move(oStream), 100500);

			encryptedStream->WriteByte('a');
			encryptedStream->WriteByte('b');	
			encryptedStream->WriteByte(1);
			BOOST_CHECK(GetStringFromStream(filePath) != "ab\1");
		}

		auto iStream = std::make_unique<CFileInputStream>(filePath);
		auto decryptedStream = std::make_unique<CInputStreamDectyptor>(std::move(iStream), 100500);

		BOOST_CHECK_EQUAL(decryptedStream->ReadByte(), 'a');
		BOOST_CHECK_EQUAL(decryptedStream->ReadByte(), 'b');
		BOOST_CHECK_EQUAL(decryptedStream->ReadByte(), 1);
	}

	BOOST_AUTO_TEST_CASE(can_encrypt_and_decrypt_block)
	{
		{
			auto oStream = std::make_unique<CFileOutputStream>(filePath);
			auto encryptedStream = std::make_unique<COutputStreamEncryptor>(std::move(oStream), 100500);
			uint8_t sourceBlock[] = { 1, 2, 3, 4 };
			encryptedStream->WriteBlock(sourceBlock, 4);
			BOOST_CHECK(GetStringFromStream(filePath) != "\1\2\3\4");
		}

		auto iStream = std::make_unique<CFileInputStream>(filePath);
		auto decryptedStream = std::make_unique<CInputStreamDectyptor>(std::move(iStream), 100500);
		uint8_t decryptedBlock[4];
		decryptedStream->ReadBlock(decryptedBlock, 4);

		BOOST_CHECK_EQUAL(decryptedBlock[0], 1);
		BOOST_CHECK_EQUAL(decryptedBlock[1], 2);
		BOOST_CHECK_EQUAL(decryptedBlock[2], 3);
		BOOST_CHECK_EQUAL(decryptedBlock[3], 4);
	}
BOOST_AUTO_TEST_SUITE_END();