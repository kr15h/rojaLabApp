#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"

struct Element{
    ofRectangle rect;
    float speed;
};

class BouncingLineSource : public ofx::piMapper::FboSource{
public:
    void setup();
    void update();
    void draw();

    vector<Element> elements;
};
