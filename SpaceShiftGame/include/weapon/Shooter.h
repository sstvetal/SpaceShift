#pragma once


namespace ss
{
	class Actor;
	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const { return mOwner; }

		int GetCurrentLevel() const { return mCurrentLevel; }
		int GetMaxLevel() const { return mMaxLevel; }


		virtual void SetCurrentLevel(int level);
		virtual void IncrementLevel(int amt = 1);


	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootImpl() = 0;
		Actor* mOwner;


		int mCurrentLevel;
		int mMaxLevel;

	};
}