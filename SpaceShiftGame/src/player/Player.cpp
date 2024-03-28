#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceShip.h"

namespace ss
{
	Player::Player()
		:mLifeCount{3},
		mScore{0},
		mCurrentPlayerSpaceShip{}
	{
	}


	weak<PlayerSpaceShip> Player::SpawnSpaceShip(World* world)
	{
		if(mLifeCount > 0)
		{
			--mLifeCount;
			auto windowSize = world->GetWindowSize();
			mCurrentPlayerSpaceShip = world->SpawnActor<PlayerSpaceShip>();
			mCurrentPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 100.f));
			mCurrentPlayerSpaceShip.lock()->SetActorRotation(-90.f);
			onLifeChange.Broadcast(mLifeCount);
			return mCurrentPlayerSpaceShip;
		}
		else
		{
			onLifeExhausted.Broadcast();
		}
		return weak<PlayerSpaceShip>{};
	}

	void Player::AddLifeCount(unsigned int count)
	{
		if(count> 0)
		{
			mLifeCount += count;
			onLifeChange.Broadcast(mLifeCount);
		}
	}

	void Player::AddScore(unsigned int amt)
	{
		if(amt > 0)
		{
			mScore = amt;
			onScoreChange.Broadcast(mScore);
		}
	}
}