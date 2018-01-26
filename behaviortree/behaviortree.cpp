#include "stdafx.h"
#include "behaviortree.h"
#include <tinyxml.h>
#include "behavior.h"
#include "group.h"
#include "selector.h"
#include "sequence.h"

bool BehaviorTree::ReadBehaviorTreeFile(const char* filename)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Couldn't read state machine from %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Invalid format for %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);
	TiXmlHandle hRootNode = hRoot.FirstChildElement("root-node");

	ReadGroup(hRootNode.Element(), mRootNode);

	TiXmlElement* nodeElem = hRootNode.FirstChild().Element();

	for (nodeElem; nodeElem; nodeElem = nodeElem->NextSiblingElement())
	{
		const char* nodeType = nodeElem->Value();

		if (!strcmp(nodeType, "group"))
		{
			Group* group = nullptr;

			ReadGroup(nodeElem, group);

			mRootNode->AddChild(group);
		}
		else if (!strcmp(nodeType, "behavior"))
		{
			Behavior* behavior = nullptr;

			ReadBehavior(nodeElem, behavior);

			mRootNode->AddChild(behavior);
		}
	}

	return true;
}

void BehaviorTree::ReadBehavior(TiXmlElement* behaviorElem, Behavior*& behavior)
{
	const char* behaviorType = behaviorElem->Attribute("type");

	if (!strcmp(behaviorType, "wait-time"))
	{
		float timeToWait = 0.0f;
		behaviorElem->Attribute("time-to-wait", &timeToWait);
		behavior = new BehaviorWaitTime(timeToWait);
	}
	else if (!strcmp(behaviorType, "set-image"))
	{
		behavior = new BehaviorSetImage(behaviorElem->Attribute("image"));
	}
	else if (!strcmp(behaviorType, "move-to-target"))
	{
		float speed = 0.0f;
		float stopDistance = 0.0f;

		behaviorElem->Attribute("speed", &speed);
		behaviorElem->Attribute("stop-distance", &stopDistance);

		behavior = new BehaviorMoveToTarget(speed, stopDistance);
	}
	else if (!strcmp(behaviorType, "attack"))
	{
		float damage = 0.0f;
		behaviorElem->Attribute("damage", &damage);

		behavior = new BehaviorAttack(damage);
	}
	else if (!strcmp(behaviorType, "check-for-target"))
	{
		const char* isInverse = behaviorElem->Attribute("is-inverse");

		if (!strcmp(isInverse, "true"))
		{
			behavior = new BehaviorCheckForTarget(true);
		}
		else if (!strcmp(isInverse, "false"))
		{
			behavior = new BehaviorCheckForTarget(false);
		}
	}
	else if (!strcmp(behaviorType, "check-distance"))
	{
		float distance = 0.0f;
		behaviorElem->Attribute("distance", &distance);

		const char* isInverse = behaviorElem->Attribute("is-inverse");

		if (!strcmp(isInverse, "true"))
		{
			behavior = new BehaviorCheckDistance(true, distance);
		}
		else if (!strcmp(isInverse, "false"))
		{
			behavior = new BehaviorCheckDistance(false, distance);
		}
	}
	else if (!strcmp(behaviorType, "check-receive-damage"))
	{
		behavior = new BehaviorCheckReceiveDamage();
	}
	else if (!strcmp(behaviorType, "check-health"))
	{
		float valueToCompare = 0.0f;
		behaviorElem->Attribute("value-to-compare", &valueToCompare);

		const char* isInverse = behaviorElem->Attribute("is-inverse");

		if (!strcmp(isInverse, "true"))
		{
			behavior = new BehaviorCheckHealth(true, valueToCompare);
		}
		else if (!strcmp(isInverse, "false"))
		{
			behavior = new BehaviorCheckHealth(false, valueToCompare);
		}
	}
	else if (!strcmp(behaviorType, "die"))
	{
		behavior = new BehaviorDie();
	}
}

void BehaviorTree::ReadGroup(TiXmlElement* groupElem, Group*& group)
{
	TiXmlElement* groupSubElem = groupElem->FirstChildElement();

	const char* groupType = groupElem->Attribute("type");

	if (!strcmp(groupType, "selector"))
	{
		group = new Selector();
	}
	else if (!strcmp(groupType, "sequence"))
	{
		group = new Sequence();
	}

	for (groupSubElem; groupSubElem; groupSubElem = groupSubElem->NextSiblingElement())
	{
		const char* groupSubElemType = groupSubElem->Value();

		if (!strcmp(groupSubElemType, "group"))
		{
			Group* newGroup = nullptr;

			ReadGroup(groupSubElem, newGroup);

			group->AddChild(newGroup);
		}
		else if (!strcmp(groupSubElemType, "behavior"))
		{
			Behavior* behavior = nullptr;
			
			ReadBehavior(groupSubElem, behavior);

			group->AddChild(behavior);
		}
	}
}

void BehaviorTree::InitOwnerCharacterReference(Character* ownerCharacter)
{
	if (mRootNode != nullptr)
	{
		mRootNode->SetOwnerCharacter(ownerCharacter);
		mHasBeenInitialized = true;
	}
}

void BehaviorTree::Tick(float step)
{
	if (mRootNode != nullptr)
	{
		mRootNode->Tick(step);
	}
}