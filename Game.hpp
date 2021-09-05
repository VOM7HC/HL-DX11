#pragma once

#include <Windows.h>
#include <string>

#include "GameClock.hpp"
#include "GameTime.hpp"

namespace Helper
{
    class Game
    {
    public:
        Game(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
        ~Game();

        HINSTANCE Instance() const;
        HWND WindowHandle() const;
        const WNDCLASSEX& Window() const;
        const std::wstring& WindowClass() const;
        const std::wstring& WindowTitle() const;
        int ScreenHeight() const;
        int ScreenWidth() const;

        virtual void Run();
        virtual void Exit();
        virtual void Initialize();
        virtual void Update(const GameTime& gameTime);
        virtual void Draw(const GameTime& gameTime);

    protected:
        virtual void InitializeWindow();
        virtual void Shutdown();

        static const UINT DefaultScreenWidth;
        static const UINT DefaultScreenHeight;
        static const UINT DefaultFrameRate;
        static const UINT DefaultMultiSamplingCount;

        HINSTANCE mInstance;
        std::wstring mWindowClass;
        std::wstring mWindowTitle;
        int mShowCommand;

        HWND mWindowHandle;
        WNDCLASSEX mWindow;

        UINT mScreenWidth;
        UINT mScreenHeight;

        GameClock mGameClock;
        GameTime mGameTime;

    private:
        Game(const Game& rhs);
        Game& operator=(const Game& rhs);

        POINT CenterWindow(int windowWidth, int windowHeight);
        static LRESULT WINAPI WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
    };
}