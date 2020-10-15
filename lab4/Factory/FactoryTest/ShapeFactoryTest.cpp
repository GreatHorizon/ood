#include "stdafx.h"
#include "../Factory/ShapeFactory.h"


struct ShapeFactoryFixture
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactoryFixture)
	BOOST_AUTO_TEST_SUITE(create_draft_test)

		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_command_is_invalid)
		{
			BOOST_CHECK_THROW(factory.CreateShape("circle 1 1 0.4 0.4 green"), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(triangle_creating_test)
			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_arguments_count_is_incorrect)
			{
				BOOST_CHECK_THROW(factory.CreateShape("triangle 1 1 0 0 green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_vertices_is_not_digit)
			{
				BOOST_CHECK_THROW(factory.CreateShape("triangle 1 0 a 0 0 1 green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_make_triangle)
			{
				auto shape = factory.CreateShape("triangle 1 0 0 0 0 1 green");
				auto triangle = dynamic_cast<CTriangle&>(*shape.get());
			
				BOOST_CHECK(triangle.GetVertex1() == CPoint(1, 0));
				BOOST_CHECK(triangle.GetVertex2() == CPoint(0, 0));
				BOOST_CHECK(triangle.GetVertex3() == CPoint(0, 1));
				BOOST_CHECK(triangle.GetColor() == Color::GREEN);
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(rectangle_creating_test)
			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_arguments_count_is_incorrect)
			{
				BOOST_CHECK_THROW(factory.CreateShape("rectangle 1 1 0 0 0 0 0 green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_vertices_is_not_digit)
			{
				BOOST_CHECK_THROW(factory.CreateShape("rectangle 1 0 a 0 green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_make_rectangle)
			{
				auto shape = factory.CreateShape("rectangle 1 0 1 0.5 blue");
				auto rectangle = dynamic_cast<CRectangle&>(*shape.get());

				BOOST_CHECK(rectangle.GetLeftTop() == CPoint(1, 0));
				BOOST_CHECK(rectangle.GetRightBottom() == CPoint(2, -0.5));
				BOOST_CHECK(rectangle.GetHeight() == 0.5);
				BOOST_CHECK(rectangle.GetWidth() == 1);
				BOOST_CHECK(rectangle.GetColor() == Color::BLUE);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(ellipse_creating_test)
			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_arguments_count_is_incorrect)
			{
				BOOST_CHECK_THROW(factory.CreateShape("ellipse green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_vertices_is_not_digit)
			{
				BOOST_CHECK_THROW(factory.CreateShape("ellipse 1 0 a 0 green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_make_ellipse)
			{
				auto shape = factory.CreateShape("ellipse 1 0 1 0.5 pink");
				auto ellipse = dynamic_cast<CEllipse&>(*shape.get());

				BOOST_CHECK(ellipse.GetCenter() == CPoint(1, 0));
				BOOST_CHECK(ellipse.GetHorizontalRadius() == 0.5);
				BOOST_CHECK(ellipse.GetVerticalRadius() == 1);
				BOOST_CHECK(ellipse.GetColor() == Color::PINK);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(regular_polygon_creating_test)
			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_arguments_count_is_incorrect)
			{
				BOOST_CHECK_THROW(factory.CreateShape("regularPolygon green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_vertices_is_not_digit)
			{
				BOOST_CHECK_THROW(factory.CreateShape("regularPolygon 1 0 a 0 green"), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(should_make_regular_polygon)
			{
				auto shape = factory.CreateShape("regularPolygon 1 0 1 5 pink");
				auto regularPolygon = dynamic_cast<CRegularPolygon&>(*shape.get());

				BOOST_CHECK(regularPolygon.GetCenter() == CPoint(1, 0));
				BOOST_CHECK(regularPolygon.GetRadius() == 1);
				BOOST_CHECK(regularPolygon.GetVertexCount() == 5);
				BOOST_CHECK(regularPolygon.GetColor() == Color::PINK);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()