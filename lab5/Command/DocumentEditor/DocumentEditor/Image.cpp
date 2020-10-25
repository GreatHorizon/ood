#include "Image.h"
#include "stdafx.h"
#include "ResizeImageCommand.h"

Path CImage::GetPath() const
{
    return m_path;
}

int CImage::GetWidth() const
{
    return m_width;
}

int CImage::GetHeight() const
{
    return m_height;
}

void CImage::Resize(int width, int height)
{
    auto resizeCommand = std::make_unique<CResizeImageCommand>(m_width, m_height, width, height);
    m_historyAdapter->SaveCommand(std::move(resizeCommand));
}

CImage::CImage(std::unique_ptr<ICommandSink>&& historyAdapter, Path const& path, int height, int width)
    : m_historyAdapter(std::move(historyAdapter))
{

    if (!IsCorrectSizeParameter(height) || !IsCorrectSizeParameter(width))
    {
        throw std::invalid_argument("Incorrect image size");
    }

    if (std::filesystem::exists(path) && IsImage(path.extension().string()))
    {
        std::string imagePath = IMAGES_DIRECTORY + "/" + GetRandomImageName() + path.extension().string();
        std::filesystem::copy_file(path, imagePath);
        m_path = imagePath;
    }
    else
    {
        throw std::invalid_argument("Invalid image path");
    }

    m_height = height;
    m_width = width;
}

CImage::~CImage()
{
    try
    {
        std::filesystem::remove(m_path);
    }
    catch (const std::exception&)
    {
    }
}

