#include "Game.h"

/* HOW TO CREATE GAYEMES LIKE A BOSS:
 * 1. add level in anon namespace
 * 2. init it in "initialize"
 * 3. delete it in "uninitialize"
 * 4. PROFIT
 * (you will spend more time by creating levels, actually)
 */

namespace game {
    namespace {
        Level** level;
        LMainMenu *lMainMenu;
        LOptionsMenu* lOptionsMenu;
        constexpr int levelsNum = 2;
        //Level lOptions,
          //lClassChoosing,
         // lWantToExit;
    }

    void initialize(HWND hWnd, HRESULT& hr){
        lMainMenu = new LMainMenu();
        lOptionsMenu = new LOptionsMenu();

        level = new Level * [levelsNum];
        level[0] = static_cast<Level*>(lMainMenu);
        level[1] = static_cast<Level*>(lOptionsMenu);
        
        
        engine::initialize(hWnd, hr, levelsNum, level);
        engine::changeLevel(idMainMenu);
    }

    void uninitialize() {
        delete lMainMenu;
        delete[]level;
        engine::uninitialize();
    }
}