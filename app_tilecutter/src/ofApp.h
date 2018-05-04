
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		
		void cut();
		
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
        
        void rescale();
        
        ofImage input;
        ofImage resized;
        ofImage cutImage;
        ofImage cutResized;
        
        int counter;
        
        ofxPanel gui;
        ofParameter<float> cutX;
        ofParameter<float> cutY;
        ofParameter<float> cutSide;
        ofParameter<float> scale;
        ofParameter<int>   threshold;
        bool bCutDone;
};
