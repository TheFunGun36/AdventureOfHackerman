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
        LMainMenu *lMainMenu;
        //Level lOptions,
          //lClassChoosing,
         // lWantToExit;
    }

    void initialize(HWND hWnd, HRESULT& hr){
        engine::initialize(hWnd, hr);
        lMainMenu = new LMainMenu();
        engine::changeLevel(static_cast<Level*>(lMainMenu));
    }

    void uninitialize() {
        delete lMainMenu;
        engine::uninitialize();
    }
}