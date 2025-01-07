#include "Game.h"

//// for memory leak detection
//#include <crtdbg.h>
//#ifdef _DEBUG
//    #define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
//#endif

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nShowCmd)
{
	//// for memory leak detection
 //   int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
 //   flag |= _CRTDBG_LEAK_CHECK_DF;
 //   _CrtSetDbgFlag(flag);

    const std::unique_ptr<Game> game = std::make_unique<Game>();

    // Initialize window and device
    if (FAILED(game->initWindow(hInstance, nShowCmd)))
        return 0;

    if (FAILED(game->initDevice()))
        return 0;

	//game->initCamera();

    // Main message loop
    MSG msg = {};
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                PostQuitMessage(0); // Send WM_QUIT message
                break;              // Exit the loop
            }
            if (GetAsyncKeyState('R') & 0x8000) {
                // Perform an action when R is pressed
                game->reset();
            }
            game->render(); // Continuously render the scene
        }
    }

    return static_cast<int>(msg.wParam);
}