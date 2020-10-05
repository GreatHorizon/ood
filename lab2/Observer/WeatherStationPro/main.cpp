#include "WeatherData.h"

int main()
{
	CWeatherData wd;
	CWeatherData wd1;

	CStatsDisplay obs;

	wd.RegisterObserver(obs, 1);
	wd.SetMeasurements(30, 2, 850, 15, 90);
	wd.SetMeasurements(30, 2, 850, 15, 180);
	wd.SetMeasurements(30, 2, 850, 15, 0);

	return 0;
}