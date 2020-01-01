#include "Engine.h"

namespace engine {
    namespace {
        Renderer renderer;
        HWND hWnd;
        std::chrono::time_point<std::chrono::steady_clock> storedTime;
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

    void initialize(HWND hWnd, HRESULT& hr) {
        renderer.initialize(hWnd, hr);
        currentLevel = nullptr;
        engine::hWnd = hWnd;
    }

    void uninitialize() {
        renderer.uninitialize();
    }

    void shutdown() {
        DestroyWindow(hWnd);
    }

    void changeLevel(Level* newLevel) {
        currentLevel = newLevel;
    }

    void computeGameLogic() {
        float deltaTime = getDeltaTime();
        currentLevel->tick(deltaTime);
        Object** objectList; int count;
        objectList = currentLevel->getObjectArray(&count);

        for (int i = 0; i < count; i++) {
            objectList[i]->eTick(deltaTime);
        }
    }

    void renderGraphic() {
        static Map mapToRender(c::charsInX, c::charsInY);
        //if (shouldBeRedrawn) {
            //shouldBeRedrawn = false;
            Object** objectList; int count;
            objectList = currentLevel->getObjectArray(&count);

            mapToRender.append(&currentLevel->background, 0, 0);

            for (int i = 0; i < count; i++) {
                mapToRender.append(objectList[i]->getTexture(), objectList[i]->posX, objectList[i]->posY);
            }

            renderer.renderMap(&mapToRender);
        //}
    }

    Level* getCurrentLevel() {
        return currentLevel;
    }

   // void redraw() {
    //    shouldBeRedrawn = true;
    //}
}