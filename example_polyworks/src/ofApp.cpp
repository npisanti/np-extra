
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
    freehandIsDone = true;   
}

//--------------------------------------------------------------
void ofApp::update(){
    float mx = ofGetMouseX() / float( ofGetWidth() );
    float my = ofGetMouseY() / float( ofGetHeight() );

    float base = np::polyworks::find_max_y(silhouette);
    
    //np::polyworks::inflate( silhouette, result, ofGetMouseX() );
    //np::polyworks::smooth( result, my * 10.0f );
    
    //np::polyworks::radial( silhouette, result, glm::vec2( ofGetWidth()*0.5f, ofGetHeight()*0.5f), mx*TWO_PI );

    //np::polyworks::stretch( silhouette, result, mx*4.0f, 1.0f );
    //np::polyworks::basealign(  result, base );
    //np::polyworks::smooth( result );
    
    //np::polyworks::normals_expand( silhouette, result, mx*50.0f );
    //np::polyworks::smooth( result, 10 );

    glm::vec2 mouse( ofGetMouseX(), ofGetMouseY() );
    np::polyworks::push( silhouette, result, mouse, 150 );

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
        
        case ' ':
            freehand.addVertex( freehand.getVertices()[0] );
            freehandIsDone = true;
        break;
    }
}

void ofApp::mousePressed(int x, int y, int button){
    if( freehandIsDone ){
        freehand.clear();
        freehandIsDone = false;
    } 
    freehand.addVertex( x, y );
}
void ofApp::mouseDragged(int x, int y, int button){
    freehand.addVertex( x, y );
}
void ofApp::mouseReleased(int x, int y, int button){
    freehand.addVertex( x, y );
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------
