#include "Map.h"

Map::Map(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    ch = new sym * [sizeY];
    for (int i = 0; i < sizeY; i++) {
        ch[i] = new sym[sizeX];
        memset(ch[i], 0, sizeof(sym) * sizeX);
    }

    textColor = new clr_t * [sizeY];
    for (int i = 0; i < sizeY; i++) {
        textColor[i] = new clr_t[sizeX];
        memset(textColor[i], c_clrDefText, sizeof(clr_t) * sizeX);
    }

    bgColor = new clr_t * [sizeY];
    for (int i = 0; i < sizeY; i++) {
        bgColor[i] = new clr_t[sizeX];
        memset(bgColor[i], c_clrDefBg, sizeof(clr_t) * sizeX);
    }

    fill(' ');
}

Map::~Map() {
    for (int i = 0; i < sizeY; i++) {
        delete[](ch[i]);
    }
    delete[](ch);

    for (int i = 0; i < sizeY; i++) {
        delete[](textColor[i]);
    }
    delete[](textColor);

    for (int i = 0; i < sizeY; i++) {
        delete[](bgColor[i]);
    }
    delete[](bgColor);
}

void Map::fill(sym cFiller) {
    for (int i = 0; i < sizeY; i++) {
        memset(ch[i], cFiller, sizeof(sym) * sizeX);
    }
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

void Map::getMapFromFile(char* map, sym** dest, int sizeX, int sizeY) {
    for (int iy = 0; iy < sizeY; iy++) {
        for (int ix = 0; ix < sizeX; ix++) {
            dest[iy][ix] = map[ix + (iy * (sizeX + 2))];
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
            ch[iy + posY][ix + posX] = other->ch[iy][ix];
            textColor[iy + posY][ix + posX] = other->textColor[iy][ix];
            bgColor[iy + posY][ix + posX] = other->bgColor[iy][ix];
        }
    }
}

void Map::fillColor(clr_t textColor, clr_t bgColor) {
    for (int iy = 0; iy < sizeY; iy++) {
        if (iy >= this->sizeY) {
            break;
        }
        for (int ix = 0; ix < sizeX; ix++) {
            if (ix >= this->sizeX) {
                break;
            }
            this->textColor[iy][ix] = textColor;
            this->bgColor[iy][ix] = bgColor;
        }
    }
}