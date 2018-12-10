
#include "ofApp.h"

#include "routines/serialize.h"
#include "routines/polyworks.h"

#define ROUTINEMAX 14

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground( 0 );
    
    std::vector<std::vector<ofPolyline>> import;
    np::deserialize_polylines( ofToDataPath("silhouette.xml"), import );
    silhouette = import[0][0];
    silhouette.close();
    
    int x = 1000;
    int y = 300;
    int side = 250;
    freehand.addVertex( x, y );
    freehand.addVertex( x+side, y );
    freehand.addVertex( x+side, y+side );
    freehand.addVertex( x, y+side );
    freehand.addVertex( x, y );
    freehandIsDone = true;   
    
    routine = 0;
    label = "";
    target = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    float mx = ofGetMouseX() / float( ofGetWidth() );
    float my = ofGetMouseY() / float( ofGetHeight() );
    float base = np::polyworks::find_max_y(silhouette);
    auto center = glm::vec2(ofGetWidth()*0.5f, ofGetHeight()*0.5f);
    glm::vec2 mouse( ofGetMouseX(), ofGetMouseY() );
    
    ofPolyline * input = nullptr;
    switch( target ){
        default:
            input = &silhouette;
        break;

        case 1: 
            input = &freehand;
        break;
    }
    
    switch( routine ){
        case 0 :
            label = "void np::polyworks::inflate( const ofPolyline & src, ofPolyline & dest, float amount )";
            np::polyworks::inflate( *input, result, ofGetMouseX()*0.5f );
        break;

        case 1 :
            label = "void np::polyworks::push( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount )";
            np::polyworks::push( *input, result, mouse, 150 );
        break;
        
        case 2 :
            label = "void np::polyworks::collapse( const ofPolyline & src, ofPolyline & dest, float amount )";
            np::polyworks::collapse( *input, result, ofGetMouseX()*0.5f );
        break;

        case 3 :
            label = "void np::polyworks::suck( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount )";
            np::polyworks::suck( *input, result, mouse, 150 );
        break;

        case 4 :
            label = "void np::polyworks::radial( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float angle, float arc=PI*1.5f, float off = 0.0f, float correction = 0.3f )";
            np::polyworks::radial( *input, result, glm::vec2( ofGetWidth()*0.5f, ofGetHeight()*0.5f), mx*TWO_PI );
        break;
        
        case 5 :
            label = "void np::polyworks::stretch( const ofPolyline & src, ofPolyline & dest, float xAmount, float yAmount )\n";
            label += "void np::polyworks::basealign( ofPolyline & dest, float yBase )";
            np::polyworks::stretch( *input, result, mx*4.0f, 1.0f );
            np::polyworks::basealign(  result, base );
        break;
        
        case 6 :
            label = "void np::polyworks::jitter( const ofPolyline & src, ofPolyline & dest, float xAmount, float yAmount=0.0f, float chance=0.03f )";
            np::polyworks::jitter( *input, result, mx*100.0f, my*50.0f, 0.3f );
        break;
        
        case 7:
            label = "void np::polyworks::point( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float pct )";
            np::polyworks::point( *input, result, center, my );
        break;
        
        case 8:
            label = "void np::polyworks::xslicer( const ofPolyline & src, ofPolyline & dest, float amount, float slicewidth, float speed = 0.01f, float density=250.0f )";
            np::polyworks::xslicer( *input, result, mx*200, 40.0f );
        break;

        case 9:
            label ="void np::polyworks::noise( const ofPolyline & src, ofPolyline & dest, float amount, float speed=0.2f, float offset=0.01f, float density=120.0f )";
            np::polyworks::noise( *input, result, mx*4.0f );
        break;

        case 10:
            label = "void np::polyworks::normals_expand( const ofPolyline & src, ofPolyline & dest, float amount, float sign = -1.0f )\n";
            label += "void smooth( ofPolyline & dest, float amount=2.0f )";
            np::polyworks::normals_expand( *input, result, mx*50.0f );
            np::polyworks::smooth( result, my*10 );
        break;    
        
        case 11:
            label ="void np::polyworks::subpoly( const ofPolyline & src, ofPolyline & dest, float start, float stop )";
            np::polyworks::subpoly( *input, result, my, my+0.25f );
        break;
    
        case 12:
            label = "void np::polyworks::xmirror( const ofPolyline & src, ofPolyline & dest, float mirrorpoint )";
            np::polyworks::xmirror( *input, result, ofGetMouseX() );
        break;

        case 13:
            label = "void np::polyworks::lerp( const ofPolyline & srcA, const ofPolyline &srcB, ofPolyline & dest, float a, float density=120.0f )";
            np::polyworks::lerp( silhouette, freehand, result, mx );
        break;    

        case 14:
            label = "void np::polyworks::radialwarp( const ofPolyline & srcA, const ofPolyline &srcB, ofPolyline & dest, const glm::vec2 & origin, float a, float density=120.0f )";
            np::polyworks::radialwarp( silhouette, freehand, result, glm::vec2(ofGetWidth()*0.5f, ofGetHeight()), mx );
        break;

        default: break;
    }

    label += "\n\npress RETURN for next routine and BACKSPACE for previous";
    label += "\nmove the mouse for some control ";
    label += "\nclick to draw a shape, SPACEBAR to start a new shape";
    label += "\npress TAB to change target. target = ";
    switch( target ){
        case 0: label +="silhouette"; break;
        case 1: label += "freehand shape"; break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();

    auto drawpoly = []( ofPolyline & poly, bool close=true ) noexcept { 
        auto & vertices = poly.getVertices();
        ofBeginShape();
        for( size_t v=0; v<vertices.size(); ++v ){
            ofVertex( vertices[v].x, vertices[v].y );
        }
        ofEndShape(close);
    };
    ofSetColor( 120, 0, 0 );
    drawpoly( silhouette );
    drawpoly( freehand );
    ofSetColor( 255 );
    drawpoly( result );
    
    ofDrawBitmapString( label, 20, 20 );
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch( key ){    
        case ' ':
            freehand.addVertex( freehand.getVertices()[0] );
            freehandIsDone = true;
        break;
        case OF_KEY_RETURN : 
            routine++;
            if( routine > ROUTINEMAX ){ routine = 0; }
        break;
        
        case OF_KEY_BACKSPACE: 
            routine--;
            if(routine<0){ routine = ROUTINEMAX; }
        break;
        
        case OF_KEY_TAB: 
            target = target ? 0 : 1;
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
