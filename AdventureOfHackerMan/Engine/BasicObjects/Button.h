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
    virtual void eMouseHoverStart(byte, byte) override;
    virtual void eMouseHoverEnd(byte, byte) override;
    virtual void eMouseLmbPressed(byte, byte) override;
    virtual void eMouseLmbReleased(byte, byte) override;

private:
    void eMouseLmbClick(byte, byte) override;

};
