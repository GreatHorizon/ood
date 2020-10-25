#pragma once

#include "IImage.h"
#include "ICommandSink.h"
#include <random>

class CImage : public IImage
{
public:
	// Возвращает путь относительно каталога документа
	Path GetPath() const;

	// Ширина изображения в пикселях
	int GetWidth() const;

	// Высота изображения в пикселях
	int GetHeight() const;

	// Изменяет размер изображения
	void Resize(int width, int height);

	CImage(std::unique_ptr<ICommandSink>&& historyAdapter, Path const& path, int height, int width);
	~CImage();
private:
	Path m_path;
	int m_height;
	int m_width;
	std::unique_ptr<ICommandSink> m_historyAdapter;
};

inline std::string GetRandomImageName()
{
	const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, static_cast<int>(CHARACTERS.size()) - 1);

	std::string randomString;

	for (std::size_t i = 0; i < 10; ++i)
	{
		randomString += CHARACTERS[distribution(generator)];
	}

	return randomString;
}

inline bool IsImage(std::string const& extention)
{
	if (extention == ".jpg" || extention == ".png")
	{
		return true;
	}

	return false;
}

inline bool IsCorrectSizeParameter(int parametr)
{
	if (parametr > 0 && parametr < 1000)
	{
		return true;
	}

	return false;
}