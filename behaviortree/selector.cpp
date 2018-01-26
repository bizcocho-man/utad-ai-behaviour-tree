#include "stdafx.h"
#include "selector.h"

void Selector::OnEnter()
{
	mCurrentChildIndex = 0;
}

Status Selector::Update(float step)
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

			if (currentChildStatus != eFail)
			{
				return currentChildStatus;
			}
			else
			{
				mCurrentChildIndex++;

				if (mCurrentChildIndex == numberOfChildren)
				{
					return eFail;
				}
			}
		}
	}

	return eInvalid;
}