#include "ClassChoosingMenu.h"

LClassChoosingMenu::LClassChoosingMenu(LevelArray* lvlArr)
    :Level(lvlArr, 4, IDR_EMPTYBG) {
    backButton = new Button(this, 52, 38, IDR_BACKBUTTON,
        [] {engine::changeLevel(LevelId::mainMenu); });
    samuraiButton = new Button(this, 2, 2, IDR_SAMURAIBUTTON, [] {});
    crusaderButton = new Button(this, 44, 2, IDR_CRUSADERBUTTON, [] {});
    thiefButton = new Button(this, 86, 2, IDR_THIEFBUTTON, [] {});
}