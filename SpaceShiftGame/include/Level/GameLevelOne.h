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
		weak<PlayerSpaceShip> testPlayerSpaceShip;
		void TimerCallBack_Test();
		TimerHandle timerHandle_Test;
	};
}