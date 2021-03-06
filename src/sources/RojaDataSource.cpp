#include "RojaDataSource.h"

void RojaDataSource::setup(){
    allocate(500, 500);
    name = "Roja Data Source";

    ofxJSONElement json; 
    std::string dataFile = "roja.json";
    bool success = json.open("roja.json");

    if(success){
        ofLog() << "Lodaded " << dataFile;
    }else{
        ofLogError() << "Failed to load " << dataFile;
        ofExit();
    }

    int max = 0; // Use this to calculate normal values after
    for(auto i = 0; i < json.size(); i++){
        RojaDataBlock block;        
        block.year = json[i]["year"].asInt();
        block.income = json[i]["income"].asInt();
        block.education = json[i]["education"].asInt();
        block.religion = json[i]["religion"].asInt();
        data[block.year] = block;

        if(block.income > max) max = block.income;
        if(block.education > max) max = block.education;
        if(block.religion > max) max = block.religion;
    }

    // Calculate normal values
    for(auto it = data.begin(); it != data.end(); it++){
        RojaNormalDataBlock normalBlock;
        normalBlock.year = it->second.year;
        normalBlock.income = (float)it->second.income / (float)max;
        normalBlock.education = (float)it->second.education / (float)max;
        normalBlock.religion = (float)it->second.religion / (float)max;
        dataNormal[normalBlock.year] = normalBlock;

        std::cout 
            << normalBlock.year 
            << "\t" << normalBlock.income
            << "\t" << normalBlock.education
            << "\t" << normalBlock.religion 
            << std::endl;
    }

    // Year in the dataCurrent serves as target indicator.
    dataCurrent.year = dataNormal.begin()->second.year;
    dataCurrent.income = 0.0f;
    dataCurrent.education = 0.0f;
    dataCurrent.religion = 0.0f;

    dataFrameRate = DATA_FRAME_RATE;
    easingMultiplier = DATA_EASING_MULTIPLIER;
    lastFrameUpdate = ofGetElapsedTimef();
    objectRefSize = DATA_OBJECT_REF_SIZE;

    posIncome = glm::vec2(
        (float)getWidth() / 2.0f, 
        objectRefSize + 50.0f);
    posEducation = glm::vec2(
        objectRefSize + 50.0f, 
        (float)getHeight() - objectRefSize - 50.0f);
    posReligion = glm::vec2(
        (float)getWidth() - objectRefSize - 50.0f, 
        (float)getHeight() - objectRefSize - 50.0f);

    soundIncome.load(SOUND_INCOME);
    soundEducation.load(SOUND_EDUCATION);
    soundReligion.load(SOUND_RELIGION);

    soundIncome.setVolume(0.33f);
    soundEducation.setVolume(0.33f);
    soundReligion.setVolume(0.33f);

    soundIncome.setLoop(true);
    soundEducation.setLoop(true);
    soundReligion.setLoop(true);

    soundIncome.setSpeed(dataCurrent.income);
    soundEducation.setSpeed(dataCurrent.education);
    soundReligion.setSpeed(dataCurrent.religion);

    soundIncome.play();
    soundEducation.play();
    soundReligion.play();
}

void RojaDataSource::update(){
    float now = ofGetElapsedTimef();
    float frameLength = 1.0f / dataFrameRate;
    float deltaTime = now - lastFrameUpdate;
    if(deltaTime > frameLength){
        lastFrameUpdate = now;
        dataCurrent.year++;
        if(dataCurrent.year > dataNormal.rbegin()->second.year){
            dataCurrent.year = dataNormal.begin()->second.year;
        }
    }

    float deltaIncome = dataNormal[dataCurrent.year].income - dataCurrent.income;
    float deltaEducation = dataNormal[dataCurrent.year].education - dataCurrent.education;
    float deltaReligion = dataNormal[dataCurrent.year].religion - dataCurrent.religion;

    deltaIncome *= easingMultiplier;
    deltaEducation *= easingMultiplier;
    deltaReligion *= easingMultiplier;

    dataCurrent.income = dataNormal[dataCurrent.year].income - deltaIncome;
    dataCurrent.education = dataNormal[dataCurrent.year].education - deltaEducation;
    dataCurrent.religion = dataNormal[dataCurrent.year].religion - deltaReligion;

    soundIncome.setSpeed(pow(dataCurrent.income, 2.0f));
    soundEducation.setSpeed(pow(dataCurrent.education, 2.0f));
    soundReligion.setSpeed(pow(dataCurrent.religion, 2.0f));
}

void RojaDataSource::draw(){
    ofSetColor(0, 0, 0, 25);
    ofDrawRectangle(0, 0, getWidth(), getHeight());
    
    ofSetColor(255);
    ofDrawCircle(posIncome, dataCurrent.income * objectRefSize);
    ofDrawCircle(posEducation, dataCurrent.education * objectRefSize);
    ofDrawCircle(posReligion, dataCurrent.religion * objectRefSize);

    ofDrawBitmapStringHighlight("City: Roja, Latvia", 10, 20, ofColor::black);
    ofDrawBitmapStringHighlight("Year: " + ofToString(dataCurrent.year), 10, 40, ofColor::black);
    ofDrawBitmapStringHighlight("Income: " + ofToString(
        (float)data[dataCurrent.year].income * dataCurrent.income, 0), 10, 60, ofColor::black);
    ofDrawBitmapStringHighlight("Exp Education: " + ofToString(
        (float)data[dataCurrent.year].education * dataCurrent.education, 0), 10, 80, ofColor::black);
    ofDrawBitmapStringHighlight("Exp Religion: " + ofToString(
        (float)data[dataCurrent.year].religion * dataCurrent.religion, 0), 10, 100, ofColor::black);

    ofDrawBitmapStringHighlight("Income", posIncome, ofColor::black);
    ofDrawBitmapStringHighlight("Exp Education", posEducation, ofColor::black);
    ofDrawBitmapStringHighlight("Exp Religion", posReligion, ofColor::black);
}
