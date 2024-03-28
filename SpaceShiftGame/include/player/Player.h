#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"



namespace ss
{
	class PlayerSpaceShip;
	class World;
	class Player : Object
	{
	public:
		Player();
		weak<PlayerSpaceShip> SpawnSpaceShip(World* world);
		const weak<PlayerSpaceShip> GetCurrentSpaceShip() const { return mCurrentPlayerSpaceShip; }

		void AddLifeCount(unsigned int count);
		int GetLifeCount() const { return mLifeCount; }

		void AddScore(unsigned int amt);
		int GetScore() const { return mScore; }

		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onLifeExhausted;

	private:
		unsigned int mLifeCount;
		unsigned int mScore;
		weak<PlayerSpaceShip> mCurrentPlayerSpaceShip;
	};
}