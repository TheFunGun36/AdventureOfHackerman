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
    wcex.lpszClassName = c::processName;

    RegisterClassEx(&wcex);

    RECT wndRect;
    wndRect.top = 0;
    wndRect.left = 0;
    wndRect.right = c::wndSizeX;
    wndRect.bottom = c::wndSizeY;

    HWND hWnd = CreateWindow(c::processName, "Adventure Of Hackerman", WS_POPUP, CW_USEDEFAULT, 0, wndRect.right, wndRect.bottom, NULL, NULL, hInstance, NULL);
    
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
    static byte mouseX = '\x00',
        mouseY = '\x00';
    switch (msg) {
    case WM_MOUSEMOVE:
    {
        {
            short nMouseX = GET_X_LPARAM(lParam),
                nMouseY = GET_Y_LPARAM(lParam);
            ScreenToClient(hWnd, &POINT({ nMouseX, nMouseY }));
            if (nMouseX < 0 || nMouseY < 0) {
                break;
            }

            mouseX = nMouseX / c::symbolSizeX;
            if (mouseX > c::charsInX) {
                break;
            }

            mouseY = nMouseY / c::symbolSizeY;
            if (mouseY > c::charsInY) {
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
                if ((mouseX >= objectX1) && (mouseX < objectX2)
                    && (mouseY >= objectY1) && (mouseY < objectY2)) {
                    if (!objectList[i]->bMouseIsHovering) {
                        objectList[i]->eMouseHoverStart(mouseX - objectList[i]->posX,
                            mouseY - objectList[i]->posY);
                        objectList[i]->bMouseIsHovering = true;
                    }
                    objectList[i]->eMouseMoving(mouseX - objectList[i]->posX,
                        mouseY - objectList[i]->posY);
                } else {
                    if (objectList[i]->bMouseIsHovering) {
                        objectList[i]->eMouseHoverEnd(mouseX - objectList[i]->posX,
                            mouseY - objectList[i]->posY);
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
                objectList[i]->eMouseLmbPressed(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
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
                objectList[i]->eMouseLmbReleased(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
                if (objectList[i]->bLmbDownHandled) {
                    objectList[i]->eMouseLmbClick(mouseX - objectList[i]->posX,
                        mouseY - objectList[i]->posY);
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
                objectList[i]->eMouseRmbDown(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
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
                objectList[i]->eMouseRmbUp(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
                if (objectList[i]->bRmbDownHandled) {
                    objectList[i]->eMouseRmbClick(mouseX - objectList[i]->posX,
                        mouseY - objectList[i]->posY);
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

