#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

#ifdef __ARM_ARCH
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.setSize( 640, 640 );
    ofCreateWindow(settings); 
#else        
	ofSetupOpenGL( 1920, 1080, OF_WINDOW);
#endif

	ofRunApp( new ofApp());
}
