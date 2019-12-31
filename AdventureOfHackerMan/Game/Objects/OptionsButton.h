#pragma once
#include "../../Engine/BasicObjects/Button.h"

class OptionsButton :public Button {
public:
    OptionsButton(byte posX, byte posY);

private:
    void eMouseLmbClick() override final;
};
