#include "stdafx.h"
#include "../ClassAdapter/app.h"
#include <sstream>

struct ClassAdapterFixture
{
	std::stringstream stream;
	app::ModernGraphicsAdapter adapter;

	ClassAdapterFixture()
		: adapter(stream)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(ClassAdapterTest, ClassAdapterFixture)

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_draw_before_begin_draw)
	{
		adapter.MoveTo(5, 4);
		BOOST_CHECK_THROW(adapter.LineTo(1, 1), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_restart_drawing)
	{
		adapter.BeginDraw();
		BOOST_CHECK_THROW(adapter.BeginDraw(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_end_drawing_before_restart)
	{
		BOOST_CHECK_THROW(adapter.EndDraw(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(cant_draw_line_after_draw_end)
	{
		adapter.BeginDraw();
		adapter.MoveTo(5, 4);
		adapter.EndDraw();
		BOOST_CHECK_THROW(adapter.LineTo(1, 1), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(can_set_color)
	{
		adapter.SetColor(0xffffff);
		adapter.BeginDraw();
		adapter.MoveTo(5, 4);
		adapter.LineTo(1, 1);
		adapter.EndDraw();
		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n  <line fromX=\"5\" fromY=\"4\" toX=\"1\" toY=\"1\"/>\n    <color r=\"1\" g=\"1\" b=\"1\" a=\"1\" />\n  </line>\n</draw>\n");
	}

	BOOST_AUTO_TEST_CASE(can_set_opacity)
	{
		adapter.SetColor(0xffffff);
		adapter.SetOpacity(0.5);
		adapter.BeginDraw();
		adapter.MoveTo(5, 4);
		adapter.LineTo(1, 1);
		adapter.EndDraw();
		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n  <line fromX=\"5\" fromY=\"4\" toX=\"1\" toY=\"1\"/>\n    <color r=\"1\" g=\"1\" b=\"1\" a=\"0.5\" />\n  </line>\n</draw>\n");
	}

	BOOST_AUTO_TEST_CASE(can_draw_line_inside_begin_block)
	{
		adapter.BeginDraw();
		adapter.MoveTo(5, 4);
		adapter.LineTo(1, 1);
		adapter.EndDraw();

		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n  <line fromX=\"5\" fromY=\"4\" toX=\"1\" toY=\"1\"/>\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n</draw>\n");
	}

	BOOST_AUTO_TEST_CASE(after_set_color_opacity_should_be_1)
	{
		adapter.BeginDraw();
		adapter.SetColor(0xffffff);
		adapter.MoveTo(5, 4);
		adapter.LineTo(1, 1);
		adapter.EndDraw();
		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n  <line fromX=\"5\" fromY=\"4\" toX=\"1\" toY=\"1\"/>\n    <color r=\"1\" g=\"1\" b=\"1\" a=\"1\" />\n  </line>\n</draw>\n");
	}

	BOOST_AUTO_TEST_CASE(when_start_drawing_without_move_to_start_point_should_be_zero)
	{
		adapter.BeginDraw();
		adapter.LineTo(1, 1);
		adapter.EndDraw();
		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n  <line fromX=\"0\" fromY=\"0\" toX=\"1\" toY=\"1\"/>\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n</draw>\n");
	}

BOOST_AUTO_TEST_SUITE_END();