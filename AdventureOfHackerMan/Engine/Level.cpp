#include "Level.h"

Level::Level(LevelArray *lvlArr, int objectNumber, int backgroundId)
    :background(backgroundId) {
    this->objectNumber = 0;
    objectList = new Object * [objectNumber];
    lvlArr->addLevel(this);
}

Level::~Level() {
    for (int i = 0; i < objectNumber; i++) {
        delete objectList[i];
        objectList[i] = nullptr;
    }
    delete[]objectList;
}

void Level::addObject(Object* obj) {
    objectList[objectNumber++] = obj;
}