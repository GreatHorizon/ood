#include "stdafx.h"
#include "../DocumentEditor/Paragraph.h"
#include "CMockHistoryAdapted.h"

struct ParagraphFixture
{
	std::stringstream out;
	std::unique_ptr<CMockHistoryAdapter> adapter = std::make_unique<CMockHistoryAdapter>(out);
	std::unique_ptr<CParagraph> paragraph;

	ParagraphFixture()
	{
		paragraph = std::make_unique<CParagraph>(std::move(adapter), "some text");
	}
};

BOOST_FIXTURE_TEST_SUITE(ReplaceTextTest, ParagraphFixture)
	BOOST_AUTO_TEST_CASE(can_get_text)
	{
		BOOST_CHECK_EQUAL(paragraph->GetText(), "some text");
	}

	BOOST_AUTO_TEST_CASE(adaptor_should_save_command_when_text_is_setting)
	{
		paragraph->SetText("some new text");
		BOOST_CHECK_EQUAL(out.str(), "Command saved and executed\n");
	}
BOOST_AUTO_TEST_SUITE_END()