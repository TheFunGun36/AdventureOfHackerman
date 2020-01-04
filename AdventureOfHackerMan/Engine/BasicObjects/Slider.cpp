#include "Slider.h"

Slider::Slider(Level* level, byte posX, byte posY, byte sliderLength,
    const char* text, void onValueChanged(byte newValue), byte defaultValue)
    :Object(level, posX, posY) {
    
    generateMouseEvents = true;
    isMousePressed = false;
    this->onValueChanged = onValueChanged;
    this->sliderLength = sliderLength;
    byte textLength = '\x00';
    
    while (text[textLength] != '\0') {
        textLength++;
    }

    realLength = max(sliderLength, textLength);
    basicTexture = new char[realLength << 1];
    std::fill(basicTexture, basicTexture + (sliderLength << 1), ' ');

    for (int i = 0; i < textLength; i++) {
        basicTexture[i] = text[i];
    }

    basicTexture[realLength] = '<';
    basicTexture[realLength + --sliderLength] = '>';

    activeTexture = new Map(realLength, 2);
    activeTexture->set(basicTexture);

    eValueChanged(defaultValue);
    activeTexture->fillColor(constants::clrDefText, constants::clrDefBg);
}

void Slider::eValueChanged(byte newValue) {
    int i = realLength + 1;

    for (; i < newValue + realLength; i++) {
        basicTexture[i] = '=';
    }

    if ((newValue > 0) && (newValue < sliderLength - 1)) {
        basicTexture[i] = '#';
        i++;
    }

    for (; i < sliderLength + realLength - 1; i++) {
        basicTexture[i] = '.';
    }

    currentValue = newValue;
    activeTexture->set(basicTexture);
    activeTexture->fillColor(constants::clrDefText, constants::clrDefBg);
    activeTexture->setSymbolColor(newValue, 1, MakeMono(127));
    onValueChanged(newValue);
}

Slider::~Slider() {
    delete[] basicTexture;
    delete activeTexture;
}

void Slider::emlPressed(byte x, byte y) {
    isMousePressed = true;
    emhMoving(x, y);
    activeTexture->setSymbolColor(currentValue, 1, MakeMono(127));
}

void Slider::emlReleased(byte, byte) {
    isMousePressed = false;
    activeTexture->fillColor(constants::clrDefText, constants::clrDefBg);
}

void Slider::emhEnd(byte, byte) {
    isMousePressed = false;
    activeTexture->fillColor(constants::clrDefText, constants::clrDefBg);
}

void Slider::emhMoving(byte x, byte y) {
    if ((y == 1) && isMousePressed) {
        if ((x <= sliderLength) && (x != currentValue)) {
            eValueChanged(x);
        }
    }
}