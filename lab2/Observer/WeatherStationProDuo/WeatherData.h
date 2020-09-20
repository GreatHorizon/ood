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

class CProStats
{
public:
	void UpdateStats(SWeatherInfo const& data)
	{
		m_tempStats.CalculateStatsInfo(data.m_temperature);
		m_humStats.CalculateStatsInfo(data.m_humidity);
		m_pressureStats.CalculateStatsInfo(data.m_pressure);
		m_windSpeedStats.CalculateStatsInfo(data.m_windInfo.m_windSpeed);
		m_windDirectionStats.CalculateStatsInfo(data.m_windInfo.m_windDirection);
	}

	void ShowStats()
	{
		std::cout << "Temperature\n" << m_tempStats.ToString() << "----------------\n";
		std::cout << "Humidity\n" << m_humStats.ToString() << "----------------\n";
		std::cout << "Pressure\n" << m_pressureStats.ToString() << "----------------\n";
		std::cout << "Wind speed\n" << m_windSpeedStats.ToString() << "----------------\n";
		std::cout << "Wind direction\n" << m_windDirectionStats.ToString() << "----------------\n";
	}

private:
	SensorStatsInfo m_tempStats;
	SensorStatsInfo m_humStats;
	SensorStatsInfo m_pressureStats;
	SensorStatsInfo m_windSpeedStats;
	DirectionSensorStats m_windDirectionStats;
};

class CStats
{
public:
	void UpdateStats(SWeatherInfo const& data)
	{
		m_tempStats.CalculateStatsInfo(data.m_temperature);
		m_humStats.CalculateStatsInfo(data.m_humidity);
		m_pressureStats.CalculateStatsInfo(data.m_pressure);
	}

	void ShowStats()
	{
		std::cout << "Temperature\n" << m_tempStats.ToString() << "----------------\n";
		std::cout << "Humidity\n" << m_humStats.ToString() << "----------------\n";
		std::cout << "Pressure\n" << m_pressureStats.ToString() << "----------------\n";
	}
private:
	SensorStatsInfo m_tempStats;
	SensorStatsInfo m_humStats;
	SensorStatsInfo m_pressureStats;
};

class CProWeatherData : public CObservable<SWeatherInfo>
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

	SWindInfo GetWindInfo() const
	{
		return m_windInfo;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		SWindInfo info;
		info.m_windDirection = windDirection;
		info.m_windSpeed = windSpeed;
		m_windInfo = info;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.m_temperature = GetTemperature();
		info.m_humidity = GetHumidity();
		info.m_pressure = GetPressure();
		info.m_windInfo = GetWindInfo();

		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_windInfo;
};

class CWeatherData : public CObservable<SWeatherInfo>
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.m_temperature = GetTemperature();
		info.m_humidity = GetHumidity();
		info.m_pressure = GetPressure();

		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
}; 

class CProStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CProStatsDisplay(CWeatherData const& wdIn, CProWeatherData const& wdOut)
		: m_wdIn(wdIn)
		, m_wdOut(wdOut)
	{
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_wdIn)
		{
			m_internalStats.UpdateStats(data);
			std::cout << "Internal statistic:\n";
			m_internalStats.ShowStats();
		}
		else
		{
			m_externalStats.UpdateStats(data);
			std::cout << "External statistic:\n";
			m_externalStats.ShowStats();
		}
	}

	CStats m_internalStats;
	CProStats m_externalStats;

	const CWeatherData& m_wdIn;
	const CProWeatherData& m_wdOut;
};