#include "stdafx.h"
#include "group.h"

void Group::SetOwnerCharacter(Character* ownerCharacter)
{
	mOwnerCharacter = ownerCharacter;

	int numberOfChildren = mChildren.size();

	for (int i = 0; i < numberOfChildren; ++i)
	{
		mChildren[i]->SetOwnerCharacter(ownerCharacter);
	}
}