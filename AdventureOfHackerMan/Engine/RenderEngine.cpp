#include "RenderEngine.h"

namespace engine {
    void Renderer::initialize(HWND hWnd, HRESULT& hr) {
        factory = nullptr;
        renderTarget = nullptr;
        writetFactory = nullptr;
        writeTextFormat = nullptr;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

        if (SUCCEEDED(hr)) {
            RECT rect;
            GetClientRect(hWnd, &rect);

            D2D1_SIZE_U wndSize = D2D1::SizeU(rect.right, rect.bottom);

            hr = factory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hWnd, wndSize),
                &renderTarget);
        }

        if (SUCCEEDED(hr)) {
            hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                __uuidof(writetFactory),
                reinterpret_cast<IUnknown**>(&writetFactory));
        }

        if (SUCCEEDED(hr)) {
            hr = writetFactory->CreateTextFormat(L"Lucida console",
                NULL,
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                constants::charSizeY - 1,
                L"",
                &writeTextFormat);
        }
    }

    void Renderer::uninitialize() {
        if (factory != nullptr) {
            factory->Release();
        }
        if (renderTarget != nullptr) {
            renderTarget->Release();
        }
    }

    void Renderer::renderMap(Map* map) {
        renderTarget->BeginDraw();
        clearScreen(1.0f, 1.0f, 1.0f);

        ID2D1SolidColorBrush* br;
        for (int iy = 0; iy < constants::charsInY; iy++) {
            for (int ix = 0; ix < constants::charsInX; ix++) {
                const WCHAR wCh[1] = { map->getSymbol(ix, iy) };
                ID2D1SolidColorBrush* br;
                ID2D1SolidColorBrush* bgBr;
                float r, g, b;
                {
                    color symbolColor = map->getSymbolColor(ix, iy);
                    Map::expandColor(symbolColor, r, g, b);
                }
                renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &br);

                {
                    color symbolBgColor = map->getSymbolBgColor(ix, iy);
                    Map::expandColor(symbolBgColor, r, g, b);
                }
                renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &bgBr);

                D2D1_RECT_F rect = D2D1::RectF(
                    static_cast<float>(constants::charSizeX * ix),
                    static_cast<float>(constants::charSizeY * iy),
                    static_cast<float>(ceil(constants::charSizeX * (ix + 1))),
                    static_cast<float>(ceil(constants::charSizeY * (iy + 1))));

                if (bgBr != nullptr) {
                    renderTarget->FillRectangle(rect, bgBr);
                    bgBr->Release();
                }
                if (br != nullptr) {
                    renderTarget->DrawTextA(wCh, 1, writeTextFormat, rect, br);
                    br->Release();
                }

            }
        }

        renderTarget->EndDraw();
    }
}