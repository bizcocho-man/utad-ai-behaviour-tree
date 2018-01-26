#ifndef __BEHAVIORTREE_H__
#define __BEHAVIORTREE_H__

class Character;
class Behavior;
class Group;
class TiXmlElement;

class BehaviorTree
{
public:
	BehaviorTree() { mRootNode = nullptr; mHasBeenInitialized = false; }

	bool HasBeenInitialized() const { return mHasBeenInitialized; }

	bool ReadBehaviorTreeFile(const char* filename);
	void InitOwnerCharacterReference(Character* ownerCharacter);

	void Tick(float step);

private:
	bool mHasBeenInitialized;

	Group* mRootNode;

	void ReadBehavior(TiXmlElement* behaviorElem, Behavior*& behavior);
	void ReadGroup(TiXmlElement* groupElem, Group*& group);
};

#endif