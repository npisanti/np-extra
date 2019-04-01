
#include "ofMain.h"
#include "components/LiveParameters.h"

class ofApp : public ofBaseApp{
    
// ---------- variables ----------------------------------------

ofParameterGroup parameters;
    ofParameter<string> label;
    ofParameter<glm::vec2> position;
    ofParameterGroup dimensions;
        ofParameter<int> width;
        ofParameter<int> height;
np::LiveParameters parameterLive;


//--------------------------------------------------------------
void setup(){
    ofBackground( 0 );
    
    parameters.setName("test");
        parameters.add( label.set( "label", "this is a test") );
        parameters.add( position.set("position", glm::vec2( 0, 0 ), glm::vec2( 0, 0 ), glm::vec2( ofGetWidth(), ofGetHeight() ) ) );
        
        dimensions.setName( "dimensions" );
            dimensions.add( width.set( "width", 200, 0, ofGetWidth() ));
            dimensions.add( height.set( "height", 50, 0, ofGetHeight() ));
        parameters.add( dimensions );
    parameterLive.watch( parameters, "data/live.json");
}

//--------------------------------------------------------------
void update(){

}

//--------------------------------------------------------------
void draw(){
    ofSetColor( 255 );
    ofNoFill();
    ofDrawBitmapString( label, 20, 20 );
    ofDrawRectangle( position.get().x, position.get().y, width, height );
}

//--------------------------------------------------------------
void exit(){

}

//--------------------------------------------------------------
void keyPressed(int key){

}

//--------------------------------------------------------------
void mousePressed(int x, int y, int button){}
void mouseDragged(int x, int y, int button){}
void mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void keyReleased(int key){}
void mouseMoved(int x, int y){}
void mouseEntered(int x, int y){}
void mouseExited(int x, int y){}
void windowResized(int w, int h){}
void gotMessage(ofMessage msg){}
void dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------

}; // class ofApp

int main(){
	ofSetupOpenGL( 800, 480, OF_WINDOW);
	ofRunApp( new ofApp() );
}
