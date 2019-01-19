#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    canvas.allocate( ofGetWidth(), ofGetHeight() );
    mask.allocate( ofGetWidth(), ofGetHeight() );
    
    np::masker::init(); // this have to go after the allocations 
    
    ofBackground( 0 );
    select = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofFill();
    ofSetColor( 255 );
    canvas.begin();
    {
        ofClear( 0, 0, 0, 0 );

        for( int n=0; n<50; ++n ){
            float x = ofRandom( ofGetWidth() );
            float y = ofRandom( ofGetHeight() );            
            ofDrawRectangle( x, y, 100, 20 );
        }
    }
    canvas.end();
    
    mask.begin();
    {
        ofClear( 0, 0, 0, 0 );
        float x = ofGetWidth() * ofNoise( 1.777f, ofGetElapsedTimef()*0.2f );
        ofDrawRectangle( x, 0, ofGetWidth()-x, ofGetHeight() );
    }
    mask.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor( 255 );
    switch( select ){
        case 1: canvas.draw(0, 0); break;
        case 2: mask.draw(0, 0); break;
        default : 
            np::masker::draw( canvas, mask );             
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch( key ){
        case '1': select = 1; break;
        case '2': select = 2; break;
        
        case '0': 
        case '3': select = 0; break;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
