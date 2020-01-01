#include "Button.h"

Button::Button(byte posX, byte posY,
    byte sizeX, byte sizeY,
    int textureId, void action())
    :Object(posX, posY, nullptr) {

    activeTexture = new Map(sizeX, sizeY);
    activeTexture->load(textureId);
    bGenerateMouseEvents = true;
    this->action = action;
}

void Button::eMouseLmbClick() {
    action();
}

Button::~Button() {
    delete activeTexture;
}

void Button::eMouseHoverStart() {
    activeTexture->fillColor(MakeMono(90), c::clrDefBg);
}

void Button::eMouseHoverEnd() {
    activeTexture->fillColor(c::clrDefText, c::clrDefBg);
}

void Button::eMouseLmbPressed() {
    activeTexture->fillColor(MakeMono(127), c::clrDefBg);
}

void Button::eMouseLmbReleased() {
    activeTexture->fillColor(MakeMono(90), c::clrDefBg);
}