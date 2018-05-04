
#pragma once

#include "ofMain.h"

namespace np {

class Palette4 {
    
public:
    Palette4();
    
    void draw( int x, int y, int w, int h);
    
    vector<ofColor> colors;

    ofParameter<int> hue0;
    ofParameter<int> hue1;
    ofParameter<int> hue2;
    ofParameter<int> hue3;
    
    ofParameter<int> saturation0;
    ofParameter<int> saturation1;
    ofParameter<int> saturation2;
    ofParameter<int> saturation3;

    ofParameter<int>  testAlpha;
    ofParameter<bool> testFill;

    ofParameterGroup ui;
    ofParameterGroup testUi;
    
private:
    void onChange( int & value );

};

}
