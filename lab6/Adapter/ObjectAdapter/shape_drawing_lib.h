#pragma once

#include "graphics_lib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib::ICanvas& canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color = 0x000000)
			: m_firstVertex(p1)
			, m_secondVertex(p2)
			, m_thirdVertex(p3)
			, m_color(color)
		{
		}

		void Draw(graphics_lib::ICanvas& canvas)const override
		{
			canvas.SetColor(m_color);
			canvas.MoveTo(m_firstVertex.x, m_firstVertex.y);
			canvas.LineTo(m_secondVertex.x, m_secondVertex.y);
			canvas.LineTo(m_thirdVertex.x, m_thirdVertex.y);
			canvas.LineTo(m_firstVertex.x, m_firstVertex.y);
		}
	private:
		Point m_firstVertex;
		Point m_secondVertex;
		Point m_thirdVertex;
		uint32_t m_color;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point& leftTop, int width, int height, uint32_t color = 0x000000)
			: m_leftTop(leftTop)
			, m_height(height)
			, m_width(width)
			, m_color(color)
		{
		}

		void Draw(graphics_lib::ICanvas& canvas)const override
		{
			canvas.SetColor(m_color);
			canvas.MoveTo(m_leftTop.x, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y - m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y);
		}
	private:
		Point m_leftTop;
		int m_width;
		int m_height;
		uint32_t m_color;
	};

	// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib::ICanvas& canvas)
			: m_canvas(canvas)
		{
		}
		void Draw(const ICanvasDrawable& drawable)
		{
			drawable.Draw(m_canvas);
		}
	private:
		graphics_lib::ICanvas& m_canvas;
	};
}