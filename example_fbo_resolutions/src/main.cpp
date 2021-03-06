#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

#ifdef __ARM_ARCH
        ofGLESWindowSettings settings;
        settings.glesVersion = 2;
        settings.setSize( 640, 480 );
        ofCreateWindow(settings);
#else        
		ofGLWindowSettings settings;
        settings.setSize( 640, 480 );
        ofCreateWindow(settings);      
#endif
        ofRunApp(new ofApp());

}
