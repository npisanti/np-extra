#include "ofApp.h"

#define SCALE 0.3f

//--------------------------------------------------------------
void ofApp::setup(){

    int num = 3;
    videos.resize(num);
    paths.resize(num);
    
    ofDirectory dir;    
    dir.listDir("/path/to/your/videos/");
	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

    for( size_t i=0; i<num; ++i ){
                        
        for( int k = 0; k < (int) dir.size(); k++){
            paths[i].add(dir.getPath(k));
        }

        videos[i].setup( paths[i] );
        
        videos[i].next();
        videos[i].next();        
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    float w = videos[0].getWidth() * SCALE;
    
    for(size_t i=0; i<videos.size(); ++i){
        videos[i].draw( i*w, 0, SCALE );        
    }
    
    ofDrawBitmapString( "fps="+ofToString(ofGetFrameRate()), 20, 20 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch( key ){
        case ' ': 
            for( auto & video : videos ){ video.next( false ); } 
        break;

        case '1': videos[0].next(); break;
        case '2': videos[1].next(); break;
        case '3': videos[2].next(); break;
        
        case 'q': videos[0].restart(); break;
        case 'w': videos[1].restart(); break;
        case 'e': videos[2].restart(); break;
        
        default: break;
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
