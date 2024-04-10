#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ss
{
	class PlayerSpaceShip;
	class GameplayHUD;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);
	private:

		virtual void AllGameStageFinished() override;
		virtual void BeginPlay() override;
		weak<PlayerSpaceShip> mPlayerSpaceShip;
		weak<GameplayHUD> mGameplayHUD;
		void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceShip);

		TimerHandle timerHandle_Test;
		virtual void InitGameStages() override;
		void QuitGame();
		void Restart();
		void SpawnCosmetics();

		void GameOver();
	};
}