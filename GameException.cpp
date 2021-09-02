#include "GameException.hpp"

Helper::GameException::GameException(const char* const& message, HRESULT hr)
{
}

HRESULT Helper::GameException::HR() const
{
    return mHR;
}

std::wstring Helper::GameException::whatw() const
{
    std::string whatString(what());
    std::wstring whatw;
    whatw.assign(whatString.begin(), whatString.end());

    return whatw;
}