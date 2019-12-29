#include "Object.h"

Object::Object(byte posX, byte posY, Map* texture) {
    this->posX = posX;
    this->posY = posY;

    activeTexture = texture;

    bGenerateMouseEvents = false;
    bMouseIsHovering = false;

    bLmbDownHandled = false;
    bRmbDownHandled = false;
}

Map* Object::getTexture() {
    return activeTexture;
}

Object::~Object() {

}

/*void Object::generateEvents(InputEngine* in)
{
  static bool bMouseIsHovering = false;
  if (bGenerateMouseEvents)
  {
    byte x, y;
    in->getMousePosition(&x, &y);
    //in->getMouseChar(&x, &y);
    if (!bMouseIsHovering)
    {
      if (
        ((posX <= x) && (x <= (posX + texture.sizeX))) &&
        ((posY <= y) && (y <= (posY + texture.sizeY)))  )
      {
        if (in->bLmbDown)
        {
          bLmbDownHandled = true;
          bLmbUpHandled = false;
        }
        if (in->bRmbDown)
        {
          bRmbDownHandled = true;
          bRmbUpHandled = false;
        }

        bMouseIsHovering = true;
        eMouseHoverStart();
      }
    }
    else
    {
      if (
        ((posX > x) || (x > (posX + texture.sizeX))) ||
        ((posY > y) || (y > (posY + texture.sizeY))) )
      {
        bMouseIsHovering = false;
        eMouseHoverEnd();
        bLmbDownHandled = false;
        bLmbUpHandled = false;
        bRmbDownHandled = false;
        bRmbUpHandled = false;
      }
    }

    if (bMouseIsHovering)
    {
      eMouseHoverTick();

      if (in->bLmbDown && !bLmbDownHandled)
      {
        bLmbDownHandled = true;
        eMouseLmbPressed();
      }
      if (!in->bLmbDown && !bLmbUpHandled)
      {
        bLmbUpHandled = true;
        eMouseLmbReleased();
        if (!bLmbWasDownWhenEntered)
        {
          bLmbDownHandled = true;
          eMouseLmbClick();
        }
        bLmbUpHandled = false;
        bLmbDownHandled = false;
        bLmbWasDownWhenEntered = false;
      }

      if (in->bRmbDown && !bRmbDownHandled)
      {
        bRmbDownHandled = true;
        eMouseRmbDown();
      }
      if (!in->bRmbDown && !bRmbUpHandled)
      {
        bRmbUpHandled = true;
        eMouseRmbUp();
        if (!bRmbWasDownWhenEntered)
        {
          bRmbDownHandled = true;
          eMouseRmbClick();
        }
        bRmbUpHandled = false;
        bRmbDownHandled = false;
        bRmbWasDownWhenEntered = false;
      }
    }
  }

  using namespace std::chrono;
  static time_point<steady_clock> storedTime = steady_clock::now();
  if (bGenerateTickEvent)
  {
    duration<float, std::milli> deltaTime = steady_clock::now() - storedTime;
    eTick(deltaTime.count());
  }
}*/

/*Map Object::getTexture()
{
  return texture;
}*/

void Object::getPosition(byte* posX, byte* posY, byte* posX2, byte* posY2) {
    *posX = this->posX;
    *posY = this->posY;
    *posX2 = activeTexture->sizeX + *posX;
    *posY2 = activeTexture->sizeY + *posY;
}