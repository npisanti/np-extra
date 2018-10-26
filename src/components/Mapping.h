
#pragma once

#include "ofMain.h"

namespace np {

class Mapping {

public:
    void setup( int pw, int ph, float mouseScale=1.0f );

    void draw( float scale = 1.0f ); // when mapping is drawing input is active

    std::vector<ofPolyline> mapping;

    ofFbo fbo;

    void renderMask( ofFbo & mask );

private:
    void drawHelp();

    void mousePressed( ofMouseEventArgs& eventArgs );
    void keyPressed( ofKeyEventArgs& eventArgs);

    void saveMapping();
    void loadMapping();

    // ------- mapping ------------
    bool bLight;
    bool bFill;
    bool bShowHelp;
    size_t max = 0;

    void vertexToCurrent( int x, int y );

    // ------- quad warping -------
    ofPoint     cursor;
    float mouseScale;

    u_int64_t currentFrame;
};

}
