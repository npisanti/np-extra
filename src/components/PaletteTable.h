
#pragma once

#include "ofMain.h"

namespace np {

class PaletteTable {
    
public:
    void setup ( int numPalettes, int numColors=1 );

    const ofColor & color( int index = 0 ) const;
    void            roundIndex();

    ofParameterGroup    parameters;

    ofParameter<float>                              tIndex;    
    std::vector<std::vector<ofParameter<ofColor>>>  colors;  
    std::vector<ofParameterGroup> palettes;
    
    ofParameterGroup test;    
        ofParameter<int>  testAlpha;
        ofParameter<bool> testFill;

    void draw( int x, int y, int w, int h);
    
private:
    std::vector<ofColor> tColors;
  
    void refreshColor( ofColor & value );
    void indexChange( float & value );

};

}
