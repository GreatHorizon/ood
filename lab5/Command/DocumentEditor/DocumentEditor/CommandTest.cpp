#include "stdafx.h"
#include "../DocumentEditor/Editor.h"


struct CommandTestFixture
{
	std::stringstream input;
	std::stringstream output;
	CEditor editor;

	CommandTestFixture()
		: editor(input, output)
	{
	}
};



BOOST_FIXTURE_TEST_SUITE(TitleTest, AfterSettingTitle)
BOOST_AUTO_TEST_CASE(can_undo_setting_title)
{
	document.Undo();
	BOOST_CHECK_EQUAL(document.GetTitle(), "");
}

BOOST_AUTO_TEST_CASE(can_redo_after_undo)
{
	document.Undo();
	document.Redo();
	BOOST_CHECK_EQUAL(document.GetTitle(), "My new title");
}

BOOST_AUTO_TEST_SUITE_END()