#include "Button.h"

Button::Button(Level* level, byte posX, byte posY,
    int textureId, void action())
    :Object(level, posX, posY, nullptr) {

    activeTexture = new Map(textureId);
    //activeTexture->load(textureId);
    generateMouseEvents = true;
    this->action = action;
}

void Button::emlClick(byte, byte) {
    action();
}

Button::~Button() {
    delete activeTexture;
}

void Button::emhStart(byte, byte) {
    activeTexture->fillColor(MakeMono(90), constants::clrDefBg);
}

void Button::emhEnd(byte, byte) {
    activeTexture->fillColor(constants::clrDefText, constants::clrDefBg);
}

void Button::emlPressed(byte, byte) {
    activeTexture->fillColor(MakeMono(127), constants::clrDefBg);
}

void Button::emlReleased(byte, byte) {
    activeTexture->fillColor(MakeMono(90), constants::clrDefBg);
}