#include "GroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(OutlineStyleEnumerator function)
    : m_enumerator(function)
{
}

std::optional<bool> CGroupOutlineStyle::IsEnabled() const
{
    std::optional<bool> result;
    bool isFirstStyle = true;

    auto callback = [&](IOutlineStyle& style)
    {
        if (isFirstStyle)
        {
            result = style.IsEnabled();
            isFirstStyle = false;
        }
        else if (style.IsEnabled() != result)
        {
            result = std::nullopt;
        }
    };

    m_enumerator(callback);

    return result;

}

void CGroupOutlineStyle::Enable(bool enable)
{
    auto callback = [&](IOutlineStyle& style)
    {
        style.Enable(true);
    };

    m_enumerator(callback);
}

std::optional<RGBAColor> CGroupOutlineStyle::GetColor() const
{
    std::optional<RGBAColor> result;
    bool isFirstStyle = true;

    auto callback = [&](IOutlineStyle& style)
    {
        if (isFirstStyle)
        {
            result = style.GetColor();
            isFirstStyle = false;
        }
        else if (style.GetColor() != result)
        {
            result = std::nullopt;
        }
    };

    m_enumerator(callback);

    return result;
}

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
    auto callback = [&](IOutlineStyle& style)
    {
        style.SetColor(color);
    };

    m_enumerator(callback);
}

std::optional<float> CGroupOutlineStyle::GetThickness() const
{
    std::optional<float> result;
    bool isFirstStyle = true;

    auto callback = [&](IOutlineStyle& style)
    {
        if (isFirstStyle)
        {
            result = style.GetThickness();
            isFirstStyle = false;
        }
        else if (style.GetThickness() != result)
        {
            result = std::nullopt;
        }
    };

    m_enumerator(callback);

    return result;
}

void CGroupOutlineStyle::SetThickness(float thickness)
{
    auto callback = [&](IOutlineStyle& style)
    {
        style.SetThickness(thickness);
    };

    m_enumerator(callback);
}
