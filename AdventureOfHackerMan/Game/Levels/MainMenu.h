#pragma once
#include "../Objects/ExitButton.h"
#include "../Objects/OptionsButton.h"
#include "../Objects/StartButton.h"

class LMainMenu : public Level {
public:
    LMainMenu();
    ~LMainMenu();

private:

    StartButton* startButton;
    OptionsButton* optionsButton;
    ExitButton *exitButton;

};