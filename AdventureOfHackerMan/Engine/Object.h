#pragma once
#include <chrono>
#include "Map.h"

namespace engine {
    void computeGameLogic();
}

class Object {
public:

    const inline Map* getTexture() {
        return activeTexture;
    }
    byte posX, posY;

    Object(byte posX = '\x00', byte posY = '\x00', Map* texture = nullptr);
    ~Object();

protected:
    virtual void eTick(float deltaTime) {}

    bool generateMouseEvents;

    virtual void emhStart(byte x, byte y) {}
    virtual void emhEnd(byte x, byte y) {}
    virtual void emhTick(byte x, byte y) {}
    virtual void emhMoving(byte x, byte y) {}

    virtual void emlPressed(byte x, byte y) {}
    virtual void emlReleased(byte x, byte y) {}
    virtual void emlClick(byte x, byte y) {}

    virtual void emrPressed(byte x, byte y) {}
    virtual void emrReleased(byte x, byte y) {}
    virtual void emrClick(byte x, byte y) {}

    virtual void eKeyPressed(WPARAM key) {}
    virtual void eKeyReleased(WPARAM key) {}
    Map* activeTexture;

private:
    bool isMouseHovering;
    bool isLmbDownHandled;
    bool isRmbDownHandled;

    //special 4 our friend :p
    const void getPosition(byte* posX, byte* posY, byte* posX2, byte* posY2);

    friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    friend void engine::computeGameLogic();
};
