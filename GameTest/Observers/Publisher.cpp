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
	for (Subscriber* subscriber : _subscriber_list)
	{
		subscriber->Update();
	}
}
