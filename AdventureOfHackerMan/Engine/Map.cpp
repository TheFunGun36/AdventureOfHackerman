#include "Map.h"

Map::Map(int rcName) {
    symbol = nullptr;
    HRSRC source = FindResource(NULL, MAKEINTRESOURCE(rcName), "TEXTURE");
    HGLOBAL resource = LoadResource(NULL, source);
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

    symbol = new char[sizeX * sizeY];

    for (int iy = 0; iy < sizeY; iy++) {
        memcpy(symbol + sizeX * iy, data + iy * (sizeX + 2) + charactersToSkip, sizeX);
    }

    symbolColor = new color[sizeY * sizeX];
    std::fill(symbolColor, symbolColor + sizeX * sizeY, constants::clrDefText);

    symbolBgColor = new color[sizeY * sizeX];
    std::fill(symbolBgColor, symbolBgColor + sizeX * sizeY, constants::clrDefBg);
}

Map::Map(byte sizeX, byte sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    symbol = new char[sizeY * sizeX];
    std::fill(symbol, symbol + sizeX * sizeY, '\x00');

    symbolColor = new color[sizeY * sizeX];
    std::fill(symbolColor, symbolColor + sizeX * sizeY, constants::clrDefText);

    symbolBgColor = new color[sizeY * sizeX];
    std::fill(symbolBgColor, symbolBgColor + sizeX * sizeY, constants::clrDefBg);
}

Map::~Map() {
    delete[](symbol);
    delete[](symbolColor);
    delete[](symbolBgColor);
}

void Map::fill(char cFiller) {
    std::fill(symbol, symbol + sizeX * sizeY, cFiller);
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
            setSymbol(ix + posX, iy + posY, other->symbol[ix + iy * other->sizeX]);
            setSymbolColor(ix + posX, iy + posY, other->symbolColor[ix + iy * other->sizeX]);
            setSymbolBgColor(ix + posX, iy + posY, other->symbolBgColor[ix + iy * other->sizeX]);
        }
    }
}

void Map::set(char* texture) {
    for (int i = 0; i < sizeX * sizeY; i++) {
        symbol[i] = texture[i];
    }
}

void Map::fillColor(color symbolColor, color symbolBgColor) {
    std::fill(this->symbolColor, this->symbolColor + sizeX * sizeY, symbolColor);
    std::fill(this->symbolBgColor, this->symbolBgColor + sizeX * sizeY, symbolBgColor);
}