#include "BouncingLineSource.h"

void BouncingLineSource::setup(){
    ofLog() << "Hello Void!";
    allocate(500, 500);
    name = "The Source";

    int numElements = 10;
    elements.resize(numElements);
    
    for(auto i = 0; i < elements.size(); i = i + 1){
        elements[i].speed = 1.0f + ofRandom(2.0f);
        elements[i].rect.x = ofRandom(getWidth());
        elements[i].rect.y = getHeight() / elements.size() * i;
        // We will calculate width in the update() part.
        elements[i].rect.height = getHeight() / elements.size();
    }
}

void BouncingLineSource::update(){
    for(auto i = 0; i < elements.size(); i++){
        // Get position between -1 and 1
        float position = sin(ofGetElapsedTimef() * elements[i].speed);
        float percent = (position + 1.0f) / 2.0f;
        
        // Calculate actual width of the moving element
        elements[i].rect.width =
            (1.0f - abs(position)) *
            getWidth();
    
        // Calculate actual x position of the moving element
        elements[i].rect.x =
            (percent * getWidth()) -
            (elements[i].rect.width / 2.0f);
    }
}

void BouncingLineSource::draw(){
    ofClear(0, 0, 0, 0);

    ofSetColor(255);

    for(auto i = 0; i < elements.size(); i++){
        ofDrawRectangle(elements[i].rect);
    }
}
