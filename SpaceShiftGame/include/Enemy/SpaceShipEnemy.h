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
					   float rewardSpawnWeight = 0.5f,
					   const List<RewardFactoryFunc> rewards =
					   {
							  CreateHealthReward,
							  CreateThreeWayShooterReward,
							  CreateFrontalWiperReward,
							  CreateLifeReward
					   }
		);
		virtual void Tick(float deltaTime) override;
		void SetScoreAwardAmt(unsigned int amt);
		void SetRewardSpawnWeight(float weight);
	private:
		void SpawnReward();
		float mCollisionDamage;
		unsigned int mScoreAwardAmt;
		float mRewardSpawnWeight;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		List<RewardFactoryFunc> mRewardFactories;

	};
}