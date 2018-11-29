
#pragma once 

#include "ofMain.h"
#include <limits>

namespace np { namespace polyworks {
    
void push( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount );
        
inline void inflate( const ofPolyline & src, ofPolyline & dest, float amount ){ push( src, dest, src.getCentroid2D(), amount ); }
    
void suck( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount );

inline void collapse( const ofPolyline & src, ofPolyline & dest, float amount ){ suck( src, dest, src.getCentroid2D(), amount ); }

// reduce polyline to a point
void point( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float pct );

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

void jitter( const ofPolyline & src, ofPolyline & dest, float xAmount, float yAmount=0.0f, float chance=0.03f );

void xslicer( const ofPolyline & src, ofPolyline & dest, float amount, float slicewidth, float speed = 0.01f, float density=250.0f );

void yslicer( const ofPolyline & src, ofPolyline & dest, float amount, float slicewidth, float speed = 0.01f, float density=250.0f );

void noise( const ofPolyline & src, ofPolyline & dest, float amount, float speed=0.2f, float offset=0.01f, float density=120.0f );

void lerp( const ofPolyline & srcA, const ofPolyline &srcB, ofPolyline & dest, float a, float density=120.0f );

void radialwarp( const ofPolyline & srcA, const ofPolyline &srcB, ofPolyline & dest, const glm::vec2 & origin, float a, float density=120.0f );

}}
