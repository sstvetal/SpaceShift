#include "spaceShip/SpaceShip.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ss
{
	SpaceShip::SpaceShip(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		mVelocity{},
		mHealthComp{100.f, 100.f},
		mBlinkTime{0.f},
		mBlinkDuration{0.2f},
		mBlinkColorOffset{255, 0, 0, 255}
	{

	}

	void SpaceShip::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}

	void SpaceShip::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}

	void SpaceShip::Shoot()
	{

	}

	void SpaceShip::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &SpaceShip::OnHealthChanged);
		mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &SpaceShip::OnTakenDamage);
		mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &SpaceShip::Blow);

	}

	void SpaceShip::ApplayDamage(float amt)
	{
		mHealthComp.ChangeHealth(-amt);
	}

	void SpaceShip::Blink()
	{
		if(mBlinkTime == 0)
		{
			mBlinkTime = mBlinkDuration;
		}
	}

	void SpaceShip::UpdateBlink(float deltaTime)
	{
		if(mBlinkTime > 0)
		{
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}

	void SpaceShip::OnHealthChanged(float amt, float health, float maxHealth)
	{
	
	}

	void SpaceShip::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void SpaceShip::Blow()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Blew();
		Destroy();
		delete exp;
	}

	void SpaceShip::Blew()
	{

	}
}