#include "MainMenu.h"

LMainMenu::LMainMenu()
    :Level(3, IDR_MAINMENUBG) {

    exitButton = new Button(6, 30, 20, 5,
        IDR_EXITBUTTON, [] { engine::shutdown(); });

    optionsButton = new Button(6, 20, 37, 6,
        IDR_OPTIONSBUTTON, [] {/*TODO: change level to optionsMenu*/});

    startButton = new Button(6, 10, 27, 5,
        IDR_STARTBUTTON, [] {/*TODO: change level to class choosing or smth*/});

    /*exitButton = new ExitButton(6, 30);
    optionsButton = new OptionsButton(6, 20);
    startButton = new StartButton(6, 10);*/

    //Происходит неявное преобразование в Object
    //Не пихайте сюда C-style касты, а ещё хуже - static_cast-ы
    objectList[0] = exitButton;
    objectList[1] = optionsButton;
    objectList[2] = startButton;
}

LMainMenu::~LMainMenu() {
    delete optionsButton;
    delete exitButton;
    delete startButton;
}