#pragma once
#include "Button.h"

class OptionsButton :public Button {
public:
    OptionsButton(byte posX, byte posY);

private:
    void eMouseLmbClick() override final;
};
