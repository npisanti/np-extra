
#pragma once

#include "ofMain.h"

namespace np {

class PaletteTableRGB {
    
public:
    void setup ( int numColors );

    const ofColor & color() const;
    void            roundIndex();

    ofParameterGroup    parameters;

    ofParameter<float>              tIndex;    
    vector<ofParameter<ofColor>>    colors;  
    
private:
    ofColor tColor;
  
    void onChange( int & value );
    void refreshColor( ofColor & value );
    void indexChange( float & value );

};

}
