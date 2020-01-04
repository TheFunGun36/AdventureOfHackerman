#include "Level.h"

Level::Level(int objectNumber, int backgroundId)
    :background(backgroundId) {
    
    this->objectNumber = objectNumber;
    objectList = new Object * [objectNumber];
}

Level::~Level() {
    for (int i = 0; i < objectNumber; i++) {
        objectList[i] = nullptr;
    }
    delete[]objectList;
}
