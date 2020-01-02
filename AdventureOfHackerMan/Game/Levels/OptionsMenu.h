#pragma once
#include "../../Engine/BasicObjects/Button.h"

class LOptionsMenu : public Level {
public:
    LOptionsMenu();
    ~LOptionsMenu();

private:
    Button* backButton;
};