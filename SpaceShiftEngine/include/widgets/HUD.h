#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Object.h"

namespace ss
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		bool HasInit() { return mAlredyInit; }
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float delataTime);
	protected:
		HUD();

	private:
		virtual void Init(const sf::RenderWindow& windowRef);
		bool mAlredyInit;
	};
}