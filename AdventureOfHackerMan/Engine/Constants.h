#pragma once
#include <Windows.h>

namespace constants {
    constexpr char processName[] = "please dont kill me";
    constexpr int charsInX = 128;
    constexpr int charsInY = 45;
    constexpr byte clrDefBg = 0;
    constexpr byte clrDefText = ((0 << 4) | (3 << 2) | (0) | (0 << 6));
    const int wndSizeX = GetSystemMetrics(SM_CXSCREEN);
    const int wndSizeY = GetSystemMetrics(SM_CYSCREEN);
    const float charSizeY = wndSizeY / float(charsInY);
    const float charSizeX = wndSizeX / float(charsInX);
}