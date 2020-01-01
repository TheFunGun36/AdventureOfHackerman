#pragma once
#include "../../Engine/BasicObjects/Button.h"
//#include "../Objects/ExitButton.h"
//#include "../Objects/OptionsButton.h"
//#include "../Objects/StartButton.h"

class LMainMenu : public Level {
public:
    LMainMenu();
    ~LMainMenu();

private:
    Button* startButton;
    Button* optionsButton;
    Button* exitButton;

};