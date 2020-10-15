#include "stdafx.h"
#include "../Factory/Rectangle.h"
#include "../Factory/Ellipse.h"
#include "../Factory/Triangle.h"
#include "../Factory/RegularPolygon.h"
#include "../Factory/Painter.h"
#include "MockCanvas.h"

struct PainterFixture
{
	CPictureDraft draft;
	MockCanvas canvas;
	CPainter painter;

	PainterFixture()
	{
		auto triangle = std::make_unique<CTriangle>(CPoint(0, 0), CPoint(0, 1), CPoint(1, 0), Color::BLACK);
		auto ellipse = std::make_unique<CEllipse>(CPoint(0, 0), 0.5, 0.6, Color::GREEN);
		auto rectangle = std::make_unique<CRectangle>(CPoint(0, 0), 1, 0.5, Color::RED);
		auto regularPolygon = std::make_unique<CRegularPolygon>(CPoint(0, 0), 0.5, 5, Color::YELLOW);

		draft.AddShape(std::move(triangle));
		draft.AddShape(std::move(ellipse));
		draft.AddShape(std::move(rectangle));
		draft.AddShape(std::move(regularPolygon));
	}
};

BOOST_FIXTURE_TEST_SUITE(painter_test, PainterFixture)
	BOOST_AUTO_TEST_SUITE(draw_picture_test)
		BOOST_AUTO_TEST_CASE(should_draw_all_shapes_from_draft)
		{
			painter.DrawPicture(draft, canvas);

			BOOST_CHECK_EQUAL(canvas.m_lineCount, 12);
			BOOST_CHECK_EQUAL(canvas.m_ellipseCount, 1);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()