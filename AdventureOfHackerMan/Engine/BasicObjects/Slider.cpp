#include "Slider.h"

Slider::Slider(byte posX, byte posY, byte length,
    const char* text, void valueChanged(byte newValue), byte defaultValue)
    :Object(posX, posY) {
    bGenerateMouseEvents = true;
    isMousePressed = false;
    this->valueChanged = valueChanged;

    sliderLength = length;
    byte textLength = '\x00';
    
    // !!! careful here !!!
    while (text[textLength] != '\0') {
        textLength++;
    }

    this->length = max(length, sliderLength);

    basicTexture = new sym[static_cast<long long>(this->length) << 1];
    std::fill(basicTexture, basicTexture + length * 2, ' ');

    for (int i = 0; i < textLength; i++) {
        basicTexture[i] = text[i];
    }

    basicTexture[this->length] = '<';
    basicTexture[this->length + --sliderLength] = '>';

    activeTexture = new Map(this->length, 2);
    activeTexture->set(basicTexture);

    eValueChanged(defaultValue);
}

void Slider::eValueChanged(byte newValue) {
    int i = this->length + 1;
    for (; i < newValue + this->length; i++) {
        basicTexture[i] = '=';
    }
    if ((newValue > 0) && (newValue < sliderLength)) {
        basicTexture[i] = '#';
        i++;
    }
    for (; i < sliderLength + this->length; i++) {
        basicTexture[i] = '.';
    }
    currentValue = newValue;
    activeTexture->set(basicTexture);

    valueChanged(newValue);
}

Slider::~Slider() {
    delete[] basicTexture;
    delete activeTexture;
}

void Slider::eMouseLmbPressed(byte x, byte y) {
    isMousePressed = true;
    eMouseMoving(x, y);
}

void Slider::eMouseLmbReleased(byte, byte) {
    isMousePressed = false;
}

void Slider::eMouseHoverEnd(byte, byte) {
    isMousePressed = false;
}

void Slider::eMouseMoving(byte x, byte y) {
    if ((y == 1) && isMousePressed) {
        if ((x <= sliderLength) && (x != currentValue)) {
            eValueChanged(x);
        }
    }
}