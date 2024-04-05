#pragma once
#include "framework/Actor.h"
#include "functional"

namespace ss
{
	class PlayerSpaceShip;
	class Reward;
	using RewardFunc = std::function<void(PlayerSpaceShip*)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;
	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string texturePath,  RewardFunc rewardFunc, float speed = 200.f);
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime);
		virtual void OnActorBeginOverlap(Actor* otherActor) override;
	private:
		float mSpeed;
		RewardFunc mRewardFunc;
	};


	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreeWayShooterReward(World* world);
	weak<Reward> CreateFrontalWiperReward(World* world);
	weak<Reward> CreateLifeReward(World* world);

	weak<Reward> CreateReward(World* world, const std::string texturePath, RewardFunc rewardFunc);

	void RewardHealth(PlayerSpaceShip* player);
	void RewardThreeWayShooter(PlayerSpaceShip* player);
	void RewardFrontalWiper(PlayerSpaceShip* player);
	void RewardLife(PlayerSpaceShip* player);

}