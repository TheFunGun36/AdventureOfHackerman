#pragma once
#include "../../Engine/BasicObjects/Button.h"

class ExitButton : public Button {
public:
    ExitButton(byte posX, byte posY);

private:
    void eMouseLmbClick() override;
};
