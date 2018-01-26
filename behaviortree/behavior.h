#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include "status.h"
#include <string>

class Character;

// Base
class Behavior
{
public:
	Behavior() { mOwnerCharacter = nullptr; }

	virtual Status Tick(float step);

	virtual void SetOwnerCharacter(Character* ownerCharacter) { mOwnerCharacter = ownerCharacter; }
	
protected:
	Character* mOwnerCharacter;
	Status mStatus;

	virtual Status Update(float step) { return eSuccess; }
	virtual void OnEnter() { }
	virtual void OnExit() { }
};

// Wait time
class BehaviorWaitTime : public Behavior
{
public:
	BehaviorWaitTime(float timeToWait) : Behavior() { mTimeToWait = timeToWait; mCurrentTime = mTimeToWait; }

protected:
	virtual Status Update(float step);
	virtual void OnEnter() { mCurrentTime = mTimeToWait; }

private:
	float mTimeToWait;
	float mCurrentTime;
};

// Set image
class BehaviorSetImage : public Behavior
{
public:
	BehaviorSetImage(const char* image) : Behavior() { mImage = image; }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();

private:
	std::string mImage;
};

// Move to target
class BehaviorMoveToTarget : public Behavior
{
public:
	BehaviorMoveToTarget(float speed, float stopDistance) : Behavior() { mSpeed = speed; mStopDistance = stopDistance; }

protected:
	virtual Status Update(float step);

private:
	float mSpeed;
	float mStopDistance;
};

// Attack
class BehaviorAttack : public Behavior
{
public:
	BehaviorAttack(float damage) : Behavior() { mDamage = damage; }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();

private:
	float mDamage;
};

// Check for target
class BehaviorCheckForTarget : public Behavior
{
public:
	BehaviorCheckForTarget(bool isInverse) : Behavior() { mIsInverse = isInverse; }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();

private:
	bool mIsInverse;
};

// Check Distance
class BehaviorCheckDistance : public Behavior
{
public:
	BehaviorCheckDistance(bool isInverse, float distance) : Behavior() { mIsInverse = isInverse; mDistance = distance; }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();

private:
	bool mIsInverse;
	float mDistance;
};

// Check receive damage
class BehaviorCheckReceiveDamage : public Behavior
{
public:
	BehaviorCheckReceiveDamage() : Behavior() { }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();
};

// Check health
class BehaviorCheckHealth : public Behavior
{
public:
	BehaviorCheckHealth(bool isInverse, float valueToCompare) : Behavior() { mIsInverse = isInverse; mValueToCompare = valueToCompare; }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();

private:
	bool mIsInverse;
	float mValueToCompare;
};

// Die
class BehaviorDie : public Behavior
{
public:
	BehaviorDie() : Behavior() { }

protected:
	virtual Status Update(float step) { return mStatus; }
	virtual void OnEnter();
};

#endif