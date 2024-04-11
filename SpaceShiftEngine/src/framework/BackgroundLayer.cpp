#include "framework/BackgroundLayer.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ss
{
	BackroundLayer::BackroundLayer(World* owningWorld,
		const List<std::string>& assetPaths,
		const sf::Vector2f& minVel,
		const sf::Vector2f& maxVel,
		float sizeMin,
		float sizeMax,
		int spriteCount,
		const sf::Color& colorTint)
		:Actor{ owningWorld },
		mMinVelocity{minVel},
		mMaxVelocity{maxVel},
		mSizeMin{sizeMin},
		mSizeMax{sizeMax},
		mSpriteCount{spriteCount},
		mTintColor{colorTint}
	{
		SetAssets(assetPaths);
		SetEnablePhysics(false);
	}

	void BackroundLayer::SetAssets(const List<std::string>& assetPathes)
	{
		for (const std::string& texturePath : assetPathes)
		{
			shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturePath);
			mTextures.push_back(newTexture);
		}

		RefreshSprites();
	}

	void BackroundLayer::RefreshSprites()
	{
		mSprites.clear();
		mVelocities.clear();

		for(int i =0; i < mSpriteCount; ++i)
		{
			sf::Sprite newSprite{};
			RandomSpriteTexture(newSprite);
			RandomSpriteTransform(newSprite, true);
			mSprites.push_back(newSprite);

			float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
			float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
			mVelocities.push_back(sf::Vector2f{velX, velY});
		}

		SetColorTint(mTintColor);
	}

	void BackroundLayer::RandomSpriteTexture(sf::Sprite& sprite)
	{
		if(mTextures.size() > 0)
		{
			shared<sf::Texture> pickedTexture = GetRandomTexture();
			sprite.setTexture(*(pickedTexture.get()));
			sprite.setTextureRect(sf::IntRect{0, 0, (int)pickedTexture->getSize().x, (int)pickedTexture->getSize().y});
			sf::FloatRect bound = sprite.getGlobalBounds();
			sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
		}
	}

	void BackroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		RandomSpritePosition(sprite, randomY);
		RandomSpriteRotation(sprite);
		RandomSpriteSize(sprite);
	}

	void BackroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		auto windowSize = GetWorld()->GetWindowSize();
		auto bound = sprite.getGlobalBounds();

		float posX = RandomRange(0, windowSize.x);
		float posY = randomY ? RandomRange(0, windowSize.y) : -bound.height;

		sprite.setPosition(sf::Vector2f{posX, posY});
	}

	void BackroundLayer::RandomSpriteRotation(sf::Sprite& sprite)
	{
		sprite.setRotation(RandomRange(0, 360.f));
	}

	void BackroundLayer::RandomSpriteSize(sf::Sprite& sprite)
	{
		float size = RandomRange(mSizeMin, mSizeMax);
		sprite.setScale(size, size);
	}

	bool BackroundLayer::IsSpriteOffScreen(sf::Sprite& sprite) const
	{
		auto bound = sprite.getGlobalBounds();
		auto windowSize = GetWorld()->GetWindowSize();
		auto spritePos = sprite.getPosition();

		if (spritePos.x < -bound.width || spritePos.x > windowSize.x + bound.width)
		{
			return true;
		}

		if (spritePos.y < -bound.height || spritePos.y > windowSize.y + bound.height)
		{
			return true;
		}

		return false;
	}

	void BackroundLayer::SetColorTint(const sf::Color& color)
	{
		mTintColor = color;
		for(sf::Sprite& sprite : mSprites)
		{
			sprite.setColor(color);
		}
	}

	void BackroundLayer::SetSpriteCount(int newCount)
	{
		mSpriteCount = newCount;
		RefreshSprites();
	}

	void BackroundLayer::SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		mMinVelocity = min;
		mMaxVelocity = max;

		for (size_t i = 0; i < mVelocities.size(); ++i)
		{
			float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
			float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
			mVelocities[i] = sf::Vector2f{ velX, velY };
		}
	}

	void BackroundLayer::SetSizes(float min, float max)
	{
		mSizeMin = min;
		mSizeMax = max;

		for (size_t i = 0; i < mSprites.size(); ++i)
		{
			RandomSpriteSize(mSprites[i]);
		}
	}

	void BackroundLayer::Render(sf::RenderWindow& windowRef)
	{
		Actor::Render(windowRef);
		for(const sf::Sprite& sprite : mSprites)
		{
			windowRef.draw(sprite);
		}
	}

	void BackroundLayer::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		for(int i = 0; i<mSprites.size(); ++i)
		{
			sf::Sprite& sprite = mSprites[i];
			sf::Vector2f& vel = mVelocities[i];

			sprite.setPosition(sprite.getPosition() + vel * deltaTime);
			if(IsSpriteOffScreen(sprite))
			{
				RandomSpriteTexture(sprite);
				RandomSpriteTransform(sprite);
		
				float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
				float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
				mVelocities[i] = sf::Vector2f{ velX, velY };
			}
		}
	}

	shared<sf::Texture> BackroundLayer::GetRandomTexture() const
	{
		int randomPickIndex = (int)(RandomRange(0, mTextures.size()));
		return mTextures[randomPickIndex];
	}
}