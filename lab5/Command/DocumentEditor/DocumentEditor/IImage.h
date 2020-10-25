#pragma once
#include <boost/optional.hpp>
#include <filesystem>

typedef std::filesystem::path Path;

class IImage
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual Path GetPath() const = 0;

	// ������ ����������� � ��������
	virtual int GetWidth() const = 0;
	// ������ ����������� � ��������
	virtual int GetHeight() const = 0;

	// �������� ������ �����������
	virtual void Resize(int width, int height) = 0;

	virtual ~IImage() = default;
};