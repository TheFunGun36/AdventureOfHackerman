#include "MainMenu.h"

LMainMenu::LMainMenu(LevelArray *lvlArr)
    :Level(lvlArr, 3, IDR_MAINMENUBG) {

    exitButton = new Button(this, 6, 30, IDR_EXITBUTTON,
        [] { engine::shutdown(); });

    optionsButton = new Button(this, 6, 20, IDR_OPTIONSBUTTON,
        [] { engine::changeLevel(LevelId::optionsMenu); });

    startButton = new Button(this, 6, 10, IDR_STARTBUTTON,
        [] { engine::changeLevel(LevelId::classChoosingMenu); });
}

/*LMainMenu::~LMainMenu() {
    delete optionsButton;
    delete exitButton;
    delete startButton;
}*/