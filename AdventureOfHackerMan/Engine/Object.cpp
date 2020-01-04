#include "Object.h"
#include "Level.h"

Object::Object(Level* lvl, byte posX, byte posY, Map* texture) {
    this->posX = posX;
    this->posY = posY;

    activeTexture = texture;
    generateMouseEvents = false;
    isMouseHovering = false;
    isLmbDownHandled = false;
    isRmbDownHandled = false;
    lvl->addObject(this);
}

Object::~Object() {

}

const void Object::getPosition(byte* posX, byte* posY, byte* posX2, byte* posY2) {
    *posX = this->posX;
    *posY = this->posY;
    *posX2 = activeTexture->sizeX + *posX;
    *posY2 = activeTexture->sizeY + *posY;
}