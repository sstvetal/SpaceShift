#include "gameFramework/GameApplication.h"
#include "Level/GameLevelOne.h"
#include "framework/AssetManager.h"
#include "config.h"


//#define DEG_TO_RAD 0.0174533f // 180 / pi // -----------------------


ss::Application* GetApplication()
{
	return new ss::GameApplication{};
}

namespace ss
{
	GameApplication::GameApplication()
		: Application{ 600, 980, "Spase Shift", sf::Style::Titlebar | sf::Style::Close }
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
	}
}