#include "RenderEngine.h"

namespace engine {
    void Renderer::initialize(HWND hWnd, HRESULT& hr) {
        pFactory = nullptr;
        pRenderTarget = nullptr;
        pWtFactory = nullptr;
        pWtTextFormat = nullptr;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

        if (SUCCEEDED(hr)) {
            RECT rect;
            GetClientRect(hWnd, &rect);

            D2D1_SIZE_U wndSize = D2D1::SizeU(rect.right, rect.bottom);

            hr = pFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hWnd, wndSize),
                &pRenderTarget);
        }

        if (SUCCEEDED(hr)) {
            hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                __uuidof(pWtFactory),
                reinterpret_cast<IUnknown**>(&pWtFactory));
        }

        if (SUCCEEDED(hr)) {
            hr = pWtFactory->CreateTextFormat(L"Lucida console",
                NULL,
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                c_nSymbolSizeY - 1,
                L"",
                &pWtTextFormat);
        }
    }

    void Renderer::uninitialize() {
        if (pFactory != nullptr) {
            pFactory->Release();
        }
        if (pRenderTarget != nullptr) {
            pRenderTarget->Release();
        }
    }

    void Renderer::renderMap(Map* map) {
        pRenderTarget->BeginDraw();
        clearScreen(1.0f, 1.0f, 1.0f);

        ID2D1SolidColorBrush* br;
        for (int iy = 0; iy < c_nCharsInY; iy++) {
            for (int ix = 0; ix < c_nCharsInX; ix++) {
                const WCHAR wCh[1] = { map->getSymbol(ix, iy) };
                ID2D1SolidColorBrush* br;
                ID2D1SolidColorBrush* bgBr;
                float r, g, b;
                {
                    clr_t textColor = map->getTextColor(ix, iy);
                    ExpandColor(textColor, r, g, b);
                }
                pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &br);

                {
                    clr_t bgColor = map->getBgColor(ix, iy);
                    ExpandColor(bgColor, r, g, b);
                }
                pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &bgBr);

                D2D1_RECT_F rect = D2D1::RectF(
                    static_cast<float>(c_nSymbolSizeX * ix),
                    static_cast<float>(c_nSymbolSizeY * iy),
                    static_cast<float>(c_nSymbolSizeX * (ix + 1)),
                    static_cast<float>(c_nSymbolSizeY * (iy + 1)));

                if (bgBr != nullptr) {
                    pRenderTarget->FillRectangle(rect, bgBr);
                    bgBr->Release();
                }
                if (br != nullptr) {
                    pRenderTarget->DrawTextA(wCh, 1, pWtTextFormat, rect, br);
                    br->Release();
                }

            }
        }

        pRenderTarget->EndDraw();
    }
}