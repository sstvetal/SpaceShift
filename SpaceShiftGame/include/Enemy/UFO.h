#pragma once

#include "Enemy/SpaceShipEnemy.h"

namespace ss
{
	class BulletShooter;
	class UFO : public EnemySpaceShip
	{
	public:
		UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath = "SpaceShiftRedux/PNG/ufoBlue.png", float rotationSpeed = 40.f);

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;


		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		float mRotationSpeed;
	};
}