#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"


namespace ss
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningWorld{owningWorld},
		mHasBeganPlay{false},
		mSprite{},
		mTexture{},
		mPhysicBody{nullptr},
		mPhysicsEnabled{false},
		mTeamID{GetNeturalTeamID()}

	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor destroyed");
	}
	void Actor::BeginPlayInternal()
	{
		if(!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if(!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::BeginPlay()
	{

	}

	void Actor::Tick(float deltaTime)
	{

	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int TestureHight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, TestureHight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;
		else
			window.draw(mSprite);
	}




	void Actor::SetDirection(float direction) //-----------------------------
	{
		mSprite.setRotation(direction);
	}





	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		mSprite.setPosition(newLoc);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorRotation(float newRot)
	{
		mSprite.setRotation(newRot);
		UpdatePhysicsBodyTransform();
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90);
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	void Actor::InitializePhysics()
	{
		if(!mPhysicBody)
		{
			mPhysicBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UnIntializePhysics()
	{
		if(mPhysicBody)
		{
			PhysicsSystem::Get().RemoveListener(mPhysicBody);
			mPhysicBody = nullptr;
		}

	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if(mPhysicBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());

			mPhysicBody->SetTransform(pos, rotation);
		}
	}


	bool Actor::IsActorOutOfWindowBounds(float allowance) const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();

		if(actorPos.x < -width - allowance)
		{
			return true;
		}

		if(actorPos.x > windowWidth + width + allowance)
		{
			return true;
		}

		if(actorPos.y < -height - allowance)
		{
			return true;
		}


		if(actorPos.y > windowHeight + height + allowance)
		{
			return true;
		}

		return false;
	}


	void Actor::SetEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if(mPhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UnIntializePhysics();
		}

	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{

	}

	void Actor::OnActorEndOverlap(Actor* other)
	{

	}

	void Actor::Destroy()
	{
		UnIntializePhysics();
		onActorDestroyed.Broadcast(this);
		Object::Destroy();
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (other == nullptr) return false;
		if (GetTeamID() == GetNeturalTeamID() || other->GetTeamID() == other->GetNeturalTeamID())
		{
			return false;
		}

		return GetTeamID() != other->GetTeamID();
	}

	void Actor::ApplayDamage(float amt)
	{

	}
}