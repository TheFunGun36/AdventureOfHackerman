#pragma once
#include "../../Engine/BasicObjects/Button.h"

class LClassChoosingMenu :public Level {
public:
    LClassChoosingMenu(LevelArray* lvlArr);

private:
    Button* backButton;
    Button* samuraiButton;
    Button* crusaderButton;
    Button* thiefButton;
};
