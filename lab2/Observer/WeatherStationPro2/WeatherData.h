#pragma once
#define _USE_MATH_DEFINES
#include "Observer.h"
#include<math.h>
#include <iostream>
#include <string>

struct SWindInfo
{
	double m_windSpeed = 0;
	double m_windDirection = 0;
};

struct SWeatherInfo
{
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 0;
	SWindInfo m_windInfo;
};

class CDisplay : public IObserver<Event*>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(Event* event) override
	{
		std::string mesurementName;
		EventType type = event->GetType();

		switch (type)
		{
		case EventType::TEMPERATURE:
			mesurementName = "Temperature";
			break;
		case EventType::HUMIDITY:
			mesurementName = "Humidity";
			break;
		case EventType::PRESSURE:
			mesurementName = "Pressure";
			break;
		case EventType::WINDSPEED:
			mesurementName = "Wind speed";
			break;
		case EventType::WINDDIRECTION:
			mesurementName = "Wind directiron";
			break;
		}

		std::cout << "Current " << mesurementName << " is "<<event->GetData() << "\n";
	}
};

class DirectionSensorStats
{
public:
	std::string ToString()
	{
		double angle = ToDegrees(atan2(AverageDirection.y, AverageDirection.x));

		if (angle < 0)
		{
			angle += 360;
		}

		return "Average wind direction " + std::to_string(angle) + "\n";
	}

	void CalculateStatsInfo(double directionAngle)
	{
		AverageDirection.y += sin(ToRadians(directionAngle));
		AverageDirection.x += cos(ToRadians(directionAngle));
	}

	struct SProportion
	{
		double x = 0;
		double y = 0;
	};

private:
	double ToRadians(double angle)
	{
		return angle * M_PI / 180;
	}

	double ToDegrees(double angle)
	{
		return angle * 180 / M_PI;
	}

	SProportion AverageDirection;
};

class CStatsDisplay : public IObserver<Event*>
{
private:
	class SensorStatsInfo
	{
	public:
		void CalculateStatsInfo(double newValue)
		{
			if (m_minSensorValue > newValue)
			{
				m_minSensorValue = newValue;
			}

			if (m_maxSensorValue < newValue)
			{
				m_maxSensorValue = newValue;
			}

			m_accSensorValue += newValue;
			++m_countAcc;
		}

		std::string ToString()
		{
			return "Max " + std::to_string(m_maxSensorValue) + "\n"
				+ "Min " + std::to_string(m_minSensorValue) + "\n"
				+ "Average " + std::to_string(m_accSensorValue / m_countAcc) + "\n";
		}

	private:
		double m_minSensorValue = std::numeric_limits<double>::infinity();
		double m_maxSensorValue = -std::numeric_limits<double>::infinity();
		double m_accSensorValue = 0;
		unsigned m_countAcc = 0;
	};

	void Update(Event* event) override
	{
		std::string mesurementName;
		EventType type = event->GetType();
		SensorStatsInfo currentStats;

		switch (type)
		{
		case EventType::TEMPERATURE: 
			m_tempStats.CalculateStatsInfo(event->GetData());
			std::cout << "Temperature\n" << m_tempStats.ToString() << "----------------\n";
			break;
		case EventType::HUMIDITY:
			m_humStats.CalculateStatsInfo(event->GetData());
			std::cout << "Humidity\n" << m_humStats.ToString() << "----------------\n";
			break;
		case EventType::PRESSURE:
			m_pressureStats.CalculateStatsInfo(event->GetData());
			std::cout << "Pressure\n" << m_pressureStats.ToString() << "----------------\n";
			break;
		case EventType::WINDSPEED:
			m_windSpeedStats.CalculateStatsInfo(event->GetData());
			std::cout << "Wind speed\n" << m_windSpeedStats.ToString() << "----------------\n";
			break;
		case EventType::WINDDIRECTION:
			m_windDirectionStats.CalculateStatsInfo(event->GetData());
			std::cout << "Wind direction\n" << m_windDirectionStats.ToString() << "----------------\n";
			break;
		}

	}

	SensorStatsInfo m_tempStats;
	SensorStatsInfo m_humStats;
	SensorStatsInfo m_pressureStats;
	SensorStatsInfo m_windSpeedStats;
	DirectionSensorStats m_windDirectionStats;
};


class CWeatherData : public CObservable<SWeatherInfo, Event*>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindDirection() const
	{
		return m_windInfo.m_windDirection;
	}

	double GetWindSpeed() const
	{
		return m_windInfo.m_windSpeed;
	}

	void MeasurementsChanged(std::set<Event*> const& changedEvents)
	{
		NotifyObservers(changedEvents);
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		std::set<Event*> changedEvents;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			changedEvents.insert(&HumidityChanged(humidity));
		}

		if (m_temperature != temp)
		{
			m_temperature = temp;
			changedEvents.insert(&TemperatureChanged(temp));
		}

		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			changedEvents.insert(&PressureChanged(pressure));
		}

		if (m_windInfo.m_windSpeed != windSpeed)
		{
			m_windInfo.m_windSpeed = windSpeed;
			changedEvents.insert(&WindSpeedChanged(windSpeed));
		}

		if (m_windInfo.m_windDirection != windDirection)
		{
			m_windInfo.m_windDirection = windDirection;
			changedEvents.insert(&WindDirectionChanged(windDirection));
		}
		
		MeasurementsChanged(changedEvents);
	}

protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.m_temperature = GetTemperature();
		info.m_humidity = GetHumidity();
		info.m_pressure = GetPressure();
		info.m_windInfo = m_windInfo;
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_windInfo;

};

