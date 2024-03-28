#pragma once

#include "spaceShip/SpaceShip.h"
#include "player/Reward.h"

namespace ss
{
	class EnemySpaceShip : public SpaceShip
	{
	public: 
		EnemySpaceShip(World* owningWorld,
					   const std::string& texturePath,
					   float collisionDamage = 200.f,
					   const List<RewardFactoryFunc> rewards =
					   {
							  CreateHealthReward,
							  CreateThreeWayShooterReward,
							  CreateFrontalWiperReward
					   }
		);
		virtual void Tick(float deltaTime) override;

	private:
		void SpawnReward();
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		List<RewardFactoryFunc> mRewardFactories;

	};
}