
#pragma once 

#include "ofMain.h"
#include <limits>

namespace np { namespace polyworks {
    
    
void push( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount );
        

inline void inflate( const ofPolyline & src, ofPolyline & dest, float amount ){
    push( src, dest, src.getCentroid2D(), amount );
}
    
void stretch( const ofPolyline & src, ofPolyline & dest, float xAmount, float yAmount );
 
inline void smooth( ofPolyline & dest, float amount=2.0f ){ dest = dest.getSmoothed( amount ); }

float find_min_y( const ofPolyline & src );
float find_max_y( const ofPolyline & src );
float find_min_x( const ofPolyline & src );
float find_max_x( const ofPolyline & src );

void basealign( ofPolyline & dest, float yBase );
inline void basealign( ofPolyline & dest, const ofPolyline & alignTo ){ basealign( dest, find_max_y( alignTo) ); }

void xalign( ofPolyline & dest, float x );
inline void xalign( ofPolyline & dest, const ofPolyline & alignTo ){ xalign( dest, alignTo.getCentroid2D().x ); }

void radial(    const ofPolyline & src, ofPolyline & dest, 
                const glm::vec2 & origin, 
                float angle, float arc=PI*1.5f, 
                float off = 0.0f, float correction = 0.3f );

void normals_expand( const ofPolyline & src, ofPolyline & dest, float amount, float sign = -1.0f );

}}
