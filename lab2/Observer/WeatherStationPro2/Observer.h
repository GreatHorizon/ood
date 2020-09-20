#pragma once
#include <set>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

enum class Event
{
	TEMPERATURE, 
	HUMIDITY, 
	PRESSURE,
	WINDSPEED, 
	WINDDIRECTION
};

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, std::set<Event> const& events, int priority) = 0;
	virtual void NotifyObservers(std::set<Event> const& changedEvents) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, std::set<Event> const& events, int priority) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{
			if (it->second == &observer)
			{
				return;
			}
		}

		m_observers.emplace(priority, &observer);
		m_observersEvents.emplace(&observer, events);
	}

	void NotifyObservers(std::set<Event> const& changedEvents) override
	{
		T data = GetChangedData();
		auto observers = m_observers;

		for (auto it = observers.rbegin(); it != observers.rend(); it++)
		{
			if (IsEventSubscriber(it->second, changedEvents))
			{
				it->second->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it);
				m_observersEvents.erase(m_observersEvents.find(&observer));
				return;
			}
		}
	}

	void SubscribeNewEvent(ObserverType& observer, Event const& newEvent)
	{
		auto it = m_observersEvents.find(&observer);
		if (it != m_observersEvents.end())
		{
			it->second.insert(newEvent);
		}
	}

	void QuitSubscription(ObserverType& observer, Event const& removingEvent)
	{
		auto it = m_observersEvents.find(&observer);
		if (it != m_observersEvents.end())
		{
			it->second.erase(removingEvent);
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:

	bool IsEventSubscriber(ObserverType* observer, std::set<Event> const& events)
	{
		auto foundSubscriber = m_observersEvents.find(observer);
		return std::any_of(events.begin(), events.end(), [&](Event event)
			{
				return foundSubscriber->second.find(event) != foundSubscriber->second.end();
			}
		);
	}

	std::multimap<unsigned, ObserverType*> m_observers;
	std::map<ObserverType*, std::set<Event>> m_observersEvents;
};

