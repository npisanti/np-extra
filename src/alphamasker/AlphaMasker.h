
#pragma once

#include "ofMain.h"

#ifndef STRINGIFY_ALPHAMASK
#define STRINGIFY_ALPHAMASK(...) STRINGIFY_ALPHAMASK_AUX(__VA_ARGS__)
#define STRINGIFY_ALPHAMASK_AUX(...) #__VA_ARGS__
#endif

namespace np{

class AlphaMasker {

public:    
    void setup (int w, int h);
    void reallocate( int w, int h );

    void draw( int x, int y );
    void draw( int x, int y, int w, int h );
        
    void maskFromContours( const std::vector<ofPolyline> & contours );
    
    void maskAndDraw( ofFbo & mask, ofFbo & canvas, int x=0, int y=0 );
    
    ofFbo canvas;
    ofFbo mask;
            
private:
    
    string vertexShader();
    string fragmentShader();

    ofShader masker;
    
};

}
