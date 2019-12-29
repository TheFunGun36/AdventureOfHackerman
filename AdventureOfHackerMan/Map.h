#pragma once
#include <string>
#include <Windows.h>
#include "resource.h"
#include "Constants.h"

//#define GETINDEX(x,y) (y * c_nCharsInX + x)
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

    sym** ch;//[c_nCharsInY];

    clr_t** textColor;//[c_nCharsInY][c_nCharsInX];
    clr_t** bgColor;//[c_nCharsInY][c_nCharsInX];

    Map(int sizeX, int sizeY);
    ~Map();

    void fill(sym cFiller);
    void fillColor(clr_t textColor, clr_t bgColor);
    void load(int rcName);
    void append(const Map* other, byte posX, byte posY);

private:
    static void getMapFromFile(char* map, sym** dest, int sizeX, int sizeY);
};