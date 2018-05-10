
#include "Playlist.h"

np::Playlist::Playlist(){
    b = 0;
    v = 0;
    buffers.resize(2);
    vindex.resize(2);
    for(size_t i=0; i<vindex.size(); ++i){
        vindex[i] = 0; 
        buffers[b].setLoopState( OF_LOOP_NORMAL );
        
        #ifdef TARGET_RASPBERRY_PI
        buffers[b].setPixelFormat(OF_PIXELS_NATIVE);
        #endif
    } 

    speed.set("speed", 0.35f, 0.0f, 1.0f );    
    currentpath = "";
    nextpath = "";
    bChangeOnEnd = false;
    bAutoNext = false;
}

int np::Playlist::frame() const{
    int m = buffers[b].getTotalNumFrames();
    int f = buffers[b].getPosition() * (float) m;
    if (f==m){ f--; }
    return f;
}

void np::Playlist::setup( PathGiver & paths ){
    this->paths = &paths;
}

void np::Playlist::autonext( bool active ){
    bAutoNext = active;
}

void np::Playlist::next( bool now ){
    if( now ){
        change();
    }else{
        bChangeOnEnd = true;
    }
}
    
void np::Playlist::restart(){
    buffers[b].firstFrame();
}
    
void np::Playlist::change(){

    oldposition = 2.0f;
    
    // video switch, two players
    int bn = b ? 0 : 1;    
    
    currentpath = nextpath;
    nextpath = paths->next();
    
    buffers[b].stop();
    buffers[b].close();
    buffers[b].loadAsync( nextpath );
    
    buffers[bn].setLoopState( OF_LOOP_NORMAL );
    buffers[bn].play();

    b = bn;
}

void np::Playlist::draw( int x, int y, float scale ){
    
    buffers[b].setSpeed( speed );    
    
    float position = buffers[b].getPosition();
    if( position < oldposition ){
        if( bChangeOnEnd || bAutoNext ){
            change();
            bChangeOnEnd = false;
        }
    }
    oldposition = position;

    buffers[b].update();    
    buffers[b].draw( x, y, buffers[b].getWidth()*scale, buffers[b].getHeight()*scale );
}
