#include "GUI/Slider.hpp"
#include <raylib.h>
#include <algorithm>

Slider::Slider(float x, float y, float width, float height, float initialValue)
    : mTrack{x, y, (initialValue/100)*width, height}, mTrackUnder{x, y, width, height}, mValue(initialValue), mIsDragging(false), mTrackColor(WHITE), mTrackUnderColor(Fade(WHITE, 0.5f)), mKnobColor({217,217,217,255}) {
    mKnob.width = 12.0f;
    mKnob.height = height + 20.0f; 
    mKnob.x = mTrack.x+mTrack.width-mKnob.width;
    mKnob.y = y - height/2;
    mValue = initialValue;
}

bool Slider::isSelectable() {
    return true;
}

void Slider::handle() {
    Vector2 mousePos = GetMousePosition();
    bool mouseOverKnob = CheckCollisionPointRec(mousePos, mKnob);

    if (mouseOverKnob && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        mIsDragging = true;
    }
    // Stop dragging on mouse release
    if (mIsDragging && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        mIsDragging = false;
    }
    // Update knob position while dragging
    if (mIsDragging) {
        float newX = mousePos.x;
        if (newX < mTrackUnder.x) newX = mTrackUnder.x;
        else if (newX > mTrackUnder.x+mTrackUnder.width-mKnob.width) newX = mTrackUnder.x+mTrackUnder.width-mKnob.width;
        mKnob.x = newX;
        mTrack.width = newX-mTrackUnder.x;
        // Calculate new value based on knob position
        float normalized = mTrack.width / mTrackUnder.width;
        mValue = normalized * 100;
        if (mValue < 0) mValue = 0;
        else if (mValue > 100) mValue = 100;
    }
    
}
void Slider::changeTrackColor(Color color) {
    mTrackColor = color;
}
void Slider::changeUnderTrackColor(Color color) {
    mTrackUnderColor = Fade(color, 0.5f);
}
void Slider::changeKnobColor(Color color) {
    mKnobColor = Fade(color, 0.5f);
}
void Slider::draw() {
    DrawRectangleRec(mTrackUnder, mTrackUnderColor);
    DrawRectangleRec(mTrack, mTrackColor);
    DrawRectangleRec(mKnob, mKnobColor);
}

float Slider::getValue() const {
    return mValue;
}