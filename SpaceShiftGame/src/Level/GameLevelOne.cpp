#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"
#include "Enemy/Boss.h"
#include "Enemy/UFOStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"
#include "framework/Application.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/BackdropActor.h"
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


	void GameLevelOne::AllGameStageFinished()
	{
		mGameplayHUD.lock()->GameFinished(true);
	}

	void GameLevelOne::BeginPlay()
	{
		SpawnCosmetics();

		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceShip = newPlayer.SpawnSpaceShip(this);
		mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
		mGameplayHUD.lock()->onQuitButtonCLicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
		mGameplayHUD.lock()->onRestartButtonCLicked.BindAction(GetWeakRef(), &GameLevelOne::Restart);
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
		
		AddStage(shared<VanguardStage>{new VanguardStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 15.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 12.f}});
		AddStage(shared<HexagonStage>{new HexagonStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<UFOStage>{new UFOStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<ChaosStage>{new ChaosStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<BossStage>{new BossStage{this}});

	}

	void GameLevelOne::QuitGame()
	{
		GetApplication()->QuitApplication();
	}

	void GameLevelOne::Restart()
	{
		PlayerManager::Get().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::SpawnCosmetics()
	{
		auto backdropActor = SpawnActor<BackdropActor>("SpaceShiftRedux/Backgrounds/darkPurple.png");
	}

	void GameLevelOne::GameOver()
	{
		mGameplayHUD.lock()->GameFinished(false);
	}
}