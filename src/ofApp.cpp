#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
    mapper.registerFboSource(sourceA);
    mapper.registerFboSource(sourceB);
    mapper.registerFboSource(sourceC);
	mapper.setup();

    #ifdef TARGET_RASPBERRY_PI
        ofSetFullscreen(true);
    #endif

    currentGuide = -1;
    guides.resize(2);
    guides[0].load("layout.jpg");
    guides[1].load("layout180.jpg");
}

void ofApp::update(){
	mapper.update();
}

void ofApp::draw(){
    if(currentGuide > -1){
        guides[currentGuide].draw(0, 0);
    }
	mapper.draw();
}

void ofApp::keyPressed(int key){
	mapper.keyPressed(key);
    if(key == 'u'){ // gUide
        currentGuide++;
        if(currentGuide >= guides.size()){
            currentGuide = -1;
        }
    }
}

void ofApp::keyReleased(int key){
	mapper.keyReleased(key);
}

void ofApp::mouseDragged(int x, int y, int button){
	mapper.mouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button){
	mapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	mapper.mouseReleased(x, y, button);
}
