#include "stdafx.h"
#include "../Factory/PictureDraft.h"
#include "../Factory/Rectangle.h"
#include "../Factory/Triangle.h"
#include "../Factory/Ellipse.h"
#include "../Factory/RegularPolygon.h"

struct PictureDraftFixture
{
	CPictureDraft draft;
};

BOOST_FIXTURE_TEST_SUITE(picture_draft_test, PictureDraftFixture)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(draft.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(size_should_be_0)
		{
			BOOST_CHECK_EQUAL(draft.GetShapesCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_attempting_get_shape)
		{
			BOOST_CHECK_THROW(draft.GetShape(1), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(has_equal_begin_and_end_iterators)
		{
			BOOST_CHECK(draft.begin() == draft.end());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_adding_a_shape_ : PictureDraftFixture
	{
		std::unique_ptr<CShape> shape1 = std::make_unique<CTriangle>
			(CPoint(0, 0), CPoint(0, 1), CPoint(1, 0), Color::GREEN);
		std::unique_ptr<CShape> shape2 = std::make_unique<CRectangle>
			(CPoint(0, 0), 0.5, 0.3, Color::BLUE);	
		std::unique_ptr<CShape> shape3 = std::make_unique<CEllipse>
			(CPoint(0, 0), 0.4, 0.5, Color::RED);

		CShape& refShape1 = *shape1;
		CShape& refShape2 = *shape2;
		CShape& refShape3 = *shape3;

		after_adding_a_shape_()
		{
			draft.AddShape(move(shape1));
			draft.AddShape(move(shape2));
			draft.AddShape(move(shape3));
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_adding_a_shape, after_adding_a_shape_)
		BOOST_AUTO_TEST_CASE(becomes_not_empty)
		{
			BOOST_CHECK(!draft.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(has_different_begin_and_end_iterators)
		{
			BOOST_CHECK(draft.begin() != draft.end());
		}

		BOOST_AUTO_TEST_CASE(should_return_ref_to_shape)
		{
			BOOST_CHECK_EQUAL(std::addressof(draft.GetShape(1)), std::addressof(refShape2));
		}

		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_index_out_of_range)
		{
			BOOST_CHECK_THROW(draft.GetShape(4), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(allows_iteration_across_added_shapes)
		{
			auto it = draft.begin();
			BOOST_CHECK_EQUAL(std::addressof(*(it++)), std::addressof(refShape1));
			BOOST_REQUIRE(it != draft.end());
			BOOST_CHECK_EQUAL(std::addressof(*(it++)), std::addressof(refShape2));
			BOOST_REQUIRE(it != draft.end());
			BOOST_CHECK_EQUAL(std::addressof(*(it++)), std::addressof(refShape3));
			BOOST_REQUIRE(it == draft.end());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()