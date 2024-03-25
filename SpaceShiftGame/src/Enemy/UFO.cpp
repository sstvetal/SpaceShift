#include "Enemy/UFO.h"
#include "Enemy/HexagonStage.h"
#include "weapon/BulletShooter.h"

namespace ss
{
	UFO::UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath, float rotationSpeed)
		:EnemySpaceShip{ owningWorld, texturePath },
		mShooter1{ new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f},-60} },
		mShooter2{ new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f},60} },
		mShooter3{ new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f},180} },
		mRotationSpeed{rotationSpeed}
	{
		SetVelocity(velocity);
		SetActorRotation(90.f);
	}

	void UFO::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		Shoot();
		AddActorRotationOffset(mRotationSpeed * deltaTime);
	}

	void UFO::Shoot()
	{
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
	}

}
