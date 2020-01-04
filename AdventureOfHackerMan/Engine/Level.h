#pragma once
#include "Object.h"

struct LevelArray {
public:
    LevelArray(Level** levelArray) {
        levelNumber = 0;
        this->levelArray = levelArray;
    }
    void addLevel(Level* level) {
        levelArray[levelNumber++] = level;
    }
    Level** levelArray;
    int levelNumber;
};

class Level {
public:
    Level(LevelArray *lvlArr, int objectNumber, int backgroundId = IDR_EMPTYBG);
    ~Level();

    inline Object** getObjectArray(int* count) {
        *count = objectNumber;
        return objectList;
    }

    virtual void tick(float deltaTime) {};
    Map background;

private:
    friend Object;
    void addObject(Object* obj);
    Object** objectList;
    int objectNumber;
};
