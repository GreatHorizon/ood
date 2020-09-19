#pragma once

#include "Observer.h"
#include <iostream>
#include <string>

struct SWeatherInfo
{
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 0;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
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
	SWeatherInfo GetChangedData()const override
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

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(CWeatherData const& wdIn, CWeatherData const& wdOut, std::ostream& outStream)
		: m_wdIn(wdIn)
		, m_wdOut(wdOut)
		, m_outStream(outStream)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		CWeatherData sourceInfo;
		if (&observable == &m_wdIn)
		{
			m_outStream << "Internal info\n";
		}
		else
		{
			m_outStream << "External info\n";
		}

		m_outStream << "Current Temp " << data.m_temperature << "\n";
		m_outStream << "Current Hum " << data.m_humidity << "\n";
		m_outStream << "Current Pressure " << data.m_pressure << "\n";
		m_outStream << "----------------" << "\n";
	}

	const CWeatherData& m_wdIn;
	const CWeatherData& m_wdOut;
	std::ostream& m_outStream;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(CWeatherData const& wdIn, CWeatherData const& wdOut, std::ostream& outStream)
		: m_wdIn(wdIn)
		, m_wdOut(wdOut)
		, m_outStream(outStream)
	{
	}
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


	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_wdIn)
		{
			m_internalTempStats.CalculateStatsInfo(data.m_temperature);
			m_outStream << "Internal temperature stats\n";
			m_outStream << m_internalTempStats.ToString() << "----------------\n";
		}
		else
		{
			m_externalTempStats.CalculateStatsInfo(data.m_temperature);
			m_outStream << "External temperature stats\n";
			m_outStream << m_externalTempStats.ToString() << "----------------\n";
		}
	}

	SensorStatsInfo m_internalTempStats;
	SensorStatsInfo m_externalTempStats;

	const CWeatherData& m_wdIn;
	const CWeatherData& m_wdOut;
	std::ostream& m_outStream;

};