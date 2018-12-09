#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

#ifdef __ARM_ARCH
        ofGLESWindowSettings settings;
        settings.glesVersion = 2;
        settings.setSize( 1600, 800 );
        ofCreateWindow(settings);
#else        
		ofGLWindowSettings settings;
        settings.setSize( 1600, 800 );
        ofCreateWindow(settings);      
#endif
        ofRunApp(new ofApp());

}
