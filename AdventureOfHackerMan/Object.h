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
    virtual void eTick(float deltaTime) {};

    bool bGenerateMouseEvents;

    virtual void eMouseHoverStart() {};
    virtual void eMouseHoverEnd() {};
    virtual void eMouseHoverTick() {};

    virtual void eMouseLmbPressed() {};
    virtual void eMouseLmbReleased() {};
    virtual void eMouseLmbClick() {};

    virtual void eMouseRmbDown() {};
    virtual void eMouseRmbUp() {};
    virtual void eMouseRmbClick() {};

    virtual void eKeyDownEvent(WPARAM key) {};
    virtual void eKeyUpEvent(WPARAM key) {};
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
