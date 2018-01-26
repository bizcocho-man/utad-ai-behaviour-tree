#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include "behaviortree/behaviortree.h"

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END

	mCurrentTarget = nullptr;

	mBehaviorTree = new BehaviorTree();

	mHealth = 0.0f;

	mHasReceivedDamage = false;
	mInitialReceiveDamageTimer = 0.5f;
	mReceiveDamageTimer = 0.0f;
}

Character::~Character()
{

}

void Character::OnStart()
{

}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	// Check targets
	if (mCurrentTarget == nullptr)
	{
		int numberOfTargets = mTargets.size();

		if (numberOfTargets > 0)
		{
			mCurrentTarget = mTargets.back();
			mTargets.pop_back();
		}
	}

	// Update receive damage timer
	if (mReceiveDamageTimer > 0.0f)
	{
		mReceiveDamageTimer -= step;
	}
	else if (mReceiveDamageTimer <= 0.0f)
	{
		mReceiveDamageTimer = 0.0f;
		mHasReceivedDamage = false;
	}

	// Update State Machine
	if (mBehaviorTree != nullptr && mBehaviorTree->HasBeenInitialized())
	{
		mBehaviorTree->Tick(step);
	}
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.0f);

}

int Character::GetImageIndex(const char* imageName) const
{
	int numberOfImages = mImages.size();

	for (int i = 0; i < numberOfImages; ++i)
	{
		if (!strcmp(mImages[i], imageName))
		{
			return i;
		}
	}

	return -1;
}

void Character::ReadAndInitializeBehaviorTree(const char* filename)
{
	if (mBehaviorTree != nullptr && mBehaviorTree->ReadBehaviorTreeFile(filename))
	{
		mBehaviorTree->InitOwnerCharacterReference(this);
	}
}



// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",						_setLinearVel },
		{ "setAngularVel",						_setAngularVel },
		{ "getPointerToThis",					_getPointerToThis },
		{ "addImageName",						_addImageName },
		{ "readAndInitializeBehaviorTree",		_readAndInitializeBehaviorTree },
		{ "addTarget",							_addTarget},
		{ "setHealth",							_setHealth},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}

int Character::_getPointerToThis(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	int pointer = reinterpret_cast<int>(self);

	lua_pushinteger(L, pointer);

	return 1;
}

int Character::_addImageName(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	cc8* image = lua_tostring(state, -1);

	self->AddImageName(image);

	lua_pop(L, -1);

	return 0;
}

int Character::_readAndInitializeBehaviorTree(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	cc8* filename = lua_tostring(state, -1);

	self->ReadAndInitializeBehaviorTree(filename);

	lua_pop(L, -1);

	return 0;
}

int Character::_addTarget(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	int targetToInt = lua_tonumber(L, -1);

	if (targetToInt != 0)
	{
		self->AddTarget(reinterpret_cast<Character*>(targetToInt));
	}

	lua_pop(L, -1);

	return 0;
}

int Character::_setHealth(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	int health = lua_tonumber(L, -1);

	self->SetHealth(health);

	lua_pop(L, -1);

	return 0;
}