#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "ofxJSON.h"

#define DATA_FRAME_RATE 5.0f
#define DATA_EASING_MULTIPLIER 0.85f
#define DATA_OBJECT_REF_SIZE 100.0f

#define SOUND_INCOME "audio/17072__fractal-dimension__low-freq-rumble.wav"
#define SOUND_EDUCATION "audio/17070__fractal-dimension__arpeggio-pitch-down_01.wav"
#define SOUND_RELIGION "audio/17067__fractal-dimension__analog-bubbles-3_01.wav"

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
    RojaNormalDataBlock dataCurrent;

    float dataFrameRate;
    float lastFrameUpdate;
    float easingMultiplier;
    float objectRefSize;

    glm::vec2 posIncome;
    glm::vec2 posEducation;
    glm::vec2 posReligion;

    ofSoundPlayer soundIncome;
    ofSoundPlayer soundEducation;
    ofSoundPlayer soundReligion;
};
