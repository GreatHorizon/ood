#include "stdafx.h"
#include "../DocumentEditor/Editor.h"



struct EditorTestFixture
{
	std::stringstream input;
	std::stringstream output;
	CEditor editor;

	EditorTestFixture()
		: editor(input, output)
	{
	}

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		output = std::stringstream();
		input = std::stringstream(command);
		editor.Start();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
		output.str("");
	}
};

std::string GetSetOfInstructions()
{
	std::stringstream ss;
	ss << "Commands list:\n"
		<< "  help: Help\n"
		<< "  exit: Exit\n"
		<< "  setTitle: Changes title. Args: <new title>\n"
		<< "  list: Show document\n"
		<< "  undo: Undo command\n"
		<< "  redo: Redo undone command\n"
		<< "  insertParagraph: Inserts paragraph. Args: <position> | end <text>\n"
		<< "  insertImage: Inserts image. Args: <position> | end <width> <height> <path>\n"
		<< "  replaceText: Replace text. Args: <position> <text>\n"
		<< "  deleteItem: Delete item. Args: <position>\n"
		<< "  resizeImage: Resize image. Args: <position> <width> <height>\n"
		<< "  save: Save document. Args: <path>\n"
		<< ">";

	return ss.str();
}

BOOST_FIXTURE_TEST_SUITE(EditorTest, EditorTestFixture)
	BOOST_AUTO_TEST_SUITE(SetTitleCommandTest)

		BOOST_AUTO_TEST_CASE(cant_set_empty_title)
		{
			VerifyCommandHandling("setTitle", GetSetOfInstructions() + "Command arguments should not be empty\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_set_non_empty_title)
		{
			VerifyCommandHandling("setTitle title", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + "Title: title\n>");
		}
		
	BOOST_AUTO_TEST_SUITE_END();
	BOOST_AUTO_TEST_SUITE(InsertParagraphCommandTest)

		BOOST_AUTO_TEST_CASE(cant_insert_paragraph_into_incorrect_positon)
		{
			VerifyCommandHandling("insertParagraph 999999 text", GetSetOfInstructions() + "Position is out of range\n>");
		}

		BOOST_AUTO_TEST_CASE(can_insert_paragraph_in_right_position)
		{
			VerifyCommandHandling("insertParagraph end text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + "0. Paragraph: text\n>");
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(ReplaceTextCommandTest)
		BOOST_AUTO_TEST_CASE(cant_replace_text_in_paragraph_in_incorrect_positon)
		{
			VerifyCommandHandling("replaceText 999999 text", GetSetOfInstructions() + "Invalid item index\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_replace_text_in_item_if_it_is_not_paragraph)
		{
			VerifyCommandHandling("insertImage end 550 380 images/shrek.jpg", GetSetOfInstructions() + ">");
			VerifyCommandHandling("replaceText 0 text", GetSetOfInstructions() + "Item in this position is not paragraph\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_replace_text_in_item_with_no_argument)
		{
			VerifyCommandHandling("replaceText", GetSetOfInstructions() + "Incorrect arguments\n>");
		}

		BOOST_AUTO_TEST_CASE(can_replace_text_in_paragraph)
		{
			VerifyCommandHandling("insertParagraph end text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("replaceText 0 newText", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + "0. Paragraph: newText\n>");
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(DeleteItemCommandTest)
		BOOST_AUTO_TEST_CASE(cant_delete_element_with_no_arguments)
		{
			VerifyCommandHandling("deleteItem", GetSetOfInstructions() + "Incorrect argument\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_delete_element_with_in)
		{
			VerifyCommandHandling("insertParagraph end text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + "0. Paragraph: text\n>");
			VerifyCommandHandling("deleteItem 0", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + ">");
		}
	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_SUITE(UndoCommandTest)
		BOOST_AUTO_TEST_CASE(cant_undo_if_there_is_nothing_to_undo)
		{
			VerifyCommandHandling("undo", GetSetOfInstructions() + "Can't undo\n>");
		}

		BOOST_AUTO_TEST_CASE(can_undo)
		{
			VerifyCommandHandling("insertParagraph end text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("undo", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + ">");
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(RedoCommandTest)
		BOOST_AUTO_TEST_CASE(cant_redo_if_there_is_nothing_to_redo)
		{
			VerifyCommandHandling("redo", GetSetOfInstructions() + "Can't redo\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_delete_element_with_in)
		{
			VerifyCommandHandling("insertParagraph end text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("undo", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + ">");
			VerifyCommandHandling("redo", GetSetOfInstructions() + ">");
			VerifyCommandHandling("list", GetSetOfInstructions() + "0. Paragraph: text\n>");
		}

	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_SUITE(InsertImageCommandTest)

		BOOST_AUTO_TEST_CASE(cant_insert_image_into_incorrect_positon)
		{
			VerifyCommandHandling("insertImage 999999 550 380 images/shrek.jpg", GetSetOfInstructions() + "Position is out of range\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_insert_image_with_no_arguments)
		{
			VerifyCommandHandling("insertImage end 380 images/shrek.jpg", GetSetOfInstructions() + "Incorrect arguments\n>");
		}

		BOOST_AUTO_TEST_CASE(can_insert_image_in_right_position)
		{
			VerifyCommandHandling("insertImage end 550 380 images/shrek.jpg", GetSetOfInstructions() + ">");
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(ResizeImageTest)
		BOOST_AUTO_TEST_CASE(cant_resize_image_with_no_arguments)
		{
			VerifyCommandHandling("resizeImage end 380 images/shrek.jpg", GetSetOfInstructions() + "Incorrect arguments\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_resize_item_if_it_is_not_image)
		{
			VerifyCommandHandling("insertParagraph end text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("resizeImage 0 380 540", GetSetOfInstructions() + "Item in this position is not image\n>");
		}

		BOOST_AUTO_TEST_CASE(cant_resize_image_with_incorrect_size)
		{
			VerifyCommandHandling("insertImage end 550 380 images/shrek.jpg", GetSetOfInstructions() + ">");
			VerifyCommandHandling("resizeImage 0 38000000 540", GetSetOfInstructions() + "Incorrect image size\n>");
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(SaveDocumentTest)
		BOOST_AUTO_TEST_CASE(cant_save_to_incorrect_path)
		{
			VerifyCommandHandling("save invalidPath", GetSetOfInstructions() + "Invalid path\n>");
		}

		BOOST_AUTO_TEST_CASE(can_save_html_file)
		{
			if (!std::filesystem::exists("document"))
			{
				std::filesystem::create_directory("document");
			}

			VerifyCommandHandling("insertImage end 550 380 images/shrek.jpg", GetSetOfInstructions() + ">");
			VerifyCommandHandling("insertParagraph end sooooooooooooooooome&<>'`\" text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("insertParagraph end another paragraph text", GetSetOfInstructions() + ">");
			VerifyCommandHandling("setTitle mytitle", GetSetOfInstructions() + ">");

			VerifyCommandHandling("save document", GetSetOfInstructions() + ">");

			BOOST_CHECK(std::filesystem::exists("document/images"));
			BOOST_CHECK(std::filesystem::exists("document/index.html"));

			if (std::filesystem::exists("document"))
			{
				std::filesystem::remove_all("document");
			}
		}
	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();