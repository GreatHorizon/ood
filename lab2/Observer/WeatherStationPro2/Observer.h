#pragma once
#include <set>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

enum class EventType
{
	TEMPERATURE, 
	HUMIDITY, 
	PRESSURE,
	WINDSPEED, 
	WINDDIRECTION
};

class Event
{
public:
	EventType GetType() const
	{
		return m_type;
	}
	virtual ~Event() = default;

	double GetData() const
	{
		return m_data;
	}
protected:
	Event(EventType type, double data)
		: m_type(type)
		, m_data(data)
	{
	}

	EventType m_type;
	double m_data;
};

class TemperatureChanged : public Event
{
public:
	TemperatureChanged(double data)
		: Event(EventType::TEMPERATURE, data)

	{
	}

};

class HumidityChanged : public Event
{
public:
	HumidityChanged(double data)
		: Event(EventType::HUMIDITY, data)
	{
	}

};

class PressureChanged : public Event
{
public:
	PressureChanged(double data)
		: Event(EventType::PRESSURE, data)
	{
	}

};

class WindSpeedChanged : public Event
{
public:
	WindSpeedChanged(double data)
		: Event(EventType::WINDSPEED, data)

	{
	}
};

class WindDirectionChanged : public Event
{
public:
	WindDirectionChanged(double data)
		: Event(EventType::WINDDIRECTION, data)
	{
	}
};

template <typename Event>
class IObserver
{
public:
	virtual void Update(Event event) = 0;
	virtual ~IObserver() = default;
};

template <typename T, typename Event>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<Event>& observer, std::set<EventType> const& events, int priority) = 0;
	virtual void NotifyObservers(std::set<Event> const& changedEvents) = 0;
	virtual void RemoveObserver(IObserver<Event>& observer) = 0;
};

template <class T, class Event>
class CObservable : public IObservable<T, Event>
{
public:
	typedef IObserver<Event> ObserverType;

	void RegisterObserver(ObserverType& observer, std::set<EventType> const& events, int priority) override
	{
		for (auto event : events)
		{
			SubscribeNewEvent(observer, event, priority);
		}
	}

	bool AlreadySubscribed(std::multimap<unsigned, ObserverType*> observers, ObserverType& observer)
	{
		for (auto it = observers.begin(); it != observers.end(); it++)
		{
			if (it->second == &observer)
			{
				return true;
			}
		}

		return false;
	}

	void NotifyObservers(std::set<Event> const& changedEvent) override
	{
		for (auto event : changedEvent)
		{
			auto it = m_observersEvent.find(event->GetType());
			if (it != m_observersEvent.end())
			{
				auto observers = it->second;
				for (auto i = observers.rbegin(); i != observers.rend(); i++)
				{
					i->second->Update(event);
				}
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observersEvent.begin(); it != m_observersEvent.end(); it++)
		{
			QuitSubscription(observer, it->first);
		}
	}

	void SubscribeNewEvent(ObserverType& observer, EventType newEvent, int priority)
	{
		auto it = m_observersEvent.find(newEvent);

		if (it == m_observersEvent.end())
		{
			std::multimap<unsigned, ObserverType*> observersMap = { {priority, &observer} };
			m_observersEvent.emplace(newEvent, observersMap);
		}
		else
		{
			if (!AlreadySubscribed(it->second, observer))
			{
				it->second.emplace(priority, &observer);
			}
		}
	}

	void QuitSubscription(ObserverType& observer, EventType const& removingEvent)
	{
		auto it = m_observersEvent.find(removingEvent);
		if (it != m_observersEvent.end())
		{
			for (auto iterator = it->second.begin(); iterator != it->second.end(); iterator++)
			{
				if (iterator->second = &observer)
				{
					it->second.erase(iterator);
					return;
				}
			}
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::map<EventType, std::multimap<unsigned, ObserverType*>> m_observersEvent;
};

