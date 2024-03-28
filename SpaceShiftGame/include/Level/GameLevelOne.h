#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ss
{
	class PlayerSpaceShip;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);
	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceShip> mPlayerSpaceShip;
		void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceShip);

		TimerHandle timerHandle_Test;
		virtual void InitGameStages() override;
		void GameOver();
	};
}