#pragma once
#include <string>
#include <Windows.h>
#include "../Resources/resource.h"
#include "Constants.h"

//#define GETINDEX(x,y) (y * c::charsInX + x)
//#define GETCH(strArr, x, y) strArr[y][x]
//#define SETCH(strArr, x, y, ch) strArr[y][x] = ch

/*
  00RRGGBB
*/
typedef byte clr_t;
typedef char sym;

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
    int sizeX, sizeY;


    Map(int sizeX, int sizeY);
    ~Map();
    const inline sym getSymbol(int x, int y) {
        return ch[x + y * sizeX];
    }
    const inline clr_t getTextColor(int x, int y) {
        return textColor[x + y * sizeX];
    }
    const inline clr_t getBgColor(int x, int y) {
        return bgColor[x + y * sizeX];
    }
    inline void setSymbol(int x, int y, sym v) {
        ch[x + y * sizeX] = v;
    }
    inline void setTextColor(int x, int y, clr_t v) {
        textColor[x + y * sizeX] = v;
    }
    inline void setBgColor(int x, int y, clr_t v) {
        bgColor[x + y * sizeX] = v;
    }
    void fill(sym cFiller);
    void fillColor(clr_t textColor, clr_t bgColor);
    void load(int rcName);
    void append(const Map* other, byte posX, byte posY);

private:
    sym* ch;

    clr_t* textColor;
    clr_t* bgColor;

    static void getMapFromFile(char* map, sym* dest, int sizeX, int sizeY);
};