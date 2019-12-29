#pragma once
#include "Object.h"

class Level {
public:
    Level(int objectNumber, int backgroundId = 0);
    ~Level();

    Object** getObjectArray(int* count) {
        *count = objectCount;
        return objectList;
    }

    virtual void tick(float deltaTime) {};
    Map background;

protected:
    Object** objectList;
    int objectCount;
};
