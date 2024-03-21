#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"


namespace ss
{
	class BulletShooter : public Shooter
	{
	public: 
		BulletShooter(Actor* owner, float cooldownTime = 1.f, const sf::Vector2f localPositionOffest = {0.f, 0.f},  float localRotationOffset = 0.f);
		virtual bool IsOnCooldown() const override;
	private:
		virtual void ShootImpl();
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffest;
		float mLocalRotationOffset;
	};
}