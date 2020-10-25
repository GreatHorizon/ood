#include "stdafx.h"
#include "../DocumentEditor/Image.h"
#include "CMockHistoryAdapted.h"

struct ImageFixture
{
	std::stringstream out;
	std::unique_ptr<CMockHistoryAdapter> adapter;
	std::unique_ptr<CImage> image;

	ImageFixture()
	{
		adapter = std::make_unique<CMockHistoryAdapter>(out);
		image = std::make_unique<CImage>(std::move(adapter), std::filesystem::path("images/shrek.jpg"), 340, 250);
	}
};

BOOST_FIXTURE_TEST_SUITE(ImageTest, ImageFixture)
	BOOST_AUTO_TEST_CASE(can_get_height)
	{
		BOOST_CHECK_EQUAL(image->GetHeight(), 340);
	}

	BOOST_AUTO_TEST_CASE(can_get_width)
	{
		BOOST_CHECK_EQUAL(image->GetWidth(), 250);
	}

	BOOST_AUTO_TEST_CASE(should_be_in_image_directory)
	{
		BOOST_CHECK(std::filesystem::exists(image->GetPath()));
	}


	BOOST_AUTO_TEST_CASE(should_add_resize_command_to_hisoty_after_resize)
	{	
		image->Resize(330, 780);
		BOOST_CHECK_EQUAL(out.str(), "Command saved and executed\n");
	}

BOOST_AUTO_TEST_SUITE_END()




