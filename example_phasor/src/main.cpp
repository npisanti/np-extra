#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

#ifdef __ARM_ARCH
        ofGLESWindowSettings settings;
        settings.glesVersion = 2;
        settings.width = 480;
        settings.height = 280;
        ofCreateWindow(settings);
#else        
        ofSetupOpenGL(480, 280, OF_WINDOW);	        
#endif
        ofRunApp(new ofApp());

}
