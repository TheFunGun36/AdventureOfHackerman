#pragma once
#include "../Engine.h"

class Button : public Object {
public:
    Button(byte posX, byte posY);
    ~Button();

protected:
    Map* textureHovered,
        * textureStatic,
        * texturePressed;

private:
    void eMouseHoverStart() override;
    void eMouseHoverEnd() override;
    void eMouseLmbPressed() override;
    void eMouseLmbReleased() override;
    //virtual void eMouseLmbClick();

};
