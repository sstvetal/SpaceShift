#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceShip.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

namespace ss
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{

	}


	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceShip = newPlayer.SpawnSpaceShip(this);
		mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
	}

	void GameLevelOne::PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceShip)
	{
		mPlayerSpaceShip = PlayerManager::Get().GetPlayer()->SpawnSpaceShip(this);
		if(!mPlayerSpaceShip.expired())
		{
			mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<UFOStage>{new UFOStage{this}});

		AddStage(shared<VanguardStage>{new VanguardStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
		AddStage(shared<HexagonStage>{new HexagonStage{this}});


		AddStage(shared<HexagonStage>{new HexagonStage{this}});

	}

	void GameLevelOne::GameOver()
	{
		LOG("Game Over!  ==========================================");
	}
}