#include "stdafx.h"
#include "Slime.h"

void Slime::BehaviourTreeInit()
{
	_behaviour_tree = std::make_shared<BehaviourTree>(RootNodeType::SEQUENCE);
	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::SayHello, this));
	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::SayBye, this));
}

void Slime::MoveTo(Vector2D location)
{
}

void Slime::MoveTo(Player* player)
{
}

BehaviourNodeState Slime::SayHello()
{
	std::wstringstream wss;
	wss << L" hello\n";
	OutputDebugString(wss.str().c_str());
	return BehaviourNodeState::SUCCESS;
}

BehaviourNodeState Slime::SayBye()
{
	std::wstringstream wss;
	wss << L" bye\n";
	OutputDebugString(wss.str().c_str());
	return BehaviourNodeState::SUCCESS;
}
