#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
	ofSetCircleResolution(50);
    
    dsFbo.allocate( ofGetWidth()/4.0f, ofGetHeight()/4.0f );
    
    dsFbo.begin();
		ofPushMatrix();
        ofClear( 0, 0, 0, 0 );
        
        ofNoFill();
        ofSetColor( 255, 0, 0 );
        
        ofDrawRectangle( 10, 10, 50, 50 );
        ofDrawLine( 10, 10, 60, 35 );
        
        ofDrawBitmapString( "test string", 10, 70 );
        
        ofPopMatrix();
    dsFbo.end();
    
    ofSetWindowTitle("MSAA / downsampling test");
    
    info = "fbo downsampling\n";
    
    bAA = false;
}

void ofApp::fbographics(){
	
		ofSetLineWidth( 1.8f);
		ofNoFill();
		ofSetColor( 255, 0, 0 );
		
		ofDrawRectangle( 40, 40, 200, 200 );
		ofDrawLine( 40, 40, 240, 140 );
		
		for(int i=0; i<2; ++i ){
			ofDrawLine( 40,  ofNoise((i*2.0f       )*1.5f, ofGetElapsedTimef()*(0.1f*i + 0.05f))*200.0f + 40,
						240, ofNoise((i*2.0f + 1.0f)*1.5f, ofGetElapsedTimef()*(0.1f*i + 0.05f))*200.0f + 40 );	
		}
		ofDrawCircle( 160, 160, 30 );
		
		ofDrawBitmapString( "test string", 10, 70 );	
}

//--------------------------------------------------------------
void ofApp::update(){
    if( mode == 1){
		aaFbo.begin();
			ofClear( 0, 255 );
			fbographics();
		aaFbo.end();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);

    switch( mode ){
		case 0:
			dsFbo.draw( 0, 0 );
		break;
		
		case 1:
			aaFbo.draw( 0, 0 );
		break;
		
		case 2:
			fbographics();
		break;
	}
    
    ofSetColor( 255, 0, 0 );
    ofDrawBitmapString( info, 20, ofGetHeight()-40 );
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   
    switch( key ){
        case OF_KEY_LEFT:
            dsFbo.multiply -= 0.05f;
        break;
        
        case OF_KEY_RIGHT:
            dsFbo.multiply += 0.05f;
        break;
        
        case '0':
			mode = 0; 
			info = "fbo downsampling\n";
		break;
        case '1': 
			mode = 1; 
			aaFbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA ); 
			ofDisableAntiAliasing(); bAA = false;
			info = "fbo, not antialiased\n";
		break;
		
        case '2': 
			mode = 1; 
			aaFbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA, 2 ); 
			ofEnableAntiAliasing(); bAA = true;
			info = "fbo, 2x antialiasing\n";
		break;
		
        case '3': 
			mode = 1; 
			aaFbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA, 4 ); 
			ofEnableAntiAliasing(); bAA = true;
			info = "fbo, 4x antialiasing\n";
		break;
		
        case '4': 
			mode = 1; 
			aaFbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA, 8 ); 
			ofEnableAntiAliasing(); bAA = true;
			info = "fbo, 8x antialiasing\n";
		break;
		
        case '5': 
			mode = 2; 
			ofDisableAntiAliasing(); bAA = false;
			info = "screen rendering, not antialiased\n";
		break;
		
        case '6': 
			mode = 2; 
			ofEnableAntiAliasing(); bAA = true;
			info = "screen rendering, antialiased\n";
		break;

		case 'a': 
			bAA = !bAA;
			if(bAA){
				ofEnableAntiAliasing();
				cout << "activating AA\n";
			} else {
				ofDisableAntiAliasing();
				cout << "deactivating AA\n";
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
