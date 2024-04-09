#pragma once

#include "spaceShip/SpaceShip.h"
#include "framework/TimerManager.h"

namespace ss
{
	class Shooter;
	class PlayerSpaceShip : public SpaceShip
	{
	public:
		PlayerSpaceShip(World* owningWorld, const std::string& path = "SpaceShiftRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		float GetSpeed() const { return mSpeed; }
		virtual void Shoot() override;
		void SetShooter(unique<Shooter>&& newShooter);
		virtual void ApplayDamage(float amt) override;
		virtual void BeginPlay() override;
	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputOnAge();
		void ConsumeInput(float deltaTime);
		void StopInvincible();
		void UpdateInvincible(float deltaTime);
		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;

		float mInvincibleTime;
		TimerHandle mInvincibleTimerHandle;
		bool mInvincible;

		float mInvincibleFlashInterval;
		float mInvincibleFlashTimer;
		float mInvincibleFlashDir;

	};
}