#include "WeatherData.h"

int main()
{
	CWeatherData wd1;
	CProWeatherData wd2;

	CProStatsDisplay obs(wd1, wd2);

	wd1.RegisterObserver(obs, 1);
	wd2.RegisterObserver(obs, 1);

	wd1.SetMeasurements(45, 2, 780);
	wd2.SetMeasurements(30, 1, 800, 7, 80);

	return 0;
}