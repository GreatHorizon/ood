#include "WeatherData.h"

int main()
{
	CWeatherData wd;
	CWeatherData wd1;

	CDisplay obs;
	CDisplay obs1;

	wd.RegisterObserver(obs, std::set<EventType>{EventType::TEMPERATURE, EventType::HUMIDITY}, 1);
	wd.SetMeasurements(30, 2, 850, 14, 90);
	wd.QuitSubscription(obs, EventType::HUMIDITY);
	wd.SetMeasurements(30, 3, 850, 14, 90);

	wd.SubscribeNewEvent(obs, EventType::HUMIDITY, 1);
	wd.SetMeasurements(30, 1, 850, 14, 90);

	wd.RemoveObserver(obs);

	return 0;
}