#include "Enemy/SpaceShipEnemy.h"
#include "framework/MathUtility.h"

namespace ss 
{
	EnemySpaceShip::EnemySpaceShip(World* owningWorld, const std::string& texturePath, float collisionDamage, const List<RewardFactoryFunc> rewards)
	    :SpaceShip{owningWorld, texturePath},
		mCollisionDamage{collisionDamage},
		mRewardFactories{rewards}
	{
		SetTeamID(2);
	}

	void EnemySpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}

	void EnemySpaceShip::SpawnReward()
	{
		if (mRewardFactories.size() == 0) return;


		int pick = (int)RandomRange(0, mRewardFactories.size());
		if(pick >= 0 && pick < mRewardFactories.size())
		{
			weak<Reward> newReward = mRewardFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
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

	void EnemySpaceShip::Blew()
	{
		SpawnReward();
	}
}