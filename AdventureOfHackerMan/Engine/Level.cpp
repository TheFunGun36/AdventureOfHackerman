#include "Level.h"

Level::Level(int objectNumber, int backgroundId)
    :background(IDR_DEFAULTBG) {
    
    if (backgroundId != 0) {
        Map tmpMap(backgroundId);
        background.append(&tmpMap, 0, 0);
    }

    this->objectCount = objectNumber;
    objectList = new Object * [objectNumber];
}

Level::~Level() {
    for (int i = 0; i < objectCount; i++) {
        objectList[i] = nullptr;
    }
    delete[]objectList;
}
