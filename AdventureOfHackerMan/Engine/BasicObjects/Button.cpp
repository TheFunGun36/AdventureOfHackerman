#include "Button.h"

Button::Button(byte posX, byte posY,
    byte sizeX, byte sizeY,
    int textureId, void action())
    :Object(posX, posY, nullptr) {

    activeTexture = new Map(textureId);
    //activeTexture->load(textureId);
    bGenerateMouseEvents = true;
    this->action = action;
}

void Button::eMouseLmbClick(byte, byte) {
    action();
}

Button::~Button() {
    delete activeTexture;
}

void Button::eMouseHoverStart(byte, byte) {
    activeTexture->fillColor(MakeMono(90), c::clrDefBg);
}

void Button::eMouseHoverEnd(byte, byte) {
    activeTexture->fillColor(c::clrDefText, c::clrDefBg);
}

void Button::eMouseLmbPressed(byte, byte) {
    activeTexture->fillColor(MakeMono(127), c::clrDefBg);
}

void Button::eMouseLmbReleased(byte, byte) {
    activeTexture->fillColor(MakeMono(90), c::clrDefBg);
}