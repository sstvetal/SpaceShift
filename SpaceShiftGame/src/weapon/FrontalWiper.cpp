#include "weapon/FrontalWiper.h"

namespace ss
{
	FrontalWiper::FrontalWiper(Actor* ownerActor, float cooldownTime, const sf::Vector2f& localOffset, float width)
		:Shooter{ownerActor},
		mWidth{width},
		mShooter1{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width/2.f}, 0.f,"SpaceShiftRedux/PNG/Lasers/laserGreen11.png"},
		mShooter2{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width/6.f}, 0.f, "SpaceShiftRedux/PNG/Lasers/laserBlue07.png"},
		mShooter3{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width/6.f}, 0.f, "SpaceShiftRedux/PNG/Lasers/laserBlue07.png"},
		mShooter4{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width/2.f}, 0.f,"SpaceShiftRedux/PNG/Lasers/laserGreen11.png"},
		mShooter5{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width/1.5f}, 15.f,"SpaceShiftRedux/PNG/Lasers/laserGreen11.png"},
		mShooter6{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width/1.5f}, -15.f,"SpaceShiftRedux/PNG/Lasers/laserGreen11.png"}
	{

	}

	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooter1.IncrementLevel(amt);
		mShooter2.IncrementLevel(amt);
		mShooter3.IncrementLevel(amt);
		mShooter4.IncrementLevel(amt);
		mShooter5.IncrementLevel(amt);
		mShooter6.IncrementLevel(amt);
	}

	void FrontalWiper::SetCurrentLevel(int newLevel)
	{
		Shooter::SetCurrentLevel(newLevel);
		mShooter1.SetCurrentLevel(newLevel);
		mShooter2.SetCurrentLevel(newLevel);
		mShooter3.SetCurrentLevel(newLevel);
		mShooter4.SetCurrentLevel(newLevel);
		mShooter5.SetCurrentLevel(newLevel);
		mShooter6.SetCurrentLevel(newLevel);
	}

	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();

		if(GetCurrentLevel() == GetMaxLevel())
		{
			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
}