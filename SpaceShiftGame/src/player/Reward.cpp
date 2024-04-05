#include "player/Reward.h"
#include "player/PlayerSpaceShip.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/World.h"
#include "player/PlayerManager.h"


namespace ss
{
	Reward::Reward(World* world, const std::string texturePath, RewardFunc rewardFunc, float speed)
		:Actor{world, texturePath},
		mRewardFunc{rewardFunc},
		mSpeed{speed}
	{
	}


	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}

	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		if (!otherActor || otherActor->IsPendingDestroy())
			return;

		if (!PlayerManager::Get().GetPlayer())
			return;

		weak<PlayerSpaceShip> playerSpaceShip = PlayerManager::Get().GetPlayer()->GetCurrentSpaceShip();
		if (playerSpaceShip.expired() || playerSpaceShip.lock()->IsPendingDestroy())
			return;

		if(playerSpaceShip.lock()->GetUniqueID() == otherActor->GetUniqueID())
		{
			mRewardFunc(playerSpaceShip.lock().get());
			Destroy();
		}
	}


	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShiftRedux/PNG/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShiftRedux/PNG/three_shooter_pickup.png", RewardThreeWayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShiftRedux/PNG/front_row_shooter_pickup.png", RewardFrontalWiper);
	}

	weak<Reward> CreateLifeReward(World* world)
	{
		return CreateReward(world, "SpaceShiftRedux/PNG/pickups/playerLife1_blue.png", RewardLife);
	}

	weak<Reward> CreateReward(World* world, const std::string texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceShip* player)
	{
		static float rewardAmt = 10.f;
		if(player && !player->IsPendingDestroy())
		{
			player->GetHealthComp().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreeWayShooter(PlayerSpaceShip* player)
	{
		if(player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4, {50.f, 0.f} }});
		}
	}


	void RewardFrontalWiper(PlayerSpaceShip* player)
	{
		if(player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new FrontalWiper{player, 0.4f, {50.f, 0.f}}});
		}
	}

	void RewardLife(PlayerSpaceShip* player)
	{
		if (!PlayerManager::Get().GetPlayer())
			return;

		PlayerManager::Get().GetPlayer()->AddLifeCount(1);
	}
}