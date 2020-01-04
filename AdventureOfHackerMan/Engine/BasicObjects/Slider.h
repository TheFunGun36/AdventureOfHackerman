#pragma once
#include "../Engine.h"

class Slider : public Object {
public:
    Slider(Level* level, byte posX, byte posY, byte sliderLength,
        const char* text, void onValueChanged(byte newValue), byte defaultValue = '\x00');
    ~Slider();

protected:
    void emlPressed(byte x, byte y) override;
    void emlReleased(byte x, byte y) override;
    void emhEnd(byte x, byte y) override;
    void emhMoving(byte x, byte y) override;
    virtual void eValueChanged(byte newValue);
    void (*onValueChanged)(byte n);

    byte realLength,
        sliderLength;
    byte currentValue;
    char* basicTexture;
    bool isMousePressed;
};