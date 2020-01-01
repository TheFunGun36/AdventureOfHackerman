/*#include "ExitButton.h"
#include "../Game.h"

ExitButton::ExitButton(byte posX, byte posY)
    :Button(posX, posY) {

    this->textureStatic = new Map(20, 5);
    this->texturePressed = new Map(20, 5);
    this->textureHovered = new Map(20, 5);

    this->textureStatic->load(IDR_EXITBUTTON);
    this->texturePressed->load(IDR_EXITBUTTON);
    this->textureHovered->load(IDR_EXITBUTTON);

    this->activeTexture = textureStatic;

    this->texturePressed->fillColor(MakeMono(127), MakeMono(0));
    this->textureHovered->fillColor(MakeMono(100), MakeMono(0));
}

void ExitButton::eMouseLmbClick() {
    engine::shutdown();
}

*/