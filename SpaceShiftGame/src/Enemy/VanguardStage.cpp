#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "framework/World.h"


namespace ss
{
	VanguardStage::VanguardStage(World* world)
		:GameStage{world},
		mSpawnInterval{1.5f},
		mSwitchInterval{5.f},
		mSpawnDistanceToEdge{100.f},
		mLeftSpawnLoc{0.0f,0.0f},
		mRightSpawnLoc{0.0f,0.0f},
		mSpawnLoc{0.0f,0.0f},
		mRowsToSpawn{2},
		mRawSpawnCount{0},
		mCurrentRawVanguardCount{0},
		mVanguardsPerRaw{3}
	{

	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawnLoc = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawnLoc);
		++mCurrentRawVanguardCount;
		if(mCurrentRawVanguardCount == mVanguardsPerRaw)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentRawVanguardCount = 0;
		}

	}

	void VanguardStage::SwitchRow()
	{
		if (mRawSpawnCount == mRowsToSpawn)
		{
			FinishStage();
			return;
		}

		if(mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc = mRightSpawnLoc;
		}
		else
		{
			mSpawnLoc = mLeftSpawnLoc;
		}

		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

		++mRawSpawnCount;
	}


}