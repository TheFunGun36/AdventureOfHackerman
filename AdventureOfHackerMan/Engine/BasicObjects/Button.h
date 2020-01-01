#pragma once
#include "../Engine.h"

class Button : public Object {
public:
    Button(byte posX, byte posY,
        byte sizeX, byte sizeY,
        int textureId, void action());
    ~Button();

protected:
    void (*action)();
    virtual void eMouseHoverStart() override;
    virtual void eMouseHoverEnd() override;
    virtual void eMouseLmbPressed() override;
    virtual void eMouseLmbReleased() override;

private:
    void eMouseLmbClick();

};
