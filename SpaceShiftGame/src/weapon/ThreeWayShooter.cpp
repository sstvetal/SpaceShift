#include "weapon/ThreeWayShooter.h"

namespace ss
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		:Shooter{owner},
		mShooterLeft{owner, cooldownTime, localOffset + sf::Vector2f{10,-10}, -30.f, "SpaceShiftRedux/PNG/Lasers/laserRed01.png"},
		mShooterMid{owner, cooldownTime, localOffset, 0.f, "SpaceShiftRedux/PNG/Lasers/laserRed01.png"},
		mShooterRight{owner, cooldownTime, localOffset + sf::Vector2f{10,10}, 30.f, "SpaceShiftRedux/PNG/Lasers/laserRed01.png"}
	{

	}

	void ThreeWayShooter::ShootImpl()
	{
		mShooterLeft.Shoot();
		mShooterMid.Shoot();
		mShooterRight.Shoot();
	}
}