#include "stdafx.h"
#include "sequence.h"

void Sequence::OnEnter()
{
	mCurrentChildIndex = 0;
}

Status Sequence::Update(float step)
{
	int numberOfChildren = mChildren.size();

	if (numberOfChildren == 0)
	{
		return eInvalid;
	}

	while (true)
	{
		if (mChildren[mCurrentChildIndex] != nullptr)
		{
			Status currentChildStatus = mChildren[mCurrentChildIndex]->Tick(step);

			if (currentChildStatus != eSuccess)
			{
				return currentChildStatus;
			}
			else
			{
				mCurrentChildIndex++;

				if (mCurrentChildIndex == numberOfChildren)
				{
					return eSuccess;
				}
			}
		}
	}

	return eInvalid;
}