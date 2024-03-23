#pragma once 

#include "Enemy/SpaceShipEnemy.h"

namespace ss
{
	class BulletShooter;
	class Hexagon : public EnemySpaceShip
	{
	public:
		Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShiftRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = {0.f,100.f});


		virtual void Tick(float deltaTime) override;
		virtual void Shoot() override;

	private:
		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		unique<BulletShooter> mShooter4;
		unique<BulletShooter> mShooter5;
		unique<BulletShooter> mShooter6;
	};
}