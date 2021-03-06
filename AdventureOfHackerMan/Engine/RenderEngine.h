#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include "Map.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")
namespace engine {
    class Renderer {
    public:
        void initialize(HWND hWnd, HRESULT& hr);
        void uninitialize();
        void renderMap(Map* map);

    private:
        ID2D1Factory* factory;
        ID2D1HwndRenderTarget* renderTarget;
        IDWriteFactory* writetFactory;
        IDWriteTextFormat* writeTextFormat;

        FORCEINLINE void clearScreen(float r, float g, float b) {
            renderTarget->Clear(D2D1::ColorF(r, g, b));
        }
    };
}