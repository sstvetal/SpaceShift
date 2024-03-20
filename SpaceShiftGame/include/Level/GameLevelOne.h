#pragma once
#include "framework/World.h"

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
		unsigned int timerIndex_Test;
	};
}