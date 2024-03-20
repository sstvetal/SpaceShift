#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceShip.h"



namespace ss
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testPlayerSpaceShip = SpawnActor<PlayerSpaceShip>();
		testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceShip.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceShip = SpawnActor<Vanguard>();
		testSpaceShip.lock()->SetActorLocation(sf::Vector2f{100.f, 50.f});

	}


	void GameLevelOne::BeginPlay()
	{
		timerHandle_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallBack_Test, 2, true);
	}

	void GameLevelOne::TimerCallBack_Test()
	{
		LOG("Callback called!");
		TimerManager::Get().ClearTimer(timerHandle_Test);
	}
}