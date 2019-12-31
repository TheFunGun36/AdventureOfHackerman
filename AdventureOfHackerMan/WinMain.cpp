//#include "Game.h"
#include "Game/Game.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(wcex);
    wcex.lpfnWndProc = WndProc;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.lpszClassName = c_sProcessName;

    RegisterClassEx(&wcex);

    RECT wndRect;
    wndRect.top = 0;
    wndRect.left = 0;
    wndRect.right = c_nWndSizeX;
    wndRect.bottom = c_nWndSizeY;

    HWND hWnd = CreateWindow(c_sProcessName, "Adventure Of Hackerman", WS_POPUP, CW_USEDEFAULT, 0, wndRect.right, wndRect.bottom, NULL, NULL, hInstance, NULL);
    
    HRESULT* hr = new HRESULT(S_OK);

    game::initialize(hWnd, *hr);

    if (FAILED(*hr)) {
        MessageBox(NULL, "Failed to initialize game", "ERROR", MB_OK | MB_ICONERROR);
        delete hr;
        return -1;
    }
    delete hr;

    ShowWindow(hWnd, 10);
    UpdateWindow(hWnd);
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOYIELD | PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        engine::computeGameLogic();
        engine::renderGraphic();
    }
    game::uninitialize();
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    //HDC hDC;// PAINTSTRUCT ps;
    switch (msg) {
    case WM_MOUSEMOVE:
    {
        byte mouseX, mouseY;
        {
            short nMouseX = GET_X_LPARAM(lParam),
                nMouseY = GET_Y_LPARAM(lParam);
            ScreenToClient(hWnd, &POINT({ nMouseX, nMouseY }));
            if (nMouseX < 0 || nMouseY < 0) {
                break;
            }

            mouseX = nMouseX / c_nSymbolSizeX;
            if (mouseX > c_nCharsInX) {
                break;
            }

            mouseY = nMouseY / c_nSymbolSizeY;
            if (mouseY > c_nCharsInY) {
                break;
            }
        }

        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->bGenerateMouseEvents) {
                byte objectX1, objectY1,
                    objectX2, objectY2;
                objectList[i]->getPosition(&objectX1, &objectY1, &objectX2, &objectY2);
                if ((mouseX >= objectX1) && (mouseX <= objectX2)
                    && (mouseY >= objectY1) && (mouseY <= objectY2)) {
                    if (!objectList[i]->bMouseIsHovering) {
                        objectList[i]->eMouseHoverStart();
                        objectList[i]->bMouseIsHovering = true;
                    }
                } else {
                    if (objectList[i]->bMouseIsHovering) {
                        objectList[i]->eMouseHoverEnd();
                        objectList[i]->bMouseIsHovering = false;
                        objectList[i]->bLmbDownHandled = false;
                    }
                }
            }
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->bGenerateMouseEvents && objectList[i]->bMouseIsHovering) {
                objectList[i]->eMouseLmbPressed();
                objectList[i]->bLmbDownHandled = true;
            }
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->bGenerateMouseEvents && objectList[i]->bMouseIsHovering) {
                objectList[i]->eMouseLmbReleased();
                if (objectList[i]->bLmbDownHandled) {
                    objectList[i]->eMouseLmbClick();
                    objectList[i]->bLmbDownHandled = false;
                }
            }
        }
    }
    break;
    case WM_RBUTTONDOWN:
    {
        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->bGenerateMouseEvents && objectList[i]->bMouseIsHovering) {
                objectList[i]->eMouseRmbDown();
                objectList[i]->bRmbDownHandled = true;
            }
        }
    }
    break;
    case WM_RBUTTONUP:
    {
        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->bGenerateMouseEvents && objectList[i]->bMouseIsHovering) {
                objectList[i]->eMouseRmbUp();
                if (objectList[i]->bRmbDownHandled) {
                    objectList[i]->eMouseRmbClick();
                    objectList[i]->bRmbDownHandled = false;
                }
            }
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

