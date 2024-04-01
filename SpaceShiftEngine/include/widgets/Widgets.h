#pragma once 

#include <SFML/Graphics.hpp>

#include "framework/Object.h"


namespace ss
{
	class Widgets : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);
		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float newRotation);
		sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
		float GetWidgetRotation() const {return mWidgetTransform.getRotation(); }

		void SetVisibility(bool newVisibility);
		bool GetVisibility() const { return mIsVisible; }
	protected:
		Widgets();
	private:
		virtual void Draw(sf::RenderWindow& renderRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

		sf::Transformable mWidgetTransform;
		bool mIsVisible;

	};
}