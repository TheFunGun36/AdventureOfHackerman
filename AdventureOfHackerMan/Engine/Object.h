#pragma once
#include <chrono>
#include "Map.h"

namespace engine {
    void computeGameLogic();
}

class Object {
public:

    Map* getTexture();
    byte posX, posY;

    Object(byte posX = '\x00', byte posY = '\x00', Map* texture = nullptr);
    ~Object();

protected:
    virtual void eTick(float deltaTime) {}

    bool bGenerateMouseEvents;

    virtual void eMouseHoverStart(byte posX, byte posY) {}
    virtual void eMouseHoverEnd(byte posX, byte posY) {}
    virtual void eMouseHoverTick(byte posX, byte posY) {}
    virtual void eMouseMoving(byte posX, byte posY) {}

    virtual void eMouseLmbPressed(byte x, byte y) {}
    virtual void eMouseLmbReleased(byte x, byte y) {}
    virtual void eMouseLmbClick(byte x, byte y) {}

    virtual void eMouseRmbDown(byte x, byte y) {}
    virtual void eMouseRmbUp(byte x, byte y) {}
    virtual void eMouseRmbClick(byte x, byte y) {}

    virtual void eKeyDownEvent(WPARAM key) {}
    virtual void eKeyUpEvent(WPARAM key) {}
    Map* activeTexture;

private:
    bool bMouseIsHovering;
    bool bLmbDownHandled;
    bool bRmbDownHandled;

    //special 4 our friend :p
    void getPosition(byte* posX, byte* posY, byte* posX2, byte* posY2);

    friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    friend void engine::computeGameLogic();
};
