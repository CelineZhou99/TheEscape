#pragma once

#include "ISubscriber.h"
#include <list>

class Publisher
{
public:
	void Subscribe(ISubscriber* subscriber);
	void Unsubscribe(ISubscriber* subscriber);
	void NotifySubscribers();

protected:
	std::list<ISubscriber*> _subscriber_list;
};

