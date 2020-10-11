#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "CInputStreamDecompressor.h"
#include "COutputStreamEnctyptor.h"
#include "CInputStreamDecryptor.h"
#include "COutputStreamCompressor.h"
#include "CMemoryInputStream.h"
#include "CMemoryOutputStream.h"

enum class OptionType
{
	COMPRESS,
	DECOMPRESS,
	ENCRYPT,
	DECRYPT
};

struct Option
{
	OptionType m_type;
	std::optional<unsigned> m_key;
};

struct FileNames
{
	std::string m_inputStreamName;
	std::string m_outputStreamName;
};

struct ParsedArgs
{
	std::vector<Option> options;
	FileNames names;
};

ParsedArgs GetParseArgs(int argc, char** argv)
{
	ParsedArgs arguments;

	if (argc < 2)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	for (int i = 1; i < argc - 2; i++)
	{
		std::string option = argv[i]; 

		if (option == "--encrypt")
		{
			arguments.options.push_back({OptionType::ENCRYPT, std::stoul(argv[++i])});
		}

		else if (option == "--decrypt")
		{
			arguments.options.push_back({ OptionType::DECRYPT, std::stoul(argv[++i]) });
		}

		else if (option == "--compress")
		{
			arguments.options.push_back({ OptionType::COMPRESS, std::nullopt});
		}

		else if (option == "--decompress")
		{
			arguments.options.push_back({ OptionType::DECOMPRESS, std::nullopt });
		}
	}

	arguments.names.m_inputStreamName = argv[argc - 2];
	arguments.names.m_outputStreamName = argv[argc - 1];
	return arguments;
}

std::unique_ptr<IInputStream> DecorateInputStream(std::vector<Option> const& options, std::unique_ptr<IInputStream>&& stream)
{

	for (auto it = options.rbegin(); it != options.rend(); it++)
	{
		if (it->m_type == OptionType::DECRYPT)
		{
			stream = std::move(std::make_unique<CInputStreamDectyptor>(std::move(stream), it->m_key.value()));
		}

		else if (it->m_type == OptionType::DECOMPRESS)
		{
			stream = std::move(std::make_unique<CInputStreamDecompressor>(std::move(stream)));
		}
	}

	return std::move(stream);
}

std::unique_ptr<IOutputStream> DecorateOutputStream(std::vector<Option> const& options, std::unique_ptr<IOutputStream>&& stream)
{

	for (auto option : options)
	{
		if (option.m_type == OptionType::ENCRYPT)
		{
			stream = std::move(std::make_unique<COutputStreamEncryptor>(std::move(stream), option.m_key.value()));
		}

		else if(option.m_type == OptionType::COMPRESS)
		{
			stream = std::move(std::make_unique<COutputStreamCompressor>(std::move(stream)));
		}
	}

	return std::move(stream);
}

void CopyStreams(std::unique_ptr<IInputStream>& inputStream, std::unique_ptr<IOutputStream>& outputStream)
{
	while (!inputStream->IsEOF())
	{
		try
		{
			uint8_t byte = inputStream->ReadByte();
			outputStream->WriteByte(byte);
		}
		catch (...)
		{
		}
	}
}

int main(int argc, char** argv)
{
	ParsedArgs arguments;

	try
	{
		arguments = GetParseArgs(argc, argv);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what();
	}

	auto FileInputStream = std::make_unique<CFileInputStream>(arguments.names.m_inputStreamName);
	auto FileOutputStream = std::make_unique<CFileOutputStream>(arguments.names.m_outputStreamName);


	auto iStream = DecorateInputStream(arguments.options, std::move(FileInputStream));
	auto oStream = DecorateOutputStream(arguments.options, std::move(FileOutputStream));

	CopyStreams(iStream, oStream);
	return 0;
}