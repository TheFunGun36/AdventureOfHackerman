#include "Engine.h"

namespace engine {
    namespace {
        Renderer renderer;
        HWND hWnd;
        std::chrono::time_point<std::chrono::steady_clock> storedTime;
        Level** levelList;
        Level* currentLevel;

        float getDeltaTime() {
            using namespace std::chrono;
            duration<float> dur;
            time_point curTime = steady_clock::now();
            dur = (curTime - storedTime);
            storedTime = curTime;
            return dur.count();
        }

        //bool shouldBeRedrawn = true;
    }

    void initialize(HWND hWnd, HRESULT& hr, int levelNum, Level** levels) {
        renderer.initialize(hWnd, hr);
        currentLevel = nullptr;
        levelList = levels;
        engine::hWnd = hWnd;
    }

    void uninitialize() {
        renderer.uninitialize();
    }

    void shutdown() {
        DestroyWindow(hWnd);
    }

    void changeLevel(LevelId levelId) {
        currentLevel = levelList[static_cast<int>(levelId)];
    }

    void computeGameLogic() {
        float deltaTime = getDeltaTime();
        currentLevel->tick(deltaTime);
        Object** objectList; int objectNumber;
        objectList = currentLevel->getObjectArray(&objectNumber);

        for (int i = 0; i < objectNumber; i++) {
            objectList[i]->eTick(deltaTime);
        }
    }

    void renderGraphic() {
        static Map mapToRender(constants::charsInX, constants::charsInY);
        Object** objectList; int count;
        objectList = currentLevel->getObjectArray(&count);
        mapToRender.append(&currentLevel->background, 0, 0);

        for (int i = 0; i < count; i++) {
            mapToRender.append(objectList[i]->getTexture(), objectList[i]->posX, objectList[i]->posY);
        }

        renderer.renderMap(&mapToRender);
    }

    Level* getCurrentLevel() {
        return currentLevel;
    }
}