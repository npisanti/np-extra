#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

#ifdef __ARM_ARCH
        ofGLESWindowSettings settings;
        settings.glesVersion = 2;
        settings.width = 640;
        settings.height = 480;
        ofCreateWindow(settings);
#else        
		ofGLWindowSettings settings;
        settings.width = 640;
        settings.height = 480;
        ofCreateWindow(settings);      
#endif
        ofRunApp(new ofApp());

}
