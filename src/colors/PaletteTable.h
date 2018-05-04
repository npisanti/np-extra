
#pragma once

#include "ofMain.h"

namespace np {

class PaletteTable {
    
public:
    void setup ( int numColors );

    const ofColor & color() const;
    void            roundIndex();

    ofParameterGroup    ui;
    vector<ofParameter<int>>    hues;
    vector<ofParameter<int>>    saturations;
    vector<ofParameter<int>>    brightnesses;
    ofParameter<float>          tIndex;
    
private:
    ofColor tColor;
    
    vector<ofColor> colors;    
    void onChange( int & value );
    void indexChange( float & value );

};

}
