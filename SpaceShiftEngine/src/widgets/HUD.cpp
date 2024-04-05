#include "widgets/HUD.h"

namespace ss
{
	void HUD::NativeInit(const sf::RenderWindow& windowRef)
	{
		if(!mAlredyInit)
		{
			mAlredyInit = true;
			Init(windowRef);
		}
	}

	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	HUD::HUD()
		:mAlredyInit{false}
	{

	}

	void HUD::Init(const sf::RenderWindow& windowRef)
	{

	}

	void HUD::Tick(float delataTime)
	{
	
	}
}