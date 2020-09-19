
#include "WeatherData.h"
int main()
{

	CWeatherData wd1;
	CWeatherData wd2;

	CDisplay obs(wd1, wd2, std::cout);
	CStatsDisplay obs1(wd1, wd2, std::cout);

	wd1.RegisterObserver(obs, 1);
	wd2.RegisterObserver(obs, 1);

	wd1.RegisterObserver(obs1, 1);
	wd2.RegisterObserver(obs1, 1);


	wd1.SetMeasurements(20, 10, 800);
	wd2.SetMeasurements(30, 5, 780);
	wd1.SetMeasurements(30, 5, 780);
	return 0;
}