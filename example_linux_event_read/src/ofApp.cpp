
// app_linux_event_read
// Nicola Pisanti, MIT License, 2016

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    // REMEMBER TO RUN WITH ROOT PERMISSION TO ACCESS /dev/input/event*
    
    device = "/dev/input/event0";
    //device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    
    // Open Keyboard
    fd = open(device.c_str(), O_RDONLY | O_NONBLOCK);
    if(fd == -1)
    {
      cout<<"ERROR Opening " << device <<"\n";
      keyboardOpen = false;
    }else{
      keyboardOpen = true;
    }
      
}

//--------------------------------------------------------------
void ofApp::update(){

    if( keyboardOpen ){
        // Read Keyboard Data
        bytes = read(fd, &data, sizeof(data));
        if(bytes > 0)
        {
            cout << device << " : value=" << data.value << " type=" << data.type << " code=" << data.code << "\n";
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
