#include "stdafx.h"
#include "../Slide/Ellipse.h"
#include "../Slide/Group.h"
#include "../Slide/Rectangle.h"
#include "../Slide/Triangle.h"
#include "MockCanvas.h"


struct EmptyGroup
{
	std::shared_ptr<IGroup> group = std::make_shared<CGroup>();
};

BOOST_FIXTURE_TEST_SUITE(group_test, EmptyGroup)
	BOOST_AUTO_TEST_SUITE(when_group_is_empty)
		BOOST_AUTO_TEST_CASE(group_size_should_be_zero)
		{
			BOOST_CHECK_EQUAL(group->GetShapesCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(get_frame_should_return_nullopt)
		{
			BOOST_CHECK(group->GetFrame() == std::nullopt);
		}

		BOOST_AUTO_TEST_CASE(set_frame_shoud_not_change_frame)
		{
			group->SetFrame(RectD(0, 0, 1, 1));
			BOOST_CHECK(group->GetFrame() == std::nullopt);
		}

		BOOST_AUTO_TEST_CASE(get_group_shoud_not_return_nullptr)
		{
			BOOST_CHECK(group->GetGroup());
		}

		BOOST_AUTO_TEST_CASE(after_adding_empty_group_frame_should_be_nullopt)
		{
			group->InsertShape(std::make_shared<CGroup>());
			BOOST_CHECK(group->GetFrame() == std::nullopt);
		}

		BOOST_AUTO_TEST_CASE(get_color_from_outline_style_should_be_nullopt)
		{
			BOOST_CHECK(group->GetOutlineStyle()->GetColor() == std::nullopt);
		}

		BOOST_AUTO_TEST_CASE(get_color_from_fill_style_should_be_nullopt)
		{
			BOOST_CHECK(group->GetFillStyle()->GetColor() == std::nullopt);
		}

		BOOST_AUTO_TEST_CASE(can_insert_element_to_the_end)
		{
			group->InsertShape(std::make_shared<CTriangle>(CPoint(1, 0), CPoint(-1, 0), CPoint(0, 1)));
			auto triangle = dynamic_cast<CTriangle&>(*group->GetShapeAtIndex(0).get());
			BOOST_CHECK(triangle.GetVertex1() == CPoint(1, 0));
		}

		BOOST_AUTO_TEST_CASE(insert_into_position_1_shoud_throw_an_exception)
		{
			BOOST_CHECK_THROW(group->InsertShape(std::make_shared<CTriangle>(CPoint(1, 0), CPoint(-1, 0), CPoint(0, 1)), 1), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(delete_from_position_1_shoud_throw_an_exception)
		{
			BOOST_CHECK_THROW(group->RemoveShapeAtIndex(1), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(get_from_position_1_shoud_throw_an_exception)
		{
			BOOST_CHECK_THROW(group->GetShapeAtIndex(1), std::out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct AfterShapesInserting : EmptyGroup
	{
		AfterShapesInserting()
		{
			group->InsertShape(std::make_shared<CTriangle>(CPoint(0, 3), CPoint(1, 0), CPoint(-1, 0)));
			group->InsertShape(std::make_shared<CRectangle>(CPoint(3, 3), 2, 3));
			group->InsertShape(std::make_shared<CEllipse>(CPoint(-4, 1.5), 1, 1.5));\
			group->InsertShape(std::make_shared<CGroup>());
		}
	};

	BOOST_FIXTURE_TEST_SUITE(group_with_elements_test, AfterShapesInserting)
		BOOST_AUTO_TEST_CASE(can_insert_element_in_1_position)
		{
			group->InsertShape(std::make_shared<CTriangle>(CPoint(2, 0), CPoint(-1, 0), CPoint(0, 1)), 1);
			auto triangle = dynamic_cast<CTriangle&>(*group->GetShapeAtIndex(1).get());
			BOOST_CHECK(triangle.GetVertex1() == CPoint(2, 0));
			BOOST_CHECK_EQUAL(group->GetShapesCount(), 5);
		}

		BOOST_AUTO_TEST_CASE(can_delete_element)
		{
			group->RemoveShapeAtIndex(1);
			BOOST_CHECK_EQUAL(group->GetShapesCount(), 3);
		}

		BOOST_AUTO_TEST_CASE(can_get_group_frame)
		{
			auto frame = group->GetFrame().value();
			BOOST_CHECK_EQUAL(frame.m_leftTop.m_x, -5);
			BOOST_CHECK_EQUAL(frame.m_leftTop.m_y, 3);
			BOOST_CHECK_EQUAL(frame.m_width, 10);
			BOOST_CHECK_EQUAL(frame.m_height, 3);
		}

		BOOST_AUTO_TEST_CASE(can_set_frame)
		{
			group->SetFrame(RectD(-5, 6, 10, 6));
			
			auto triangleFrame = group->GetShapeAtIndex(0)->GetFrame().value();

			BOOST_CHECK_EQUAL(triangleFrame.m_height, 6);
			BOOST_CHECK_EQUAL(triangleFrame.m_width, 2);
			BOOST_CHECK_EQUAL(triangleFrame.m_leftTop.m_x, -1);
			BOOST_CHECK_EQUAL(triangleFrame.m_leftTop.m_y, 6);

			group->SetFrame(RectD(-7, 6, 12, 6));

			auto rectangleFrame = group->GetShapeAtIndex(1)->GetFrame().value();

			BOOST_CHECK_EQUAL(rectangleFrame.m_height, 6);
			BOOST_CHECK_EQUAL(rectangleFrame.m_width, 2.4);
			BOOST_CHECK_EQUAL(rectangleFrame.m_leftTop.m_y, 6);
		}

		BOOST_AUTO_TEST_CASE(can_draw_group)
		{
			std::stringstream out, streamForExpectedOutput;
			streamForExpectedOutput << "Set ffffffff fill color\n" <<
				"Set ff00ff79 outline color\n" <<
				"Set 2 line width\n" <<
				"Fill poligon\n" <<
				"Drawing line\n" <<
				"Drawing line\n" <<
				"Drawing line\n" <<
				"Set ffffffff fill color\n" <<
				"Fill poligon\n" <<
				"Set ffffffff fill color\n" <<
				"Fill ellipse\n";
			std::string expectedOutput = streamForExpectedOutput.str();
			MockCanvas canvas(out);


			group->GetShapeAtIndex(0)->GetOutlineStyle()->Enable(true);
			group->GetShapeAtIndex(0)->GetOutlineStyle()->SetThickness(2);
			group->GetShapeAtIndex(0)->GetOutlineStyle()->SetColor(0xff00ff79);

			group->Draw(canvas);
		
			BOOST_CHECK_EQUAL(out.str(), expectedOutput);
		}

		BOOST_AUTO_TEST_CASE(get_color_should_return_nullopt_when_chapes_with_different_color)
		{
			BOOST_CHECK(group->GetOutlineStyle()->GetColor() == std::nullopt);
			BOOST_CHECK(group->GetFillStyle()->GetColor() == std::nullopt);
		}

		BOOST_AUTO_TEST_CASE(set_color_should_set_color_for_all_shapes)
		{
			group->GetFillStyle()->SetColor(0xffffffff);
			group->GetOutlineStyle()->SetColor(0xff00ffff);

			group->GetShapeAtIndex(3)->GetGroup()->InsertShape(std::make_shared<CTriangle>(CPoint(5, 0), CPoint(-1, 0), CPoint(0, 1)));

			BOOST_CHECK(group->GetFillStyle()->GetColor().has_value());
			BOOST_CHECK(group->GetFillStyle()->GetColor().has_value());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()