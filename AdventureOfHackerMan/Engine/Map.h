#pragma once
#include <string>
#include <Windows.h>
#include "../Resources/resource.h"
#include "Constants.h"

typedef byte color;

/*#define Map::getRed(x) ((x & 48) >> 4)
#define Map::getGreen(x) ((x & 12) >> 2)
#define Map::getBlue(x) (x & 3)
#define Map::getMono(x) (x & 127)
#define Map::expandColor(x, r, g, b) r = (x & 128) ? (static_cast<float>(Map::getMono(x)) / 127.0f) : ((Map::getRed(x) / 3.0f) / (((x & 64) >> 6) + 1)); \
g = (x & 128) ? (static_cast<float>(Map::getMono(x)) / 127.0f) : ((Map::getGreen(x) / 3.0f) / (((x & 64) >> 6) + 1)); \
b = (x & 128) ? (static_cast<float>(Map::getMono(x)) / 127.0f) : ((Map::getBlue(x) / 3.0f) / (((x & 64) >> 6) + 1))

//Maximum values: 3, 3, 3, 1
#define Map::makeRgb(r, g, b, d) ((r << 4) | (g << 2) | (b) | (d << 6))
#define Map::createMono(c) (128 | c)*/

struct Map {
public:
    byte sizeX, sizeY;

    Map(int rcName);
    Map(byte sizeX, byte sizeY);
    ~Map();

    static const FORCEINLINE byte getRed(byte x) { return (x & 48) >> 4; }
    static const FORCEINLINE byte getGreen(byte x) { return (x & 12) >> 2; }
    static const FORCEINLINE byte getBlue(byte x) { return x & 3; }
    static const FORCEINLINE byte getMono(byte x) { return x & 127; }

    static const FORCEINLINE void expandColor(byte x, float& r, float& g, float& b) {
        if (x & 128) {
            r = getMono(x) / 127.0f;
            g = r;
            b = r;
        }
        else {
            r = (getRed(x) / 3.0f) / (((x & 64) >> 6) + 1);
            g = (getGreen(x) / 3.0f) / (((x & 64) >> 6) + 1);
            b = (getBlue(x) / 3.0f) / (((x & 64) >> 6) + 1);
        }
    }

    static const FORCEINLINE byte createRgb(byte r, byte g, byte b, bool isDark) {
#ifndef NDEBUG
        if (r > 3) {
            MessageBox(NULL, "Red is too big! Max 3", "Map::createRgb() says:", MB_OK);
        }
        if (g > 3) {
            MessageBox(NULL, "Green is too big! Max 3", "Map::createRgb() says:", MB_OK);
        }
        if (b > 3) {
            MessageBox(NULL, "Blue is too big! Max 3", "Map::createRgb() says:", MB_OK);
        }
#endif
        return (r << 4) | (g << 2) | (b) | (static_cast<byte>(isDark) << 6);
    }
    static const FORCEINLINE byte createMono(byte x) {
#ifndef NDEBUG
        if (x > 127) {
            MessageBox(NULL, "Value is too big! Max 127", "Map::createMono() says:", MB_OK);
        }
#endif
        return 128 | x;
    }

    const FORCEINLINE char getSymbol(byte x, byte y) {
#ifndef NDEBUG
        if (x > sizeX || y > sizeY) {
            MessageBox(NULL, "Out of bounds!", "Map::getSymbol() says:", MB_OK);
            return '\x00';
        }
#endif
        return symbol[x + static_cast<int>(y)* sizeX];
    }
    const FORCEINLINE color getSymbolColor(byte x, byte y) {
#ifndef NDEBUG
        if (x > sizeX || y > sizeY) {
            MessageBox(NULL, "Out of bounds!", "Map::getSymbol() says:", MB_OK);
            return '\x00';
        }
#endif
        return symbolColor[x + static_cast<int>(y)* sizeX];
    }
    const FORCEINLINE color getSymbolBgColor(byte x, byte y) {
#ifndef NDEBUG
        if (x > sizeX || y > sizeY) {
            MessageBox(NULL, "Out of bounds!", "Map::getSymbol() says:", MB_OK);
            return '\x00';
        }
#endif
        return symbolBgColor[x + static_cast<int>(y)* sizeX];
    }

    FORCEINLINE void setSymbol(byte x, byte y, char v) {
#ifndef NDEBUG
        if (x > sizeX || y > sizeY) {
            MessageBox(NULL, "Out of bounds!", "Map::getSymbol() says:", MB_OK);
            return;
        }
#endif
        symbol[x + static_cast<int>(y)* sizeX] = v;
    }
    FORCEINLINE void setSymbolColor(byte x, byte y, color v) {
#ifndef NDEBUG
        if (x > sizeX || y > sizeY) {
            MessageBox(NULL, "Out of bounds!", "Map::getSymbol() says:", MB_OK);
            return;
        }
#endif
        symbolColor[x + static_cast<int>(y)* sizeX] = v;
    }
    FORCEINLINE void setSymbolBgColor(byte x, byte y, color v) {
#ifndef NDEBUG
        if (x > sizeX || y > sizeY) {
            MessageBox(NULL, "Out of bounds!", "Map::getSymbol() says:", MB_OK);
            return;
        }
#endif
        symbolBgColor[x + static_cast<int>(y)* sizeX] = v;
    }

    void fill(char ciller);
    void fillColor(color symbolColor, color symbolBgColor);
    void set(char* texture);

    void append(const Map* other, byte posX, byte posY);

private:
    char* symbol;
    color* symbolColor;
    color* symbolBgColor;
};