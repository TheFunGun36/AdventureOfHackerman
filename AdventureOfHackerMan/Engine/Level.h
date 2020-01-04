#pragma once
#include "Object.h"

class Level {
public:
    Level(int objectNumber, int backgroundId = 0);
    ~Level();

    inline Object** getObjectArray(int* count) {
        *count = objectNumber;
        return objectList;
    }

    virtual void tick(float deltaTime) {};
    Map background;

protected:
    Object** objectList;
    int objectNumber;
};
