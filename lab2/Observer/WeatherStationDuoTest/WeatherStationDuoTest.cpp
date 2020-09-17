#include "stdafx.h"
#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"

BOOST_AUTO_TEST_SUITE(weather_station_test)

	BOOST_AUTO_TEST_CASE(CDisplay_test)
	{
		CWeatherData wdIn;
		CWeatherData wdOut;
		std::stringstream output;
		std::string expectedOutput;

		CDisplay obs(wdIn, wdOut, output);

		wdIn.RegisterObserver(obs, 1);
		wdOut.RegisterObserver(obs, 1);

		wdOut.SetMeasurements(4, 2, 800);
		expectedOutput = "External info\nCurrent Temp 4\nCurrent Hum 2\nCurrent Pressure 800\n----------------\n";
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);

		output.str(std::string());
		wdIn.SetMeasurements(80, 5, 760);
		expectedOutput = "Internal info\nCurrent Temp 80\nCurrent Hum 5\nCurrent Pressure 760\n----------------\n";
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	BOOST_AUTO_TEST_CASE(CStatsdDisplay_test)
	{
		CWeatherData wdIn;
		CWeatherData wdOut;
		std::stringstream output;
		std::string expectedOutput;

		CStatsDisplay obs(wdIn, wdOut, output);

		wdIn.RegisterObserver(obs, 1);
		wdOut.RegisterObserver(obs, 1);

		wdOut.SetMeasurements(4, 2, 800);

		expectedOutput = "External temperature stats\nMax 4.000000\nMin 4.000000\nAverage 4.000000\n----------------\n";
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);

		output.str(std::string());

		wdOut.SetMeasurements(10, 2, 800);
		expectedOutput = "External temperature stats\nMax 10.000000\nMin 4.000000\nAverage 7.000000\n----------------\n";
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);

		output.str(std::string());
		wdIn.SetMeasurements(10, 2, 800);
		expectedOutput = "Internal temperature stats\nMax 10.000000\nMin 10.000000\nAverage 10.000000\n----------------\n";
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

BOOST_AUTO_TEST_SUITE_END();