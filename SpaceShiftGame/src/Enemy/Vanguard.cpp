#include "Enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ss
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		:EnemySpaceShip{owningWorld, texturePath},
		mShooter{new BulletShooter{this, 1.f, {50.f, 0}} }
	{
		SetVelocity(velocity);
		SetActorRotation(90.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		mShooter->Shoot();
	}
}