#pragma once

#include "Subscriber.h"
#include <list>

class Publisher
{
public:
	void Subscribe(Subscriber* subscriber);
	void Unsubscribe(Subscriber* subscriber);
	void NotifySubscribers();

protected:
	std::list<Subscriber*> _subscriber_list;
};

