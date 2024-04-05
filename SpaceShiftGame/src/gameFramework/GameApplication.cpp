#include "gameFramework/GameApplication.h"
#include "Level/GameLevelOne.h"
#include "Level/MainMenuLevel.h"
#include "framework/AssetManager.h"
#include "config.h"

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
		weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
	}
}