#include "widgets/GameplayHUD.h"

namespace ss
{
	GameplayHUD::GameplayHUD()
		:mFramerateText{"Frame Rate"},
		mPlayerHealthBar{}
	{
		mFramerateText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float delatTime)
	{
		int frameRate = int(1 / delatTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFramerateText.SetString(frameRateStr);
	}


	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{0.f, windowSize.y - 50.f});
		mPlayerHealthBar.UpdateValue(100.f, 200.f);
	}
}