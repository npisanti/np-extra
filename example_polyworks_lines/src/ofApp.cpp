
#include "ofMain.h"
#include "serializers/polylines.h"
#include "components/polyworks.h"

class ofApp : public ofBaseApp{
    
// ---------- members ------------------------------------------
        
ofPolyline silhouette;
std::vector<ofPolyline> result;  
std::vector<ofPolyline> lines;
    
//--------------------------------------------------------------
void setup(){
    
    ofBackground( 0 );
    
    std::vector<std::vector<ofPolyline>> import;
    np::deserialize_polylines( ofToDataPath("silhouette.xml"), import );
    silhouette = import[0][0];
    silhouette.close();

    result.reserve(12);
}

//--------------------------------------------------------------
void update(){

    float mx = ofGetMouseX() / float( ofGetWidth() );
    float my = ofGetMouseY() / float( ofGetHeight() );
    float base = np::polyworks::find_max_y(silhouette);
    auto center = glm::vec2(ofGetWidth()*0.5f, ofGetHeight()*0.5f);

    result.clear();
    lines.resize(50);
    
    auto box = silhouette.getBoundingBox();
    box.scaleFromCenter( 1.2f );
    for( size_t i=0; i<lines.size(); ++i ){
        lines[i].clear();
        float y0 = box.y + ofNoise( i*2.0f, ofGetElapsedTimef()*0.2f ) * box.height;
        float y1 = box.y + ofNoise( i*2.0f + 1.0f, ofGetElapsedTimef()*0.2f ) * box.height;
        lines[i].addVertex( box.x, y0 );
        lines[i].addVertex( box.x + box.width, y0 );
        
        np::polyworks::inside( lines[i], silhouette, result );
    }
}

//--------------------------------------------------------------
void draw(){
    
    
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
    ofSetColor( 255 );
    for( auto & poly : result ){
        drawpoly( poly );
    }
   ofDrawBitmapString( "fps: " + ofToString( ofGetFrameRate()), 20, 20 );
}

//--------------------------------------------------------------
void exit(){

}

//--------------------------------------------------------------
void keyPressed(int key){
    switch( key ){    

    }
}

//--------------------------------------------------------------
void keyReleased(int key){}
void mousePressed(int x, int y, int button){}
void mouseDragged(int x, int y, int button){}
void mouseReleased(int x, int y, int button){}
void mouseMoved(int x, int y){}
void mouseEntered(int x, int y){}
void mouseExited(int x, int y){}
void windowResized(int w, int h){}
void gotMessage(ofMessage msg){}
void dragEvent(ofDragInfo dragInfo){ }

}; // ofApp code end

//--------------------------------------------------------------

// ------------------ MAIN -------------------------------------
#include "ofAppGLFWWindow.h"
int main(int argc, const char** argv)
{
    #ifdef __ARM_ARCH
            ofGLESWindowSettings settings;
            settings.glesVersion = 2;
    #else        
            ofGLWindowSettings settings;
    #endif
    
    settings.setSize( 600, 800 );
    ofCreateWindow(settings);     
    ofRunApp(new ofApp());
}
