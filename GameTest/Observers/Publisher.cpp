#include "stdafx.h"
#include "Publisher.h"

void Publisher::Subscribe(ISubscriber* subscriber)
{
	_subscriber_list.push_back(subscriber);
}

void Publisher::Unsubscribe(ISubscriber* subscriber)
{
	_subscriber_list.remove(subscriber);
}

void Publisher::NotifySubscribers()
{
	for (ISubscriber* subscriber : _subscriber_list)
	{
		subscriber->Update();
	}
}
