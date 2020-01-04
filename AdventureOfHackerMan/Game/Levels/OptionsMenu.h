#pragma once
#include "../../Engine/BasicObjects/Slider.h"
#include "../../Engine/BasicObjects/Button.h"

class LOptionsMenu : public Level {
public:
    LOptionsMenu();
    ~LOptionsMenu();

private:
    Button* backButton;
    Slider* volumeSlider;
};