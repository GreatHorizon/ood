#include "GroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(FillStyleEnumerator enumerator)
    : m_enumerator(enumerator)
{
}

std::optional<bool> CGroupFillStyle::IsEnabled() const
{
    std::optional<bool> result;
    bool isFirstStyle = true;

    auto callback = [&](IStyle& style) 
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

void CGroupFillStyle::Enable(bool enable)
{
    auto callback = [&](IStyle& style)
    {
        style.Enable(true);
    };

    m_enumerator(callback);
}

std::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
    std::optional<RGBAColor> result;
    bool isFirstStyle = true;

    auto callback = [&](IStyle& style)
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

void CGroupFillStyle::SetColor(RGBAColor color)
{
    auto callback = [&](IStyle& style)
    {
        style.SetColor(color);
    };

    m_enumerator(callback);
}
