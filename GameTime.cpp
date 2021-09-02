#include "GameTime.hpp"

Helper::GameTime::GameTime() : mTotalGameTime(0.0), mElapsedGameTime(0.0)
{
}

double Helper::GameTime::TotalGameTime() const
{
    return mTotalGameTime;
}

void Helper::GameTime::SetTotalGameTime(double totalGameTime)
{
    mTotalGameTime = totalGameTime;
}

double Helper::GameTime::ElapsedGameTime() const
{
    return mElapsedGameTime;
}

void Helper::GameTime::SetElapsedGameTime(double elapsedGameTime)
{
    mElapsedGameTime = elapsedGameTime;
}