#pragma once
#include "ExitButton.h"
#include "OptionsButton.h"
#include "StartButton.h"

class LMainMenu : public Level {
public:
    LMainMenu();
    ~LMainMenu();

private:

    StartButton* startButton;
    OptionsButton* optionsButton;
    ExitButton *exitButton;

};