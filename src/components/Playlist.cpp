
#include "Playlist.h"


// ------------------ np::Playlist ----------------------------------

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

    speed.set("speed", 0.6f, 0.0f, 2.0f );    
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
    draw( x, y, buffers[b].getWidth()*scale, buffers[b].getHeight()*scale );
}

void np::Playlist::draw( int x, int y, int w, int h  ){
    
    buffers[b].setSpeed( speed*speed );    
    
    float position = buffers[b].getPosition();
    if( position < oldposition ){
        if( bChangeOnEnd || bAutoNext ){
            change();
            bChangeOnEnd = false;
        }
    }
    oldposition = position;

    buffers[b].update();    
    buffers[b].draw( x, y, w, h );
}


// ------------------ np::Playlist::RandomPaths ---------------------
const std::string np::Playlist::RandomPaths::wrong = "wrong mode";

np::Playlist::RandomPaths::RandomPaths(){
    index = 0;
    mode = 0;
}


void np::Playlist::RandomPaths::add( std::string path ){
    paths.push_back( path );
    ofLogVerbose()<<"[random paths] adding folder "<<path<<"\n";
    index = rand()%paths.size();
}


const std::string & np::Playlist::RandomPaths::next(){
    
    switch(mode){
        case 0:
        {
            int ni = index;
            while( ni == index ){ // this could be slow if there are few paths
                ni = rand()%paths.size();
            }
            index = ni;
            return paths[index];
        }
        break;
        
        default: break;
    }
    
    return wrong;
}
