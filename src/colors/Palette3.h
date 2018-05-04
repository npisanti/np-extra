
#pragma once

#include "ofMain.h"

namespace np {

class Palette3 {
    
public:
    Palette3();
    
    void draw( int x, int y, int w, int h);
    
    vector<ofColor> colors;

    ofParameter<int> hue;
    ofParameter<int> hueOffset1;
    ofParameter<int> hueOffset2;
    
    ofParameter<int> saturation0;
    ofParameter<int> saturation1;
    ofParameter<int> saturation2;

    ofParameter<int>  testAlpha;
    ofParameter<bool> testFill;

    ofParameterGroup ui;
    ofParameterGroup testUi;
    
private:
    void onChange( int & value );

};

}
