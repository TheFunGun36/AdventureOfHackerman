#pragma once
#include "Button.h"

class StartButton :public Button {
public:
    StartButton(byte posX, byte posY);

private:
    void eMouseLmbClick() override final;
};
