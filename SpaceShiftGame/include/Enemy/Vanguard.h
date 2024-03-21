#pragma once
#include "Enemy/SpaceShipEnemy.h"

namespace ss
{
	class BulletShooter;
	class Vanguard : public EnemySpaceShip
	{
	public:
		Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShiftRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f& velocity = {0.f, 150.f});
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;
		unique<BulletShooter> mShooter;
	};
}