#pragma once
#include "../../Engine/BasicObjects/Slider.h"
#include "../../Engine/BasicObjects/Button.h"

class LMainMenu : public Level{
public:
    LMainMenu();
    ~LMainMenu();

private:
    Button* startButton;
    Button* optionsButton;
    Button* exitButton;
};