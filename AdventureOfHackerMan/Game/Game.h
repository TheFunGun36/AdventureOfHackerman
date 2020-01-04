#pragma once
#include "../Game/Levels/MainMenu.h"
#include "../Game/Levels/OptionsMenu.h"
#include "../Game/Levels/ClassChoosingMenu.h"

namespace game {
    void initialize(HWND hWnd, HRESULT& hr);
    void uninitialize();
}