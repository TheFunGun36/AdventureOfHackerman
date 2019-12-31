#include "Button.h"

Button::Button(byte posX, byte posY)
    :Object(posX, posY, nullptr) {
    bGenerateMouseEvents = true;
    textureHovered = nullptr;
    texturePressed = nullptr;
    textureStatic = nullptr;
    activeTexture = nullptr;
    //texturePressed->fillColor(MakeMono(127), MakeMono(10));

    //textureHovered->fillColor(MakeMono(100), MakeMono(5));

}

Button::~Button() {
    delete textureStatic;
    delete texturePressed;
    delete textureHovered;
}

void Button::eMouseHoverStart() {
    activeTexture = textureHovered;
    //engine::redraw();
}

void Button::eMouseHoverEnd() {
    activeTexture = textureStatic;
    //engine::redraw();
}

void Button::eMouseLmbPressed() {
    activeTexture = texturePressed;
    //engine::redraw();
}

void Button::eMouseLmbReleased() {
    activeTexture = textureHovered;
    //engine::redraw();
}