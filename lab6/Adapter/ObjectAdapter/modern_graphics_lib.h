#pragma once
#include <iostream>
#include <boost/format.hpp>


class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
	float r, g, b, a;
};

// ѕространство имен современной графической библиотеки (недоступно дл€ изменени€)
namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	//  ласс дл€ современного рисовани€ графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream& strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // «авершаем рисование, если оно было начато
			{
				EndDraw();
			}
		}

		// Ётот метод должен быть вызван в начале рисовани€
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// ¬ыполн€ет рисование линии
		void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
		{
			if (!m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}

			m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
				% start.x % start.y % end.x % end.y << std::endl;
			m_out << boost::format(R"(    <color r="%1%" g="%2%" b="%3%" a="%4%" />)")
				% color.r % color.g % color.b % color.a << std::endl;
			m_out << "  </line>\n";
		}

		// Ётот метод должен быть вызван в конце рисовани€
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}
	private:
		std::ostream& m_out;
		bool m_drawing = false;
	};
}