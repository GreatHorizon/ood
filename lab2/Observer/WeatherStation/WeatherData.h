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

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.m_temperature << "\n";
		std::cout << "Current Hum " << data.m_humidity << "\n";
		std::cout << "Current Pressure " << data.m_pressure << "\n";
		std::cout << "----------------" << "\n";
	}
};	

class CRemovingObserver : public IObserver<SWeatherInfo>
{
public:
	CRemovingObserver(CObservable<SWeatherInfo>& observable)
		: m_observable(&observable)
	{}
private:
	void Update(SWeatherInfo const& data) override
	{
		m_observable->RemoveObserver(*this);
		std::cout << "This observer has removed subscription in update method\n";
	}

	CObservable<SWeatherInfo>* m_observable;
};

class CPriorityObserver : public IObserver<SWeatherInfo>
{
public:
	CPriorityObserver(std::string name, std::ostream& stream)
		: m_name(name)
		, m_outStream(stream)
	{}

	void Update(SWeatherInfo const& data) override
	{
		m_outStream << "Now updating observer " << m_name << "\n";
	}

private:
	std::string m_name;
	std::ostream& m_outStream;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
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
		std::string m_sensorName;
	};


	void Update(SWeatherInfo const& data) override
	{
		m_tempStats.CalculateStatsInfo(data.m_temperature);
		m_humStats.CalculateStatsInfo(data.m_humidity);
		m_pressureStats.CalculateStatsInfo(data.m_pressure);

		std::cout << "Temperature\n" << m_tempStats.ToString() << "----------------\n";
		std::cout << "Humidity\n" << m_humStats.ToString() << "----------------\n";
		std::cout << "Pressure\n" << m_pressureStats.ToString() << "----------------\n";
	}
	
	SensorStatsInfo m_tempStats;
	SensorStatsInfo m_humStats;
	SensorStatsInfo m_pressureStats;
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

