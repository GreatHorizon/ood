#include "stdafx.h"
#include "../DocumentEditor/Document.h"

BOOST_AUTO_TEST_SUITE(DocumentTest)

	struct EmptyDocument
	{
		CDocument document;
	};

	BOOST_FIXTURE_TEST_SUITE(when_creating_empty_document, EmptyDocument)
		BOOST_AUTO_TEST_CASE(items_count_should_be_zero)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(title_should_be_empty_string)
		{
			BOOST_CHECK_EQUAL(document.GetTitle(), "");
		}

		BOOST_AUTO_TEST_CASE(cant_redo_command)
		{
			BOOST_CHECK(!document.CanRedo());
		}

		BOOST_AUTO_TEST_CASE(cant_undo_command)
		{
			BOOST_CHECK(!document.CanUndo());
		}

		BOOST_AUTO_TEST_CASE(can_set_title)
		{
			document.SetTitle("New title");
			BOOST_CHECK_EQUAL(document.GetTitle(), "New title");
		}

		BOOST_AUTO_TEST_CASE(cant_insert_paragraph_into_position_more_than_size)
		{
			BOOST_CHECK_THROW(document.InsertParagraph("Some text", 2), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(cant_get_item_from_position_more_than_size)
		{
			BOOST_CHECK_THROW(document.GetItem(2), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(can_insert_element_to_end_of_list)
		{
			document.InsertParagraph("Some text at the end of list", boost::none);
			auto documentItem = document.GetItem(0);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			BOOST_CHECK_EQUAL(documentItem.GetParagraph()->GetText(), "Some text at the end of list");
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct AfterSettingTitle : EmptyDocument
	{
		AfterSettingTitle()
		{
			document.SetTitle("My new title");
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
		
	struct AfterInsertingSeveralParagraphs : EmptyDocument
	{
		AfterInsertingSeveralParagraphs()
		{
			document.InsertParagraph("1 1 1");
			document.InsertParagraph("2 2 2", 0);
			document.InsertParagraph("3 3 3", 1);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(InsertParagraphTest, AfterInsertingSeveralParagraphs)
		BOOST_AUTO_TEST_CASE(items_should_not_be_image)
		{
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage(), nullptr);
			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage(), nullptr);
			BOOST_CHECK_EQUAL(document.GetItem(2).GetImage(), nullptr);
		}

		BOOST_AUTO_TEST_CASE(items_count_should_be_3)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
		}

		BOOST_AUTO_TEST_CASE(paragraphs_should_be_in_right_order)
		{
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "2 2 2");
			BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "3 3 3");
			BOOST_CHECK_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "1 1 1");
		}

		BOOST_AUTO_TEST_CASE(can_undo_insertion)
		{
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "2 2 2");
			BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "1 1 1");

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "1 1 1");

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(can_redo_after_undo_insertion)
		{
			document.Undo();
			document.Undo();
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);

			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "1 1 1");

			document.Redo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "2 2 2");
			BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "3 3 3");
			BOOST_CHECK_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "1 1 1");
		}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(ImageInsertTest, EmptyDocument)
		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_path_is_invalid)
		{
			BOOST_CHECK_THROW(document.InsertImage(std::filesystem::path("images/invalidPath.jpg"), 340, 250), std::invalid_argument);
			BOOST_CHECK_THROW(document.InsertImage(std::filesystem::path("images/image.txt"), 340, 250), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_size_is_invalid)
		{
			BOOST_CHECK_THROW(document.InsertImage(std::filesystem::path("images/shrek.jpg"), 250999, 250), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(can_insert_correct_image)
		{
			document.InsertImage(std::filesystem::path("images/shrek.jpg"), 500, 250);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 250);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 500);
		}

		BOOST_AUTO_TEST_CASE(can_undo_and_redo_inserting)
		{
			document.InsertImage(std::filesystem::path("images/shrek.jpg"), 500, 250);
			document.InsertImage(std::filesystem::path("images/shrek.jpg"), 600, 230);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 250);
			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage()->GetHeight(), 230);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 500);
			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage()->GetWidth(), 600);

			document.Undo();
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 250);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 500);
			document.Redo();

			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage()->GetHeight(), 230);
			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage()->GetWidth(), 600);

		}

	BOOST_AUTO_TEST_SUITE_END()


	struct DocumentWithParagraphs : EmptyDocument
	{
		DocumentWithParagraphs()
		{
			document.InsertParagraph("text in first paragraph");
			document.InsertParagraph("text in second paragraph");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(ReplaceTextTest, DocumentWithParagraphs)
		BOOST_AUTO_TEST_CASE(should_replace_paragraph_text)
		{
			auto firstParagraph = document.GetItem(0);
			BOOST_CHECK_EQUAL(firstParagraph.GetParagraph()->GetText(), "text in first paragraph");
			firstParagraph.GetParagraph()->SetText("Now it is other text in first paragraph");
			BOOST_CHECK_EQUAL(firstParagraph.GetParagraph()->GetText(), "Now it is other text in first paragraph");
		}

		BOOST_AUTO_TEST_CASE(can_undo_text_setting)
		{
			auto firstParagraph = document.GetItem(0);
			firstParagraph.GetParagraph()->SetText("Now it is other text in first paragraph");

			document.Undo();
			BOOST_CHECK_EQUAL(firstParagraph.GetParagraph()->GetText(), "text in first paragraph");
		}


		BOOST_AUTO_TEST_CASE(can_redo_text_setting_after_undo)
		{
			auto firstParagraph = document.GetItem(0);
			firstParagraph.GetParagraph()->SetText("Now it is other text in first paragraph");

			document.Undo();
			document.Redo();
			BOOST_CHECK_EQUAL(firstParagraph.GetParagraph()->GetText(), "Now it is other text in first paragraph");
		}
	BOOST_AUTO_TEST_SUITE_END()
	struct DocumentWithSomeItems : EmptyDocument
	{
		DocumentWithSomeItems()
		{
			document.InsertParagraph("text in first paragraph");
			document.InsertParagraph("text in second paragraph");
			document.InsertImage("images/shrek.jpg", 540, 330);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(DeleteItemTest, DocumentWithSomeItems)
		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_position_more_than_size)
		{
			BOOST_CHECK_THROW(document.DeleteItem(5), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(can_delete_item_in_right_position)
		{
			document.DeleteItem(1);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(),"text in first paragraph");
			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage()->GetHeight(), 330);
		}


		BOOST_AUTO_TEST_CASE(can_undo_deleting_item)
		{
			document.DeleteItem(1);
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
			BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "text in second paragraph");
		}

		BOOST_AUTO_TEST_CASE(can_redo_after_undo_deleting_item)
		{
			document.DeleteItem(1);
			document.Undo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "text in first paragraph");
			BOOST_CHECK_EQUAL(document.GetItem(1).GetImage()->GetHeight(), 330);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct DocumentWithImage : EmptyDocument
	{
		DocumentWithImage()
		{
			document.InsertImage("images/shrek.jpg", 540, 330);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(ResizeImageTest, DocumentWithImage)
		BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_new_size_is_incorrect)
		{
			BOOST_CHECK_THROW(document.GetItem(0).GetImage()->Resize(9999999, 1), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(should_resize_image)
		{
			auto image = document.GetItem(0).GetImage();
			image->Resize(840, 390);

			BOOST_CHECK_EQUAL(image->GetHeight(), 390);
			BOOST_CHECK_EQUAL(image->GetWidth(), 840);
		}


		BOOST_AUTO_TEST_CASE(should_can_undo_resizing)
		{
			auto image = document.GetItem(0).GetImage();
			image->Resize(840, 390);
			document.Undo();
			BOOST_CHECK_EQUAL(image->GetHeight(), 330);
			BOOST_CHECK_EQUAL(image->GetWidth(), 540);
		}

		BOOST_AUTO_TEST_CASE(should_can_redo_after_undo_resizing)
		{
			auto image = document.GetItem(0).GetImage();
			image->Resize(840, 390);
			document.Undo();
			document.Redo();
			BOOST_CHECK_EQUAL(image->GetHeight(), 390);
			BOOST_CHECK_EQUAL(image->GetWidth(), 840);
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()