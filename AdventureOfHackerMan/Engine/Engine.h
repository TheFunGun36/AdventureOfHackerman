#pragma once
#include <chrono>
#include <windows.h>
#include "RenderEngine.h"
#include "Level.h"

namespace engine {
    void initialize(HWND hWnd, HRESULT& hr);
    void uninitialize();
    void shutdown();
    void computeGameLogic();
    void renderGraphic();
    void changeLevel(Level* newLevel);
    //void redraw();
    Level* getCurrentLevel();
}