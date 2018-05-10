
#include "RandomPaths.h"

const std::string np::RandomPaths::wrong = "wrong mode";

np::RandomPaths::RandomPaths(){
    index = 0;
    mode = 0;
}


void np::RandomPaths::add( std::string path ){
    paths.push_back( path );
    ofLogVerbose()<<"[random paths] adding folder "<<path<<"\n";
    index = rand()%paths.size();
}


const std::string & np::RandomPaths::next(){
    
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

