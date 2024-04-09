#pragma once 

#include "Enemy/SpaceShipEnemy.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ss
{
	class Boss : public EnemySpaceShip
	{
	public:
		Boss(World* world);
		virtual void Tick(float delatTime);
		virtual void BeginPlay() override;

	private:
		float mSpeed;
		float mBaseSpeed;
		float mSwitchDistanceToEdge;
		void CheckMove();

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;

		ThreeWayShooter mThreeWayShooter;
		FrontalWiper mFrontalWiperLeft;
		FrontalWiper mFrontalWiperRight;

		BulletShooter mFinalStageShooterLeft;
		BulletShooter mFinalStageShooterRight;

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWipers();
		void HealthChanged(float amt, float currentHealth, float maxHealth);

		void SetStage(int newStage);
		int mStage;
	};
}