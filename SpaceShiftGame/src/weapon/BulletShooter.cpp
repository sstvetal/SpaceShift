#include "framework/Core.h"
#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/World.h"

namespace ss
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f localPositionOffest, float localRotationOffset)
		: Shooter{owner},
		mCooldownClock{},
		mCooldownTime{cooldownTime},
		mLocalPositionOffest{localPositionOffest},
		mLocalRotationOffset{localRotationOffset}
	{
	}
	bool BulletShooter::IsOnCooldown() const
	{
		if(mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
		{
			return false;
		}

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

		mCooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShiftRedux/PNG/Lasers/laserBlue16.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffest.x + ownerRightDir * mLocalPositionOffest.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
	}
}