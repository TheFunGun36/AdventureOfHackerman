#pragma once
#include "../../Engine/BasicObjects/Slider.h"
#include "../../Engine/BasicObjects/Button.h"

class LOptionsMenu : public Level {
public:
    LOptionsMenu(LevelArray *lvlArr);
    //~LOptionsMenu();

private:
    Button* backButton;
    Slider* volumeSlider;
};