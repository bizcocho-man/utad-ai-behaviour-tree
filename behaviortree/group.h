#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include "behavior.h"

class Behavior;

class Group : public Behavior
{
public:
	void AddChild(Behavior* child) { mChildren.push_back(child); }

	virtual void SetOwnerCharacter(Character* ownerCharacter);

protected:
	std::vector<Behavior*> mChildren;
};

#endif