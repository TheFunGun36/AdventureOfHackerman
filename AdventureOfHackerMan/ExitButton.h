#pragma once
#include "Button.h"

class ExitButton : public Button {
public:
    ExitButton(byte posX, byte posY);

private:
    void eMouseLmbClick() override;
};
