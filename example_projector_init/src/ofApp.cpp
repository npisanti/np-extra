#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    fbo.allocate( PROJECTOR_WIDTH, PROJECTOR_HEIGHT );

	bDrawGui = true;
	gui.setup("", "settings.xml", PROJECTOR_WIDTH+10, 10);
	gui.setName("GUI");
		
	gui.minimizeAll();
	//gui.loadFromFile("settings.xml");
	
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
        ofClear(0, 0, 0, 0);
        
        
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    fbo.draw(0, 0);
    if( bDrawGui ){ gui.draw(); }
}

void ofApp::drawSecondWindow(ofEventArgs& args){
    ofBackground(0);
    ofSetColor(255);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){
		
		case 'g': bDrawGui = !bDrawGui; break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------
