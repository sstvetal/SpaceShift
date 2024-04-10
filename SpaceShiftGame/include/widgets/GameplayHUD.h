#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"

namespace ss
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float delatTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);
		Delegate<>onRestartButtonCLicked;
		Delegate<>onQuitButtonCLicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void RefreshHealthBar();
		void ConnectPlayerStatus();
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int newScore);
		void PlayerSpaceShipDestroyed(Actor* actor);

		void RestartButtonClicked();
		void QuitButtonClicked();

		TextWidget mFramerateText;
		ValueGuage mPlayerHealthBar;

		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshold;

		float mWidgetSpaceing;

		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		Button mRestartButton;
		Button mQuitButton;

		sf::Vector2u mWindowSize;


	};
}