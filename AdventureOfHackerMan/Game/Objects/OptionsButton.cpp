/*#include "OptionsButton.h"

OptionsButton::OptionsButton(byte posX, byte posY)
    :Button(posX, posY) {

    this->textureStatic = new Map(37, 6);
    this->texturePressed = new Map(37, 6);
    this->textureHovered = new Map(37, 6);

    this->textureStatic->load(IDR_OPTIONSBUTTON);
    this->texturePressed->load(IDR_OPTIONSBUTTON);
    this->textureHovered->load(IDR_OPTIONSBUTTON);

    this->activeTexture = textureStatic;

    this->texturePressed->fillColor(MakeMono(127), MakeMono(0));
    this->textureHovered->fillColor(MakeMono(100), MakeMono(0));
}

void OptionsButton::eMouseLmbClick() {
    MessageBox(NULL, "There is no options", "ya pashka ti ne pashka ya pashka ti ne pashka", MB_OK);
}*/