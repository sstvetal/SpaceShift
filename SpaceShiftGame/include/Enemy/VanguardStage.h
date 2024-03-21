#pragma once
#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"




namespace ss
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);
		virtual void StartStage() override;

	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRawSpawnCount;

		int mVanguardsPerRaw;
		int mCurrentRawVanguardCount;

		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();

	};
}