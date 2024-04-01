#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"

namespace ss
{
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float delatTime) override;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		TextWidget mFramerateText;
		ValueGuage mPlayerHealthBar;
	};
}