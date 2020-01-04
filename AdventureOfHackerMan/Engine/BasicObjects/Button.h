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
    virtual void emhStart(byte, byte) override;
    virtual void emhEnd(byte, byte) override;
    virtual void emlPressed(byte, byte) override;
    virtual void emlReleased(byte, byte) override;

private:
    void emlClick(byte, byte) override;

};
