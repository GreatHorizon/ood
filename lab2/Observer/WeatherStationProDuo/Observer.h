#pragma once
#include <set>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T> const& observable) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{
			if (it->second == &observer)
			{
				return;
			}
		}

		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		auto observers = m_observers;
		T data = GetChangedData();
		for (auto it = observers.rbegin(); it != observers.rend(); it++)
		{
			it->second->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it);
				break;
			}
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::multimap<unsigned, ObserverType*> m_observers;
};

