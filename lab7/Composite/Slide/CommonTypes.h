#pragma once
#include <cstdint>

template <typename T>
struct Point
{
	T m_x;
	T m_y;
};

template <typename T>
struct Rect
{	
	Point<T> m_leftTop;
	T m_width;
	T m_height;

	Rect(T x, T y, T width, T height)
		: m_leftTop({x, y})
		, m_width(width)
		, m_height(height)
	{
	}
};

typedef Rect<double> RectD;
typedef uint32_t RGBAColor;