#include "GameClock.hpp"

Helper::GameClock::GameClock() : mStartTime(), mCurrentTime(), mLastTime(), mFrequency()
{
    mFrequency = GetFrequency();
    Reset();
}

const LARGE_INTEGER& Helper::GameClock::StartTime() const
{
    return mStartTime;
}

const LARGE_INTEGER& Helper::GameClock::CurrentTime() const
{
    return mCurrentTime;
}

const LARGE_INTEGER& Helper::GameClock::LastTime() const
{
    return mLastTime;
}

void Helper::GameClock::Reset()
{
    GetTime(mStartTime);
    mCurrentTime = mStartTime;
    mLastTime = mCurrentTime;
}

double Helper::GameClock::GetFrequency() const
{
    LARGE_INTEGER frequency;

    if (QueryPerformanceFrequency(&frequency) == false) {
        throw std::exception("QueryPerformanceFrequency() failed.");
    }

    return static_cast<double>(frequency.QuadPart);
}

void Helper::GameClock::GetTime(LARGE_INTEGER& time) const
{
    QueryPerformanceCounter(&time);
}

void Helper::GameClock::UpdateGameTime(GameTime& gameTime)
{
    GetTime(mCurrentTime);
    gameTime.SetTotalGameTime((mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrequency);
    gameTime.SetElapsedGameTime((mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrequency);

    mLastTime = mCurrentTime;
}
