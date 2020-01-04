#include "OptionsMenu.h"

LOptionsMenu::LOptionsMenu()
    :Level(2, IDR_OPTIONSMENUBG){
    backButton = new Button(6, 35, 25, 5,
        IDR_BACKBUTTON, [] { engine::changeLevel(idMainMenu); });

    volumeSlider = new Slider(6, 10, 30, "Volume", [](byte) {}, '\x0f');

    objectList[0] = backButton;
    objectList[1] = volumeSlider;
    //back: 25 x 5
}

LOptionsMenu::~LOptionsMenu() {
    delete[] backButton;
    delete[] volumeSlider;
}