#pragma once
#include <Windows.h>

constexpr char c_sProcessName[] = "please dont kill me";
constexpr int c_nSymbolSizeY = 24;
constexpr int c_nSymbolSizeX = static_cast<int>((2.0 / 3.0)* c_nSymbolSizeY - 1.0);
constexpr int c_nCharsInX = 128;
constexpr int c_nCharsInY = 45;
constexpr int c_nWndSizeX = c_nCharsInX * c_nSymbolSizeX;
constexpr int c_nWndSizeY = c_nCharsInY * c_nSymbolSizeY;
constexpr byte c_clrDefBg = 0;
constexpr byte c_clrDefText = ((0 << 4) | (3 << 2) | (0) | (0 << 6));
