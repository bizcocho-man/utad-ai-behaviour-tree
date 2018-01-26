#include "stdafx.h"
#include "behavior.h"
#include "character.h"

// Base
Status Behavior::Tick(float step)
{
	if (mStatus == eInvalid)
	{
		OnEnter();
	}

	mStatus = Update(step);

	if (mStatus != eRunning)
	{
		OnExit();

		Status statusToReturn = mStatus;
		mStatus = eInvalid;

		return statusToReturn;
	}

	return mStatus;
}

// Wait time
Status BehaviorWaitTime::Update(float step)
{
	mCurrentTime -= step;

	if (mCurrentTime <= 0.0f)
	{
		return eSuccess;
	}

	return eRunning;
}

// Set Image
void BehaviorSetImage::OnEnter()
{
	if (mOwnerCharacter != nullptr)
	{
		int imageIndex = mOwnerCharacter->GetImageIndex(mImage.c_str());
		mOwnerCharacter->SetImage(imageIndex);

		mStatus = eSuccess;

		return;
	}

	mStatus = eFail;
}

// Move To Target
Status BehaviorMoveToTarget::Update(float step)
{
	if (mOwnerCharacter != nullptr)
	{
		Character* target = mOwnerCharacter->GetCurrentTarget();

		if (target != nullptr)
		{
			USVec2D direction = target->GetLoc() - mOwnerCharacter->GetLoc();
			float length = direction.Length();

			if (length > 0.0f)
			{
				direction.NormSafe();
				direction *= mSpeed;

				mOwnerCharacter->SetLoc(mOwnerCharacter->GetLoc() + direction * step);
			}

			// Check stop distance
			USVec2D characterLoc2D = USVec2D(mOwnerCharacter->GetLoc().mX, mOwnerCharacter->GetLoc().mY);
			USVec2D enemyLoc2D = USVec2D(target->GetLoc().mX, target->GetLoc().mY);

			float distance = characterLoc2D.Dist(enemyLoc2D);

			if (distance <= mStopDistance)
			{
				return eSuccess;
			}
			else
			{
				return eRunning;
			}
		}
	}

	return eFail;
}

// Attack
void BehaviorAttack::OnEnter()
{
	if (mOwnerCharacter != nullptr)
	{
		Character* target = mOwnerCharacter->GetCurrentTarget();

		if (target != nullptr)
		{
			target->ReceiveDamage(mDamage);

			if (target->IsDead())
			{
				mOwnerCharacter->DeleteCurrentTarget();
			}

			mStatus = eSuccess;

			return;
		}
	}

	mStatus = eFail;
}

// Check for target
void BehaviorCheckForTarget::OnEnter()
{
	if (mOwnerCharacter != nullptr && mOwnerCharacter->GetCurrentTarget() != nullptr)
	{
		if (mIsInverse)
		{
			mStatus = eFail;
		}
		else
		{
			mStatus = eSuccess;
		}

		return;
	}

	if (mIsInverse)
	{
		mStatus = eSuccess;
	}
	else
	{
		mStatus = eFail;
	}
}

// Check distance
void BehaviorCheckDistance::OnEnter()
{
	if (mOwnerCharacter != nullptr)
	{
		Character* target = mOwnerCharacter->GetCurrentTarget();

		if (target != nullptr)
		{
			USVec2D characterLoc2D = USVec2D(mOwnerCharacter->GetLoc().mX, mOwnerCharacter->GetLoc().mY);
			USVec2D enemyLoc2D = USVec2D(target->GetLoc().mX, target->GetLoc().mY);

			float distance = characterLoc2D.Dist(enemyLoc2D);

			if (distance >= mDistance)
			{
				if (mIsInverse)
				{
					mStatus = eSuccess;
				}
				else
				{
					mStatus = eFail;
				}

				return;
			}
			else
			{
				if (mIsInverse)
				{
					mStatus = eFail;
				}
				else
				{
					mStatus = eSuccess;
				}

				return;
			}
		}
	}

	if (mIsInverse)
	{
		mStatus = eSuccess;
	}
	else
	{
		mStatus = eFail;
	}
}

// Receive damage
void BehaviorCheckReceiveDamage::OnEnter()
{
	if (mOwnerCharacter != nullptr)
	{
		if (mOwnerCharacter->HasReceivedDamage())
		{
			mStatus = eSuccess;

			return;
		}
	}

	mStatus = eFail;
}

// Check health
void BehaviorCheckHealth::OnEnter()
{
	if (mOwnerCharacter != nullptr)
	{
		if (mOwnerCharacter->GetHealth() >= mValueToCompare)
		{
			if (mIsInverse)
			{
				mStatus = eSuccess;
			}
			else
			{
				mStatus = eFail;
			}

			return;
		}
		else
		{
			if (mIsInverse)
			{
				mStatus = eFail;
			}
			else
			{
				mStatus = eSuccess;
			}

			return;
		}
	}

	if (mIsInverse)
	{
		mStatus = eSuccess;
	}
	else
	{
		mStatus = eFail;
	}
}

// Die
void BehaviorDie::OnEnter()
{
	if (mOwnerCharacter != nullptr)
	{
		mOwnerCharacter->Die();

		mStatus = eSuccess;

		return;
	}

	mStatus = eFail;
}