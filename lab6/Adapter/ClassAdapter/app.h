#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

// ������������ ���� ���������� (�������� ��� �����������)
namespace app
{
	class ModernGraphicsAdapter : public graphics_lib::ICanvas, 
		public modern_graphics_lib::CModernGraphicsRenderer
	{
	public:
		ModernGraphicsAdapter(std::ostream& stream)
			: modern_graphics_lib::CModernGraphicsRenderer(stream)
			, m_startPoint(0, 0)
			, m_color(0, 0, 0, 1)
		{
		}

		void MoveTo(int x, int y) override
		{
			m_startPoint = { x, y };
		}

		void LineTo(int x, int y) override
		{
			DrawLine(m_startPoint, { x, y }, m_color);
		}

		void SetColor(uint32_t rgbColor) override
		{
			auto r = ((rgbColor >> 16) & 255) / 255.0f;
			auto g = ((rgbColor >> 8) & 255) / 255.0f;
			auto b = (rgbColor & 255) / 255.0f;

			m_color = CRGBAColor(r, g, b, 1);
		}

		void SetOpacity(float opacity)
		{
			m_color.a = opacity;
		}

	private:
		modern_graphics_lib::CPoint m_startPoint;
		CRGBAColor m_color;
	};

	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x242424);
		CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		app::ModernGraphicsAdapter adaptedGraphics(std::cout);
		shape_drawing_lib::CCanvasPainter painter(adaptedGraphics);

		adaptedGraphics.BeginDraw();
		PaintPicture(painter);
		adaptedGraphics.EndDraw();
	}
}