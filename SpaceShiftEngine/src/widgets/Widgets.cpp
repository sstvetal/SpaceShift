#include "widgets/Widgets.h"

namespace ss
{
	void Widgets::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (mIsVisible)
		{
			Draw(windowRef);
		}
	}

	bool Widgets::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void Widgets::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		mWidgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widgets::SetWidgetRotation(float newRotation)
	{
		mWidgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widgets::SetVisibility(bool newVisibility)
	{
		mIsVisible = newVisibility;
	}

	Widgets::Widgets()
		:mIsVisible{ true },
		mWidgetTransform{}
	{

	}

	void Widgets::Draw(sf::RenderWindow& renderRef)
	{

	}

	void Widgets::LocationUpdated(const sf::Vector2f& newLocation)
	{

	}

	void Widgets::RotationUpdated(float newRotation)
	{

	}
}