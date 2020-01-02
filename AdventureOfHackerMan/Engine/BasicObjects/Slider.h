#include "../Engine.h"

class Slider : public Object {
public:
    Slider(byte posX, byte posY, byte length,
        const char* text, void valueChanged(byte newValue), byte defaultValue = '\x00');
    ~Slider();

protected:
    void eMouseLmbPressed(byte x, byte y) override;
    void eMouseLmbReleased(byte x, byte y) override;
    void eMouseHoverEnd(byte x, byte y) override;
    void eMouseMoving(byte x, byte y) override;
    virtual void eValueChanged(byte newValue);
    void (*valueChanged)(byte n);

    byte length,
        sliderLength;
    byte currentValue;
    sym* basicTexture;
    bool isMousePressed;
};