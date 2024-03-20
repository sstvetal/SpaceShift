#include "Enemy/SpaceShipEnemy.h"

namespace ss 
{
	EnemySpaceShip::EnemySpaceShip(World* owningWorld, const std::string& texturePath,float collisionDamage)
		:SpaceShip{owningWorld, texturePath},
		mCollisionDamage{collisionDamage}
	{
		SetTeamID(2);
	}

	void EnemySpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
		{
			Destroy();
		}
	}

	void EnemySpaceShip::OnActorBeginOverlap(Actor* other)
	{
		SpaceShip::OnActorBeginOverlap(other);
		if(IsOtherHostile(other))
		{
			other->ApplayDamage(mCollisionDamage);
		}
	}
}