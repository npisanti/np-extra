#pragma once

#include "ofMain.h"
#include "ofxGui.h"

// this should match the projector resolution
#define PROJECTOR_WIDTH 720
#define PROJECTOR_HEIGHT 480

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void drawSecondWindow(ofEventArgs& args);
    
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofFbo 		fbo;
        
        bool		bDrawGui;
		ofxPanel 	gui;

};
