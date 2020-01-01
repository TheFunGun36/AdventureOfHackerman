#include "Map.h"

Map::Map(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    ch = new sym[sizeY * sizeX];
    std::fill(ch, ch + sizeX * sizeY, 0x00);

    textColor = new clr_t[sizeY * sizeX];
    std::fill(textColor, textColor + sizeX * sizeY, c::clrDefText);

    bgColor = new clr_t[sizeY * sizeX];
    std::fill(bgColor, bgColor + sizeX * sizeY, c::clrDefBg);
}

Map::~Map() {
    delete[](ch);
    delete[](textColor);
    delete[](bgColor);
}

void Map::fill(sym cFiller) {

    std::fill(ch, ch + sizeX * sizeY, cFiller);
}

void Map::load(int rcName) {
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(rcName), "TEXTURE");
    if (hRes != 0) {
        HGLOBAL hBytes = LoadResource(NULL, hRes);
        if (hBytes != 0) {
            LPVOID pData = LockResource(hBytes);
            getMapFromFile(static_cast<char*>(pData), ch, sizeX, sizeY);
            //str;
        } else MessageBox(NULL, "Resource can't be loaded", "ERROR", MB_OK);
    } else MessageBox(NULL, "Resource can't be found", "ERROR", MB_OK);
}

void Map::getMapFromFile(char* map, sym* dest, int sizeX, int sizeY) {
    for (int iy = 0; iy < sizeY; iy++) {
        for (int ix = 0; ix < sizeX; ix++) {
            dest[iy * sizeX + ix] = map[ix + iy * (sizeX + 2)];
        }
    }
}

void Map::append(const Map* other, byte posX = 0, byte posY = 0) {
    for (int iy = 0; iy < other->sizeY; iy++) {
        if (iy >= this->sizeY) {
            break;
        }
        for (int ix = 0; ix < other->sizeX; ix++) {
            if (ix >= this->sizeX) {
                break;
            }
            setSymbol(ix + posX, iy + posY, other->ch[ix + iy * other->sizeX]);
            setTextColor(ix + posX, iy + posY, other->textColor[ix + iy * other->sizeX]);
            setBgColor(ix + posX, iy + posY, other->bgColor[ix + iy * other->sizeX]);
        }
    }
}

void Map::fillColor(clr_t textColor, clr_t bgColor) {
    std::fill(this->textColor, this->textColor + sizeX * sizeY, textColor);
    std::fill(this->bgColor, this->bgColor + sizeX * sizeY, bgColor);
}