#include "MainMenu.h"

LMainMenu::LMainMenu()
    :Level(4, IDR_MAINMENUBG) {

    exitButton = new Button(6, 30, 20, 5,
        IDR_EXITBUTTON, [] { engine::shutdown(); });

    optionsButton = new Button(6, 20, 37, 6,
        IDR_OPTIONSBUTTON, [] {/*TODO: change level to optionsMenu*/});

    startButton = new Button(6, 10, 27, 5,
        IDR_STARTBUTTON, [] {/*TODO: change level to class choosing or smth*/});
    slider = new Slider(1, 1, 12, "test", [](byte) {});

    objectList[0] = static_cast<Object*>(exitButton);
    objectList[1] = static_cast<Object*>(optionsButton);
    objectList[2] = static_cast<Object*>(startButton);
    objectList[3] = static_cast<Object*>(slider);
}

LMainMenu::~LMainMenu() {
    delete optionsButton;
    delete exitButton;
    delete startButton;
    delete slider;
}