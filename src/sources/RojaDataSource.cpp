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
}

void RojaDataSource::update(){
    
}

void RojaDataSource::draw(){
    ofClear(0, 0, 0, 0);
    ofSetColor(255, 255, 0);
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}
