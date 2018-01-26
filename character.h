#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <vector>

#include <params.h>

class BehaviorTree;

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;  }
	void SetAngularVelocity(float angle) { mAngularVelocity = angle; }
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity; }
	float GetAngularVelocity() const { return mAngularVelocity; }

	Params GetParams() { return mParams; }

	void AddImageName(const char* image) { mImages.push_back(image); }
	int GetImageIndex(const char* image) const;

	void ReadAndInitializeBehaviorTree(const char* filename);

	void AddTarget(Character* target) { mTargets.push_back(target); }
	Character* GetCurrentTarget() const { return mCurrentTarget; }
	void DeleteCurrentTarget() { mCurrentTarget = nullptr; }

	float GetHealth() const { return mHealth; }
	void SetHealth(float health) { mHealth = health; }
	bool IsDead() const { return mHealth <= 0.0f; }
	void Die() { RemoveEntity(this); }

	void ReceiveDamage(float damage) { mHealth -= damage; mHasReceivedDamage = true; mReceiveDamageTimer = mInitialReceiveDamageTimer; }
	bool HasReceivedDamage() { return mHasReceivedDamage; mHasReceivedDamage = false; mReceiveDamageTimer = 0.0f; }

private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;

	Params mParams;
	BehaviorTree* mBehaviorTree;

	std::vector<const char*> mImages;

	Character* mCurrentTarget;
	std::vector<Character*> mTargets;

	float mHealth;

	bool mHasReceivedDamage;
	float mInitialReceiveDamageTimer;
	float mReceiveDamageTimer;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _getPointerToThis(lua_State* L);
	static int _addImageName(lua_State* L);
	static int _readAndInitializeBehaviorTree(lua_State* L);
	static int _addTarget(lua_State* L);
	static int _setHealth(lua_State* L);
};

#endif