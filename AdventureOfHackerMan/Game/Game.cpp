#include "Game.h"

namespace game {
    namespace {
        Level** level;
        constexpr int levelsNum = 3;
    }

    void initialize(HWND hWnd, HRESULT& hr) {
        level = new Level * [levelsNum];
        LevelArray* lvlArr = new LevelArray(level);

        LMainMenu* l1 = new LMainMenu(lvlArr);
        LOptionsMenu* l2 = new LOptionsMenu(lvlArr);
        LClassChoosingMenu* l3 = new LClassChoosingMenu(lvlArr);
        

        engine::initialize(hWnd, hr, levelsNum, level);
        engine::changeLevel(LevelId::mainMenu);
        delete lvlArr;
    }

    void uninitialize() {
        for (int i = 0; i < levelsNum; i++) {
            delete level[i];
        }
        delete[]level;
        engine::uninitialize();
    }
}