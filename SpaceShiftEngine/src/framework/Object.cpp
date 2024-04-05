#include "framework/Object.h"
#include "framework/Core.h"

namespace ss
{
	unsigned int Object::mUniqueIDCounter = 0;
	Object::Object()
		:mIsPendingDestroy{false},
		mUniqueID{GetNextAvalibleID()}
	{
	}

	Object:: ~Object()
	{
		LOG("Object Destroyed");
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef() 
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}

	unsigned int Object::GetNextAvalibleID()
	{
		return mUniqueIDCounter++;
	}
}
