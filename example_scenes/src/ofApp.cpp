
#include "ofApp.h"

//------------------ shared resources --------------------------
namespace resources {
    ofColor colorA;
    ofColor colorB;
    float width;
    float height;
}

//--------------------------------------------------------------
void ofApp::setup(){

    // init the resources

    resources::colorA = ofColor(255, 0, 0);
    resources::colorB = ofColor( ofRandom(255), ofRandom(255), ofRandom(255) );

    resources::width = ofGetWidth();
    resources::height = ofGetHeight();


    // then init the scenes
    sceneA.setup();
    sceneB.setup();

    // then set up the manager
    manager.setup( ofGetWidth(), ofGetHeight() );
    manager.add( nullptr ); // nullptr for empty slot
    manager.add( &sceneA );
    manager.add( &sceneB );

    ofBackground( resources::colorB * 0.25 );
}

//--------------------------------------------------------------
void ofApp::update(){
    manager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    manager.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == ' '){
        manager.next();
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
