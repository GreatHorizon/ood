#include "WeatherData.h"

int main()
{
	CWeatherData wd;
	CStatsDisplay obs;
	wd.RegisterObserver(obs, 1);

	wd.SetMeasurements(4, 8, 800, 20, 350);

	return 0;
}