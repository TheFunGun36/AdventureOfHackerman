#pragma once
#include <string>
#include <Windows.h>
#include "../Resources/resource.h"
#include "Constants.h"

typedef byte color;

#define GetRed(x) ((x & 48) >> 4)
#define GetGreen(x) ((x & 12) >> 2)
#define GetBlue(x) (x & 3)
#define GetMono(x) (x & 127)
#define ExpandColor(x, r, g, b) r = (x & 128) ? (static_cast<float>(GetMono(x)) / 127.0f) : ((GetRed(x) / 3.0f) / (((x & 64) >> 6) + 1)); \
g = (x & 128) ? (static_cast<float>(GetMono(x)) / 127.0f) : ((GetGreen(x) / 3.0f) / (((x & 64) >> 6) + 1)); \
b = (x & 128) ? (static_cast<float>(GetMono(x)) / 127.0f) : ((GetBlue(x) / 3.0f) / (((x & 64) >> 6) + 1))

//Maximum values: 3, 3, 3, 1
#define MakeRgb(r, g, b, d) ((r << 4) | (g << 2) | (b) | (d << 6))
#define MakeMono(c) (128 | c)

struct Map {
public:
    byte sizeX, sizeY;

    Map(int rcName);
    Map(byte sizeX, byte sizeY);
    ~Map();

    const inline char getSymbol(int x, int y) { return symbol[x + y * sizeX]; }
    const inline color getSymbolColor(int x, int y) { return symbolColor[x + y * sizeX]; }
    const inline color getSymbolBgColor(int x, int y) { return symbolBgColor[x + y * sizeX]; }

    inline void setSymbol(int x, int y, char v) { symbol[x + y * sizeX] = v; }
    inline void setSymbolColor(int x, int y, color v) { symbolColor[x + y * sizeX] = v; }
    inline void setSymbolBgColor(int x, int y, color v) { symbolBgColor[x + y * sizeX] = v; }

    void fill(char cFiller);
    void fillColor(color symbolColor, color symbolBgColor);
    void set(char* texture);

    void append(const Map* other, byte posX, byte posY);

private:
    char* symbol;
    color* symbolColor;
    color* symbolBgColor;
};