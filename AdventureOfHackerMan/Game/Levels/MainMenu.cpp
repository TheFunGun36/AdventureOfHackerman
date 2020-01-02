#include "MainMenu.h"

LMainMenu::LMainMenu()
    :Level(3, IDR_MAINMENUBG) {

    exitButton = new Button(6, 30, 20, 5,
        IDR_EXITBUTTON, [] { engine::shutdown(); });

    optionsButton = new Button(6, 20, 37, 6,
        IDR_OPTIONSBUTTON, [] { engine::changeLevel(idOptionsMenu); });

    startButton = new Button(6, 10, 27, 5,
        IDR_STARTBUTTON, [] {/*TODO: change level to class choosing or smth*/});

    objectList[0] = static_cast<Object*>(exitButton);
    objectList[1] = static_cast<Object*>(optionsButton);
    objectList[2] = static_cast<Object*>(startButton);
}

LMainMenu::~LMainMenu() {
    delete optionsButton;
    delete exitButton;
    delete startButton;
}