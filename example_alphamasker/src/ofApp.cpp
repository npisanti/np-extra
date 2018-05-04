
// app_alpha_masker
// Nicola Pisanti, MIT License, 2016

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    backgroundImage.load("A.jpg");
    foregroundImage.load("B.jpg");
    brushImage.load("brush.png");
    
    int w = backgroundImage.getWidth();
    int h = backgroundImage.getHeight();
    
    bBrushDown = false;

    // masking setup
    masker.setup( w, h );

    // this happen just once
    masker.canvas.begin();
        backgroundImage.draw(0, 0);   
        bUpdateMasking = true;
    masker.canvas.end();

    ofSetWindowShape( w, h );
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetColor(255);

    // this is our alpha mask which we draw into.
    if(bBrushDown) {
        masker.mask.begin();            
            int brushImageSize = 50;
            int brushImageX = mouseX - brushImageSize * 0.5;
            int brushImageY = mouseY - brushImageSize * 0.5;
            brushImage.draw(brushImageX, brushImageY, brushImageSize, brushImageSize);
        masker.mask.end();
        
        bUpdateMasking = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
       
    //----------------------------------------------------------
    // FIRST draw the background image
    foregroundImage.draw(0,0);
    
    // THEN draw the masked fbo on top
    masker.draw(0,0);
    
    //----------------------------------------------------------
    ofDrawBitmapString("Drag the Mouse to draw", 15,15);
    ofDrawBitmapString("Press spacebar to clear", 15, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        masker.mask.begin();
            ofClear(0,0,0,0);
        masker.mask.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bBrushDown = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bBrushDown = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
