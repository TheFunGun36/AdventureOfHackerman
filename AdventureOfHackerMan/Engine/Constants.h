#pragma once
#include <Windows.h>

namespace c {
    constexpr char processName[] = "please dont kill me";
    constexpr int charsInX = 128;
    constexpr int charsInY = 45;
    constexpr byte clrDefBg = 0;
    constexpr byte clrDefText = ((0 << 4) | (3 << 2) | (0) | (0 << 6));
    const int wndSizeX = GetSystemMetrics(SM_CXSCREEN);
    const int wndSizeY = GetSystemMetrics(SM_CYSCREEN);
    const float symbolSizeY = wndSizeY / float(charsInY);
    const float symbolSizeX = wndSizeX / float(charsInX);//static_cast<int>((2.0 / 3.0)* c::symbolSizeY - 1.0);
}