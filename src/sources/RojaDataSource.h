#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "ofxJSON.h"

struct RojaDataBlock {
    int year;
    int income;
    int education;
    int religion;
};

struct RojaNormalDataBlock {
    int year;
    float income;
    float education;
    float religion;
};

class RojaDataSource : public ofx::piMapper::FboSource{
public:
    void setup();
    void update();
    void draw();

    std::map<int, RojaDataBlock> data;
    std::map<int, RojaNormalDataBlock> dataNormal;
};
