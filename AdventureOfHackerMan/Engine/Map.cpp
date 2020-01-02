#include "Map.h"

Map::Map(int rcName) {
    ch = nullptr;
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(rcName), "TEXTURE");
    if (hRes != 0) {
        HGLOBAL hBytes = LoadResource(NULL, hRes);
        if (hBytes != 0) {

            LPVOID pData = LockResource(hBytes);
            char* map = static_cast<char*>(pData);
            int c = 0;
            std::string str;

            if ((map[0] == 'B') && (map[1] == 'G')) {
                c = 4;
                sizeX = c::charsInX;
                sizeY = c::charsInY;
            }
            else {
                for (int i = 0; map[i] != ' '; i++) {
                    c++;
                    str.push_back(map[i]);
                }
                sizeX = std::stoi(str);
                c++;
                str.clear();
                for (int i = c; map[i] != '\r'; i++) {
                    c++;
                    str.push_back(map[i]);
                }
                sizeY = std::stoi(str);
                c += 2;
            }
            
            ch = new sym[sizeX * sizeY];

            for (int iy = 0; iy < sizeY; iy++) {
                for (int ix = 0; ix < sizeX; ix++) {
                    ch[iy * sizeX + ix] = map[ix + iy * (sizeX + 2) + c];
                }
            }
            //str;
        } else MessageBox(NULL, "Resource can't be loaded", "ERROR", MB_OK);
    } else MessageBox(NULL, "Resource can't be found", "ERROR", MB_OK);

    //ch = new sym[sizeY * sizeX];
    //std::fill(ch, ch + sizeX * sizeY, 0x00);

    textColor = new clr_t[sizeY * sizeX];
    std::fill(textColor, textColor + sizeX * sizeY, c::clrDefText);

    bgColor = new clr_t[sizeY * sizeX];
    std::fill(bgColor, bgColor + sizeX * sizeY, c::clrDefBg);
}

Map::Map(byte sizeX, byte sizeY) {
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

void Map::set(sym* texture) {
    for (int i = 0; i < sizeX * sizeY; i++) {
        ch[i] = texture[i];
    }
}

void Map::fillColor(clr_t textColor, clr_t bgColor) {
    std::fill(this->textColor, this->textColor + sizeX * sizeY, textColor);
    std::fill(this->bgColor, this->bgColor + sizeX * sizeY, bgColor);
}