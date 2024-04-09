#include "player/PlayerSpaceShip.h"
#include <SFML/System.hpp>
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ss
{
	PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string& path)
		:SpaceShip{ owningWorld, path },
		mMoveInput{},
		mSpeed{ 200.f },
		mShooter{ new BulletShooter{this, 0.1f, {50.f, 0.f}} },
		mInvincibleTime{2.f},
		mInvincible{true},
		mInvincibleFlashInterval{0.5f},
		mInvincibleFlashTimer{0.f},
		mInvincibleFlashDir{1}
	{
		SetTeamID(1);
	}

	void PlayerSpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
		UpdateInvincible(deltaTime);
	}

	void PlayerSpaceShip::Shoot()
	{
		if(mShooter)
		{
			mShooter->Shoot();
		}
	}

	void PlayerSpaceShip::SetShooter(unique<Shooter>&& newShooter)
	{
		if(mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->IncrementLevel();
			return;
		}

		mShooter = std::move(newShooter);
	}

	void PlayerSpaceShip::ApplayDamage(float amt)
	{
		if(!mInvincible)
		{
			SpaceShip::ApplayDamage(amt);
		}
	}

	void PlayerSpaceShip::BeginPlay()
	{
		SpaceShip::BeginPlay();
		TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceShip::StopInvincible, mInvincibleTime);
	}

	void PlayerSpaceShip::HandleInput()
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMoveInput.y = 1.f;
		}


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMoveInput.x = -1.f;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}


		ClampInputOnAge();
		NormalizeInput();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceShip::NormalizeInput()
	{
		Normalize(mMoveInput);
	}

	void PlayerSpaceShip::ClampInputOnAge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if(actorLocation.x < 0 && mMoveInput.x == -1)
		{
			mMoveInput.x = 0.f;
		}

		if(actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}

		if(actorLocation.y < 0 && mMoveInput.y == -1)
		{
			mMoveInput.y = 0.f;
		}

		if(actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}
	}


	void PlayerSpaceShip::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}


	void PlayerSpaceShip::StopInvincible()
	{
		GetSprite().setColor({ 255,255,255,255 });
		mInvincible = false;
	}

	void PlayerSpaceShip::UpdateInvincible(float deltaTime)
	{
		if (!mInvincible) 
		{
			return;
		}
		
		mInvincibleFlashTimer += deltaTime * mInvincibleFlashDir;
		if(mInvincibleFlashTimer < 0 || mInvincibleFlashTimer > mInvincibleFlashInterval)
		{
			mInvincibleFlashDir *= -1;
		}

		GetSprite().setColor(LerpColor({ 255, 255,255, 40 }, { 255,255,255,200 }, mInvincibleFlashTimer/ mInvincibleFlashInterval));
	}

}

