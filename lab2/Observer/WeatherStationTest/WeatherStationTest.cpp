#include "stdafx.h"
#include "../WeatherStation/Observer.h"
#include "../WeatherStation/WeatherData.h"

BOOST_AUTO_TEST_SUITE(weather_station_test)

	BOOST_AUTO_TEST_CASE(observer_priority_test)
	{
		CWeatherData wd;
		std::stringstream output;
		std::string expectedOutput = "Now updating observer John\nNow updating observer Dan\nNow updating observer Sarah\n";

		CPriorityObserver obs1("Dan", output);
		CPriorityObserver obs2("Sarah", output);
		CPriorityObserver obs3("John", output);
		
		wd.RegisterObserver(obs1, 5);
		wd.RegisterObserver(obs2, 0);
		wd.RegisterObserver(obs3, 100);
		wd.SetMeasurements(4, 2, 800);
		
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	BOOST_AUTO_TEST_CASE(removing_observer_test)
	{
		CWeatherData wd;
		CRemovingObserver obs1(wd);
		CRemovingObserver obs2(wd);

		wd.RegisterObserver(obs1, 1);
		wd.RegisterObserver(obs2, 1);

		wd.SetMeasurements(4, 2, 800);
	}

BOOST_AUTO_TEST_SUITE_END();