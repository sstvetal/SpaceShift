#include "framework/Core.h"
#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/World.h"

namespace ss
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f localPositionOffest, float localRotationOffset, const std::string bulletTexturePath)
		: Shooter{owner},
		mCooldownClock{},
		mCooldownTime{cooldownTime},
		mLocalPositionOffest{localPositionOffest},
		mLocalRotationOffset{localRotationOffset},
		mBulletTexturePath{bulletTexturePath}
	{
	}
	bool BulletShooter::IsOnCooldown() const
	{
		if(mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime / GetCurrentLevel())
		{
			return false;
		}

		return true;
	}

	void BulletShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
	}

	void BulletShooter::SetBulletTexturePath(const std::string& bulletTexturePath)
	{
		mBulletTexturePath = bulletTexturePath;
	}

	void BulletShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

		mCooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), mBulletTexturePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffest.x + ownerRightDir * mLocalPositionOffest.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
	}
}