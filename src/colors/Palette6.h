
#pragma once

#include "ofMain.h"

namespace np {

class Palette6 {
    
public:
    Palette6();
    
    void setup ( int hue, int saturation, int satOffset, int hueOffset );

    void draw( int x, int y, int w, int h);
    
    vector<ofColor> colors;

    ofParameter<int> hue;
    ofParameter<int> saturation;
    
    ofParameter<int> satOffset;
    ofParameter<int> hueOffset;

    ofParameter<int>  testAlpha;
    ofParameter<bool> testFill;

    ofParameterGroup ui;
    ofParameterGroup testUi;
private:
    
    void onChange( int & value );

};

}
