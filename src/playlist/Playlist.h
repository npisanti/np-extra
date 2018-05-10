
#pragma once

#include "ofMain.h"
#include "PathGiver.h"

namespace np{
    
class Playlist {
  
public:
    Playlist();
    
    void setup( PathGiver & paths );
    
    void next( bool now=true );
    
    void restart();
    
    void autonext( bool active = true );
    
    void draw( int x, int y, float scale );
    
    int frame() const;
    
    float getWidth() const { return buffers[b].getWidth(); }
    float getHeight() const { return buffers[b].getHeight(); }
    
    std::string path() const { return currentpath; }
    std::string nextPath() const { return nextpath; }

    ofParameter<float> speed;

private:
    std::vector<int> vindex;
    
    void change();
    
    float oldposition;
    
    int v;
    int b;
    
    std::vector<ofVideoPlayer>  buffers;
    
    bool bChangeOnEnd;
    bool bAutoNext;
    
    PathGiver * paths;
    
    std::string currentpath;
    std::string nextpath;
};
    
}
