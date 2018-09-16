#include "ofApp.h"

// phasor tests 

//--------------------------------------------------------------
void ofApp::setup(){
	
	bSmooth = true;

    phasors.resize(2);
    phasors[0].speed = 0.135f;
    phasors[1].speed = 0.265f;
    
#ifndef __ARM_ARCH
    ofSetWindowTitle("phasors");
#endif

	gui.setup( "", "settings.xml", ofGetWidth()-220, 20 );
	gui.add( phasors[0].label("phasor 0") );
	gui.add( phasors[1].label("phasor 1") );
	
	gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    for( auto & phazor : phasors ) phazor.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255, 80, 80, 150);    

    ofDrawBitmapString("delta: " + ofToString(ofGetLastFrameTime()), 20, 20);

    ofPushMatrix();
    ofTranslate( 20, 50 );
    for( size_t i=0; i<phasors.size(); ++i ){
        ofDrawRectangle( 0, 40*i, 200*phasors[i].phase(), 20);
    }    
    ofPopMatrix();
    
    string info = "press o to set to oneshot,\nmode=";
    if(phasors[0].oneshot){
        info += "oneshot\n";
    }else{
        info += "free run\n";
    }
    info+="press 1/2 to retrigger cycles";
    ofDrawBitmapString(info, 5, ofGetHeight()-60 );
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key){
        case 'o':
            phasors[0].oneshot = phasors[0].oneshot ? false : true; 
            phasors[1].oneshot = phasors[1].oneshot ? false : true; 
        break;
        
        case '1': phasors[0].retrigger(); break;
        case '2': phasors[1].retrigger(); break;
        case 'a':
            bSmooth = !bSmooth;
            if (bSmooth){
                ofEnableAntiAliasing(); 
            }else{
                ofDisableAntiAliasing(); 
            }
        break;
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
