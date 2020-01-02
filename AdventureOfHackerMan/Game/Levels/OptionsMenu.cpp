#include "OptionsMenu.h"

LOptionsMenu::LOptionsMenu()
    :Level(1, IDR_OPTIONSMENUBG){
    backButton = new Button(6, 35, 25, 5,
        IDR_BACKBUTTON, [] { engine::changeLevel(idMainMenu); });

    objectList[0] = backButton;
    //back: 25 x 5
}

LOptionsMenu::~LOptionsMenu() {
    delete[] backButton;
}
