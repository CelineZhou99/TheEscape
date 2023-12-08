#include "stdafx.h"
#include "Publisher.h"

void Publisher::Subscribe(Subscriber* subscriber)
{
	_subscriber_list.push_back(subscriber);
}

void Publisher::Unsubscribe(Subscriber* subscriber)
{
	_subscriber_list.remove(subscriber);
}

void Publisher::NotifySubscribers()
{
	std::list<Subscriber*>::iterator iterator = _subscriber_list.begin();
	while (iterator != _subscriber_list.end())
	{
		(*iterator)->Update();
		++iterator;
	}
}
