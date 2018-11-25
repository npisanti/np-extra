#include "ofApp.h"

#include "serializers/polylines.h"
#include "components/polyworks.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground( 0 );
    
    std::vector<std::vector<ofPolyline>> import;
    np::deserialize_polylines( ofToDataPath("silhouette.xml"), import );
    silhouette = import[0][0];
    silhouette.close();
    
    int x = 800;
    int y = 300;
    int side = 250;
    freehand.addVertex( x, y );
    freehand.addVertex( x+side, y );
    freehand.addVertex( x+side, y+side );
    freehand.addVertex( x, y+side );
    freehand.addVertex( x, y );
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float mx = ofGetMouseX() / float( ofGetWidth() );
    float my = ofGetMouseY() / float( ofGetHeight() );
    
    np::polyworks::inflate( silhouette, result, ofGetMouseX() );
    np::polyworks::smooth( result, my * 10.0f );
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofNoFill();

    auto drawpoly = []( ofPolyline & poly ) noexcept { 
        auto & vertices = poly.getVertices();
        ofBeginShape();
        for( size_t v=0; v<vertices.size(); ++v ){
            ofVertex( vertices[v].x, vertices[v].y );
        }
        ofEndShape(true);
    };
    ofSetColor( 120, 0, 0 );
    drawpoly( silhouette );
    drawpoly( freehand );
    ofSetColor( 255 );
    drawpoly( result );
   
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   
    switch( key ){
        case '1': 
        
        break;
        
        case '2': 
        
        break;
        
        case '3': 
        
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
