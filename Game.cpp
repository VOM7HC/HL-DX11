#include "Game.hpp"

const UINT Helper::Game::DefaultScreenHeight = 768;
const UINT Helper::Game::DefaultScreenWidth = 1024;

Helper::Game::Game(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
                 : mInstance(instance), mWindowClass(windowClass), mWindowTitle(windowTitle), mShowCommand(showCommand),
                   mWindowHandle(), mWindow(),
                   mScreenWidth(DefaultScreenWidth), mScreenHeight(DefaultScreenHeight),
                   mGameClock(), mGameTime()
{
}

Helper::Game::~Game()
{
}

HINSTANCE Helper::Game::Instance() const
{
    return mInstance;
}

HWND Helper::Game::WindowHandle() const
{
    return mWindowHandle;
}

const WNDCLASSEX& Helper::Game::Window() const
{
    return mWindow;
}

const std::wstring& Helper::Game::WindowClass() const
{
    return mWindowClass;
}

const std::wstring& Helper::Game::WindowTitle() const
{
    return mWindowTitle;
}

int Helper::Game::ScreenWidth() const
{
    return mScreenWidth;
}

int Helper::Game::ScreenHeight() const
{
    return mScreenHeight;
}

void Helper::Game::Run()
{
    InitializeWindow();
    Initialize();

    MSG message;
    ZeroMemory(&message, sizeof(message));

    mGameClock.Reset();

    while (message.message != WM_QUIT) {
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else {
            mGameClock.UpdateGameTime(mGameTime);
            Update(mGameTime);
            Draw(mGameTime);
        }
    }

    Shutdown();
}

void Helper::Game::Exit()
{
    PostQuitMessage(0);
}

void Helper::Game::Initialize()
{
}

void Helper::Game::Update(const GameTime& gameTime)
{
}

void Helper::Game::Draw(const GameTime& gameTime)
{
}

void Helper::Game::InitializeWindow()
{
    ZeroMemory(&mWindow, sizeof(mWindow));
    mWindow.cbSize = sizeof(WNDCLASSEX);
    mWindow.style = CS_CLASSDC;
    mWindow.lpfnWndProc = WndProc;
    mWindow.hInstance = mInstance;
    mWindow.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    mWindow.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    mWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
    mWindow.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    mWindow.lpszClassName = mWindowClass.c_str();

    RECT windowRectangle = { 0, 0, mScreenWidth, mScreenHeight };
    AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

    RegisterClassEx(&mWindow);
    POINT center = CenterWindow(mScreenWidth, mScreenHeight);
    mWindowHandle = CreateWindow(mWindowClass.c_str(),
                                 mWindowTitle.c_str(),
                                 WS_OVERLAPPEDWINDOW,
                                 center.x,
                                 center.y,
                                 windowRectangle.right - windowRectangle.left,
                                 windowRectangle.bottom - windowRectangle.top,
                                 nullptr,
                                 nullptr,
                                 mInstance,
                                 nullptr);

    ShowWindow(mWindowHandle, mShowCommand);
    UpdateWindow(mWindowHandle);
}

void Helper::Game::Shutdown()
{
    UnregisterClass(mWindowClass.c_str(), mWindow.hInstance);
}

LRESULT WINAPI Helper::Game::WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(windowHandle, message, wParam, lParam);
}

POINT Helper::Game::CenterWindow(int windowWidth, int windowHeight)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    POINT center;
    center.x = (screenWidth - windowWidth) / 2;
    center.y = (screenHeight - windowHeight) / 2;

    return center;
}