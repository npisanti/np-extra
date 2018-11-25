
#pragma once 

#include "ofMain.h"

namespace np { namespace polyworks {
    
inline void inflate( const ofPolyline & src, ofPolyline & dest, float amount ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();
    auto center = src.getCentroid2D();
    for( size_t v=0; v<destVerts.size(); v++) {
        auto difference = srcVerts[v] - center;
        auto outside = glm::normalize(difference);
        outside = outside * amount;
        destVerts[v] = srcVerts[v] + outside;
    }
}
    
inline void smooth( ofPolyline & dest, float amount ){
    dest = dest.getSmoothed( amount );
}

}}
