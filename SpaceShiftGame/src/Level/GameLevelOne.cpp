#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "player/PlayerSpaceShip.h"

namespace ss
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testPlayerSpaceShip = SpawnActor<PlayerSpaceShip>();
		testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceShip.lock()->SetActorRotation(-90.f);

	}


	void GameLevelOne::BeginPlay()
	{

	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<VanguardStage>{new VanguardStage{this}});
	}
}