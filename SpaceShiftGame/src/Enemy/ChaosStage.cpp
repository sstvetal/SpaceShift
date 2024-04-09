#include "Enemy/ChaosStage.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"

namespace ss
{
	ChaosStage::ChaosStage(World* world)
		:GameStage{world},
		mSpawnInterval{4.f},
		mMinSpawnInterval{0.8f},
		mSpawnIntervalDecrement{0.5f},
		mSpawnIntervalDecrementInterval{5.f},
		mStageDuration{60.f}
	{

	}

	void ChaosStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
		mDifficultTimeHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreseDificulty, mSpawnIntervalDecrementInterval, true);
		TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mDifficultTimeHandle);
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	void ChaosStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);

	}

	void ChaosStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, mSpawnInterval);
	}

	void ChaosStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{
		
		sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();

		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center = sf::Vector2f{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f dirToCenter = center - spawnLoc;
		Normalize(dirToCenter);

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(dirToCenter * 200.f);
		newUFO.lock()->SetActorLocation(spawnLoc);

		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
	}

	void ChaosStage::IncreseDificulty()
	{
		mSpawnInterval -= mSpawnIntervalDecrement;
		if(mSpawnInterval < mMinSpawnInterval)
		{
			mSpawnInterval = mMinSpawnInterval;
		}
	}

	void ChaosStage::StageDurationReached()
	{
		FinishStage();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnX = RandomRange(100.f, windowSize.x - 100.f);
		float spawnY = -100.f;

		return{ spawnX, spawnY };
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnLeft = RandomRange(-1, 1);
		float spawnLocX = 0;

		if(spawnLeft < 0)
		{
			spawnLocX = windowSize.x + 100.f;
		}
		else
		{
			spawnLocX = -100.f;
		}

		float spawnLocY = RandomRange(0, windowSize.y);
		return sf::Vector2f{spawnLocX, spawnLocY};
	}


}