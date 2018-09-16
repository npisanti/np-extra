
#pragma once

#include "ofMain.h"

namespace np{
    

class Playlist {


public: // ------------------ public API ----------------------------
    class PathGiver{ 
        public: virtual const std::string & next()=0; 
    };

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


public: // --------------- basic PathGiver --------------------------

    class RandomPaths : public PathGiver {
        
        public:
            RandomPaths();

            void add( std::string path );
            const std::string & next() override;
            
        private:
            std::vector<std::string> paths;
            static const std::string wrong;
            
            int index;
            int mode;
    };

private:  // --------------------------------------------------------
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
