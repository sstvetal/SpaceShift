#pragma once 

#include <functional>
#include "framework/Core.h"
#include "framework/Object.h"


namespace ss
{
	struct TimerHandle
	{
	public:
		TimerHandle();
		unsigned int GetTimerKey() const { return mTimerKey; }
	private:
		unsigned int mTimerKey;
		static unsigned int timerKeyCounter;
		static unsigned int GetNextTimerKey() { return ++timerKeyCounter; }
	};

	struct TimeHandleHashFunction                                           // Hash function for timer to replase usigned int
	{
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const       // operator () for Hash function to be able to call "()"
		{
			return timerHandle.GetTimerKey();
		}
	};

	bool operator == (const TimerHandle& lhs, const TimerHandle& rhs);     // operator == for Hash function to compare bouth timers

	struct Timer
	{
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();

	private:
		std::pair<weak<Object>, std::function<void()>> mListener;
		float mDuration;
		bool mRepeat;
		float mTimerCounter;
		bool mIsExpired;
	};

	class TimerManager
	{
	public:
		static TimerManager& Get();
		template<typename ClassName>
		TimerHandle  SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			TimerHandle newHandle{};
			mTimers.insert({ newHandle, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat)});
			return newHandle;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerHandle);

	protected:
		TimerManager();

	private:
		static unique<TimerManager> timerManager;
		Dictionary<TimerHandle, Timer, TimeHandleHashFunction> mTimers;
	};
}