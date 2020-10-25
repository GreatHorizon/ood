#include "stdafx.h"
#include "../DocumentEditor/History.h"
#include "../DocumentEditor/Document.h"

struct DocumentWithExecutedCommands
{
	CDocument document;

	DocumentWithExecutedCommands()
	{
		for (size_t i = 0; i < 11; i++)
		{
			document.SetTitle(std::to_string(i));
		}
	}
};

BOOST_FIXTURE_TEST_SUITE(HistoryTest, DocumentWithExecutedCommands)

	BOOST_AUTO_TEST_CASE(can_undo_and_redo_image_resize)
	{
		document.InsertImage("images/shrek.jpg", 540, 760);
		auto image = document.GetItem(0);

		image.GetImage()->Resize(340, 560);

		BOOST_CHECK_EQUAL(image.GetImage()->GetHeight(), 560);
		BOOST_CHECK_EQUAL(image.GetImage()->GetWidth(), 340);

		document.Undo();
		BOOST_CHECK_EQUAL(image.GetImage()->GetHeight(), 760);
		BOOST_CHECK_EQUAL(image.GetImage()->GetWidth(), 540);

		document.Redo();
		BOOST_CHECK_EQUAL(image.GetImage()->GetHeight(), 560);
		BOOST_CHECK_EQUAL(image.GetImage()->GetWidth(), 340);
	}

	BOOST_AUTO_TEST_CASE(should_not_delete_image_file_when_undo_inserting)
	{
		document.InsertImage("images/shrek.jpg", 540, 760);
		std::string imagePath = document.GetItem(0).GetImage()->GetPath().string();
		document.Undo();

		BOOST_CHECK(std::filesystem::exists(imagePath));
	}

	BOOST_AUTO_TEST_CASE(should_delete_image_copy_when_insert_command_was_deleted)
	{
		document.InsertImage("images/shrek.jpg", 540, 760);
		std::string imagePath = document.GetItem(0).GetImage()->GetPath().string();

		document.Undo();
		document.InsertParagraph("some text");

		BOOST_CHECK(!std::filesystem::exists(imagePath));
	}

	BOOST_AUTO_TEST_CASE(should_delete_first_command_when_history_size_more_than_10)
	{
		for (size_t i = 0; i < 11; i++)
		{
			document.Undo();
		}

		BOOST_CHECK(!document.CanUndo());
		BOOST_CHECK_EQUAL(document.GetTitle(), "0");
	}

	BOOST_AUTO_TEST_CASE(should_delete_unexecuted_commands_when_new_is_inserting)
	{
		BOOST_CHECK_EQUAL(document.GetTitle(), "10");

		for (size_t i = 0; i < 11; i++)
		{
			document.Undo();
		}

		BOOST_CHECK(document.CanRedo());
		document.InsertParagraph("some text");
		BOOST_CHECK(!document.CanRedo());
	}
BOOST_AUTO_TEST_SUITE_END()