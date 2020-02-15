#include "Map.h"

Map::Map(int rcName) {
    if (rcName == IDR_EMPTYBG) {
        sizeX = constants::charsInX;
        sizeY = constants::charsInY;

        symbol = new char[static_cast<int>(sizeX)* sizeY];
        std::fill(symbol, symbol + static_cast<int>(sizeX)* sizeY, ' ');
    }
    else {
        symbol = nullptr;
        HRSRC source = FindResource(NULL, MAKEINTRESOURCE(rcName), "TEXTURE");
        HGLOBAL resource = LoadResource(NULL, source);//dfgdfg
        LPVOID rawData = LockResource(resource);
        char* data = static_cast<char*>(rawData);
        int charactersToSkip = 0;
        std::string firstLine;

        if ((data[0] == 'B') && (data[1] == 'G')) {
            charactersToSkip = 4;
            sizeX = constants::charsInX;
            sizeY = constants::charsInY;
        }
        else {
#ifndef NDEBUG
            if (data[0] < '0' || data[0] > '9') {
                MessageBox(NULL, "There is no size in file! Unexpected behaviour", "Map::Map(int) says:", MB_OK);
            }
#endif
            for (int i = 0; data[i] != ' '; i++) {
                charactersToSkip++;
                firstLine.push_back(data[i]);
            }

            sizeX = std::stoi(firstLine);
            charactersToSkip++;
            firstLine.clear();

            for (int i = charactersToSkip; data[i] != '\r'; i++) {
                charactersToSkip++;
                firstLine.push_back(data[i]);
            }

            sizeY = std::stoi(firstLine);
            charactersToSkip += 2;
        }

        symbol = new char[static_cast<int>(sizeX)* sizeY];

        for (int iy = 0; iy < sizeY; iy++) {
            memcpy(symbol + static_cast<int>(sizeX)* iy, data + iy * (static_cast<int>(sizeX) + 2) + charactersToSkip, sizeX);
        }
    }

    symbolColor = new color[static_cast<int>(sizeX)* sizeY];
    std::fill(symbolColor, symbolColor + static_cast<int>(sizeX)* sizeY, constants::clrDefText);

    symbolBgColor = new color[static_cast<int>(sizeX)* sizeY];
    std::fill(symbolBgColor, symbolBgColor + static_cast<int>(sizeX)* sizeY, constants::clrDefBg);
}

Map::Map(byte sizeX, byte sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    symbol = new char[sizeY * static_cast<int>(sizeX)];
    std::fill(symbol, symbol + static_cast<int>(sizeX)* sizeY, '\x00');

    symbolColor = new color[sizeY * static_cast<int>(sizeX)];
    std::fill(symbolColor, symbolColor + static_cast<int>(sizeX)* sizeY, constants::clrDefText);

    symbolBgColor = new color[sizeY * static_cast<int>(sizeX)];
    std::fill(symbolBgColor, symbolBgColor + static_cast<int>(sizeX)* sizeY, constants::clrDefBg);
}

Map::~Map() {
    delete[](symbol);
    delete[](symbolColor);
    delete[](symbolBgColor);
}

void Map::fill(char cFiller) {
    std::fill(symbol, symbol + static_cast<int>(sizeX)* sizeY, cFiller);
}

void Map::append(const Map* other, byte posX = 0, byte posY = 0) {
    for (int iy = 0; iy < other->sizeY; iy++) {
#ifndef NDEBUG
        if (iy >= this->sizeY) {
            MessageBox(NULL, "Other map is too big!", "Map::append() says:", MB_OK);
            break;
        }
#endif
        for (int ix = 0; ix < other->sizeX; ix++) {
#ifndef NDEBUG
            if (ix >= this->sizeX) {
                MessageBox(NULL, "Other map is too big!", "Map::append() says:", MB_OK);
                break;
            }
#endif
            setSymbol(ix + posX, iy + posY, other->symbol[ix + iy * other->sizeX]);
            setSymbolColor(ix + posX, iy + posY, other->symbolColor[ix + iy * other->sizeX]);
            setSymbolBgColor(ix + posX, iy + posY, other->symbolBgColor[ix + iy * other->sizeX]);
        }
    }
}

void Map::set(char* texture) {
#ifndef NDEBUG
    for (int i = 0; i < sizeX * sizeY; i++) {
        if (texture[i] == '\0') {
            MessageBox(NULL, "Texture is too small!", "Map::set() says:", MB_OK);
        }
        symbol[i] = texture[i];
    }
#endif
    //TODO: else: memcpy... endif
    //just because testing
    memcpy(symbol, texture, static_cast<int>(sizeX)* sizeY);
}

void Map::fillColor(color symbolColor, color symbolBgColor) {
    std::fill(this->symbolColor, this->symbolColor + static_cast<int>(sizeX)* sizeY, symbolColor);
    std::fill(this->symbolBgColor, this->symbolBgColor + static_cast<int>(sizeX)* sizeY, symbolBgColor);
}