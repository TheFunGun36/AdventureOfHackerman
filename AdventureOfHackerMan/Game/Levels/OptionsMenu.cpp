#include "OptionsMenu.h"

LOptionsMenu::LOptionsMenu(LevelArray *lvlArr)
    :Level(lvlArr, 2, IDR_OPTIONSMENUBG){
    backButton = new Button(this, 6, 35, IDR_BACKBUTTON,
        [] { engine::changeLevel(LevelId::mainMenu); });

    volumeSlider = new Slider(this, 6, 10, 30, "Volume", [](byte) {}, '\x0f');
    
    //back: 25 x 5
}

/*LOptionsMenu::~LOptionsMenu() {
    delete[] backButton;
    delete[] volumeSlider;
}*/