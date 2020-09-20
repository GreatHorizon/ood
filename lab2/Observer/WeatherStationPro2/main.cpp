#include "WeatherData.h"

int main()
{
	CWeatherData wd;
	CWeatherData wd1;

	CDisplay obs;
	CDisplay obs1;

	wd.RegisterObserver(obs, std::set<Event>{Event::WindSpeed}, 1);
	wd1.RegisterObserver(obs1, std::set<Event>{Event::Temperature}, 1);
	
	wd.SetMeasurements(30, 2, 850, 14, 90);
	wd.SetMeasurements(30, 2, 850, 15, 90);

	wd.SubscribeNewEvent(obs, Event::Temperature);
	wd.SetMeasurements(50, 2, 850, 15, 90);

	wd.RemoveObserver(obs);
	wd.SetMeasurements(50, 2, 850, 15, 90);

	wd1.SetMeasurements(30, 2, 850, 14, 180);
	wd1.QuitSubscription(obs1, Event::Pressure);
	wd1.SetMeasurements(31, 2, 850, 14, 270);

	return 0;
}