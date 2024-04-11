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
#include "framework/BackgroundLayer.h"
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
		weak<BackroundLayer> planets = SpawnActor<BackroundLayer>();
		planets.lock()->SetAssets(
			{
				"SpaceShiftRedux/PNG/Planets/Planet1.png",
				"SpaceShiftRedux/PNG/Planets/Planet2.png",
			    "SpaceShiftRedux/PNG/Planets/Planet3.png",
			    "SpaceShiftRedux/PNG/Planets/Planet4.png",
			    "SpaceShiftRedux/PNG/Planets/Planet5.png",
			    "SpaceShiftRedux/PNG/Planets/Planet6.png",
			    "SpaceShiftRedux/PNG/Planets/Planet7.png"
			}
		);
		planets.lock()->SetSpriteCount(1);
		planets.lock()->SetSizes(1, 1.5f);
		planets.lock()->SetVelocities({0,30}, {0,80.f});




		weak<BackroundLayer> meteors = SpawnActor<BackroundLayer>();
		meteors.lock()->SetAssets(
			{
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorBrown_tiny2.png",



				"SpaceShiftRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_small2.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShiftRedux/PNG/Meteors/meteorGrey_tiny2.png"


			}
		);

		meteors.lock()->SetSpriteCount(20);
		meteors.lock()->SetSizes(.2f, .5f);
	}

	void GameLevelOne::GameOver()
	{
		mGameplayHUD.lock()->GameFinished(false);
	}
}