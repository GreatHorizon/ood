#include "stdafx.h"
#include "../Factory/Shape.h"
#include "../Factory/Designer.h"
#include "../Factory/IShapeFactory.h"
#include "../Factory/PictureDraft.h"

using boost::algorithm::all_of;
using boost::copy;

class CMockShape : public CShape
{
public:
	CMockShape(const std::string& descr)
		: descr(descr)
		, CShape(Color::BLACK)
	{
	}

	void Draw(ICanvas& canvas) const
	{
		//drawing
	}

	std::string descr;
};

struct MockShapeFactory : IShapeFactory
{
	std::vector<std::string> shapeDescriptions;
	// Inherited via IShapeFactory
	std::unique_ptr<CShape> CreateShape(const std::string& description) override
	{
		// «апротоколировали описание созданной фигуры
		shapeDescriptions.push_back(description);
		return std::make_unique<CMockShape>(description);
	}
};

struct Designer_
{
	MockShapeFactory factory;
	CDesigner designer = CDesigner(factory);
};

BOOST_FIXTURE_TEST_SUITE(Designer, Designer_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)
		BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
		{
			std::istringstream input;
			auto draft = designer.CreateDraft(input);
			BOOST_CHECK(draft.IsEmpty());
			BOOST_CHECK(input.eof());
		}

		struct when_creating_draft_with_non_empty_input_ : Designer_
		{
			std::vector<std::string> expectedShapeDescriptions = {
				"square", "circle", "triangle"
			};

			std::stringstream strm;
			CPictureDraft returnedDraft;

			when_creating_draft_with_non_empty_input_()
			{
				copy(expectedShapeDescriptions, std::ostream_iterator<std::string>(strm, "\n"));
				returnedDraft = designer.CreateDraft(strm);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_creating_draft_with_non_empty_input, when_creating_draft_with_non_empty_input_)
			BOOST_AUTO_TEST_CASE(passes_each_line_from_input_to_shape_factory)
			{
				BOOST_CHECK(factory.shapeDescriptions == expectedShapeDescriptions);
			}
			BOOST_AUTO_TEST_CASE(returns_draft_with_shapes_created_by_factory)
			{
				std::vector<std::string> shapeDescriptions;
				std::transform(returnedDraft.begin(), returnedDraft.end(), back_inserter(shapeDescriptions), [](auto& shape) {
					auto shapeAsMockShape = dynamic_cast<const CMockShape*>(&shape);
					BOOST_REQUIRE(shapeAsMockShape);
					return shapeAsMockShape->descr;
					});
				BOOST_CHECK(shapeDescriptions == expectedShapeDescriptions);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
