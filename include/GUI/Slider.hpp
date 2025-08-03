#pragma once

#include "GUI/Component.hpp"
#include "Global.hpp"
#include "Resource/ResourceHolder.hpp"
#include "Resource/ResourceIdentifier.hpp"

class Slider : public Component {
public:
    Slider(float x, float y, float width, float height, float initialValue);

    bool isSelectable() override;
    void handle() override;
    void draw() override;
    void changeTrackColor(Color color);
    void changeUnderTrackColor(Color color);
    void changeKnobColor(Color color);
    float getValue() const;

private:
    Rectangle mTrack;
    Color mTrackColor;
    Rectangle mTrackUnder;
    Color mTrackUnderColor;
    Rectangle mKnob;
    Color mKnobColor;
    float mValue;
    bool mIsDragging;
};