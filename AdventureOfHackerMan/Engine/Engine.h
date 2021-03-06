#pragma once
#include <chrono>
#include <windows.h>
#include "RenderEngine.h"
#include "Level.h"

enum class LevelId {
    mainMenu,
    optionsMenu,
    classChoosingMenu
};
namespace engine {
    void initialize(HWND hWnd, HRESULT& hr, int levelNum, Level** levels);
    void uninitialize();
    void shutdown();
    void computeGameLogic();
    void renderGraphic();
    void changeLevel(LevelId levelId);
    Level* getCurrentLevel();
}