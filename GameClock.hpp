#pragma once

#include <Windows.h>
#include <exception>

#include "GameTime.hpp"

namespace Helper
{    
    class GameClock
    {
    public:
        GameClock();

        const LARGE_INTEGER& StartTime() const;
        const LARGE_INTEGER& CurrentTime() const;
        const LARGE_INTEGER& LastTime() const;

        void Reset();
        double GetFrequency() const;
        void GetTime(LARGE_INTEGER& time) const;
        void UpdateGameTime(GameTime& gameTime);

    private:
        GameClock(const GameClock& rhs);
        GameClock& operator=(const GameClock& rhs);

        LARGE_INTEGER mStartTime;
        LARGE_INTEGER mCurrentTime;
        LARGE_INTEGER mLastTime;
        double mFrequency;
    };
}