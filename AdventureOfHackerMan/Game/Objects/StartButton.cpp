#include "StartButton.h"

StartButton::StartButton(byte posX, byte posY)
    :Button(posX, posY) {

    this->textureStatic = new Map(27, 5);
    this->texturePressed = new Map(27, 5);
    this->textureHovered = new Map(27, 5);

    this->textureStatic->load(IDR_STARTBUTTON);
    this->texturePressed->load(IDR_STARTBUTTON);
    this->textureHovered->load(IDR_STARTBUTTON);

    this->activeTexture = textureStatic;

    this->texturePressed->fillColor(MakeMono(127), MakeMono(0));
    this->textureHovered->fillColor(MakeMono(100), MakeMono(0));
}

void StartButton::eMouseLmbClick() {
    MessageBox(NULL, "There is no game", "fuk u", MB_OK);
    engine::shutdown();
}