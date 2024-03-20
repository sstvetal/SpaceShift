#pragma once

#include "spaceShip/SpaceShip.h"

namespace ss
{
	class EnemySpaceShip : public SpaceShip
	{
	public: 
		EnemySpaceShip(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);

		virtual void Tick(float deltaTime) override;

	private:
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;

	};
}