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
    wcex.lpszClassName = constants::processName;

    RegisterClassEx(&wcex);

    RECT wndRect;
    wndRect.top = 0;
    wndRect.left = 0;
    wndRect.right = constants::wndSizeX;
    wndRect.bottom = constants::wndSizeY;

    HWND hWnd = CreateWindow(constants::processName, "Adventure Of Hackerman", WS_POPUP, CW_USEDEFAULT, 0, wndRect.right, wndRect.bottom, NULL, NULL, hInstance, NULL);
    
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

            mouseX = nMouseX / constants::charSizeX;
            if (mouseX > constants::charsInX) {
                break;
            }

            mouseY = nMouseY / constants::charSizeY;
            if (mouseY > constants::charsInY) {
                break;
            }
        }

        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->generateMouseEvents) {
                byte objectX1, objectY1,
                    objectX2, objectY2;
                objectList[i]->getPosition(&objectX1, &objectY1, &objectX2, &objectY2);
                if ((mouseX >= objectX1) && (mouseX < objectX2)
                    && (mouseY >= objectY1) && (mouseY < objectY2)) {
                    if (!objectList[i]->isMouseHovering) {
                        objectList[i]->emhStart(mouseX - objectList[i]->posX,
                            mouseY - objectList[i]->posY);
                        objectList[i]->isMouseHovering = true;
                    }
                    objectList[i]->emhMoving(mouseX - objectList[i]->posX,
                        mouseY - objectList[i]->posY);
                } else {
                    if (objectList[i]->isMouseHovering) {
                        objectList[i]->emhEnd(mouseX - objectList[i]->posX,
                            mouseY - objectList[i]->posY);
                        objectList[i]->isMouseHovering = false;
                        objectList[i]->isLmbDownHandled = false;
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
            if (objectList[i]->generateMouseEvents && objectList[i]->isMouseHovering) {
                objectList[i]->emlPressed(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
                objectList[i]->isLmbDownHandled = true;
            }
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->generateMouseEvents && objectList[i]->isMouseHovering) {
                objectList[i]->emlReleased(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
                if (objectList[i]->isLmbDownHandled) {
                    objectList[i]->emlClick(mouseX - objectList[i]->posX,
                        mouseY - objectList[i]->posY);
                    objectList[i]->isLmbDownHandled = false;
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
            if (objectList[i]->generateMouseEvents && objectList[i]->isMouseHovering) {
                objectList[i]->emrPressed(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
                objectList[i]->isRmbDownHandled = true;
            }
        }
    }
    break;
    case WM_RBUTTONUP:
    {
        int arraySize;
        Object** objectList = engine::getCurrentLevel()->getObjectArray(&arraySize);
        for (int i = 0; i < arraySize; i++) {
            if (objectList[i]->generateMouseEvents && objectList[i]->isMouseHovering) {
                objectList[i]->emrReleased(mouseX - objectList[i]->posX,
                    mouseY - objectList[i]->posY);
                if (objectList[i]->isRmbDownHandled) {
                    objectList[i]->emrClick(mouseX - objectList[i]->posX,
                        mouseY - objectList[i]->posY);
                    objectList[i]->isRmbDownHandled = false;
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

