
#include "polyworks.h"

void np::polyworks::push( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();
    for( size_t v=0; v<destVerts.size(); v++) {
        auto difference = srcVerts[v] - origin;
        auto outside = glm::normalize(difference);
        outside = outside * amount;
        destVerts[v] = srcVerts[v] + outside;
    }
}
    
void np::polyworks::suck( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float amount ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();
    glm::vec3 origin3 = glm::vec3(origin.x, origin.y, 0.0f);

    for( size_t v=0; v<destVerts.size(); v++) {
        auto difference = srcVerts[v] - origin;
        float distance = glm::distance( srcVerts[v], origin3 );
        auto inside = glm::normalize(difference);
        float amt = (amount<distance) ? amount : distance;
        inside = inside * amt;
        destVerts[v] = srcVerts[v] - inside;
    }
}    

void np::polyworks::point( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float pct ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();

    glm::vec3 origin3 = glm::vec3(origin.x, origin.y, 0.0f);
    for( size_t v=0; v<destVerts.size(); v++) {
        destVerts[v] = glm::mix( srcVerts[v], origin3, pct );
    }
}    

void np::polyworks::stretch( const ofPolyline & src, ofPolyline & dest, float xAmount, float yAmount ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();
    auto center = src.getCentroid2D();
    for( size_t v=0; v<destVerts.size(); v++ ){
        auto difference = srcVerts[v] - center;
        auto outside = difference;
        outside.x *= xAmount;
        outside.y *= yAmount;
        destVerts[v] = center + outside;
    }
}
 
float np::polyworks::find_min_y( const ofPolyline & src ){
    float min = std::numeric_limits<float>::max();
    auto & vertices = src.getVertices();
    for( auto & vertex : vertices ){
        min = ( vertex.y < min ) ? vertex.y : min; 
    }
    return min;
}
float np::polyworks::find_max_y( const ofPolyline & src ){
    float max = std::numeric_limits<float>::lowest();
    auto & vertices = src.getVertices();
    for( auto & vertex : vertices ){
        max = ( vertex.y > max ) ? vertex.y : max; 
    }
    return max;
}
float np::polyworks::find_min_x( const ofPolyline & src ){
    float min = std::numeric_limits<float>::max();
    auto & vertices = src.getVertices();
    for( auto & vertex : vertices ){
        min = ( vertex.x < min ) ? vertex.y : min; 
    }
    return min;
}
float np::polyworks::find_max_x( const ofPolyline & src ){
    float max = std::numeric_limits<float>::lowest();
    auto & vertices = src.getVertices();
    for( auto & vertex : vertices ){
        max = ( vertex.x > max ) ? vertex.y : max; 
    }
    return max;
}

void np::polyworks::basealign( ofPolyline & dest, float yBase ){
    float srcbase = find_max_y( dest );
    float diff = yBase - srcbase;
    auto & destVerts = dest.getVertices();
    for( size_t v=0; v<destVerts.size(); v++ ){
        destVerts[v].y += diff;
    }
}

void np::polyworks::xalign( ofPolyline & dest, float x ){
    float srcbase = dest.getCentroid2D().x;
    float diff = x - srcbase;
    auto & destVerts = dest.getVertices();
    for( size_t v=0; v<destVerts.size(); v++ ){
        destVerts[v].x += diff;
    }
}
   
void np::polyworks::radial( const ofPolyline & src, ofPolyline & dest, const glm::vec2 & origin, float angle, float arc, float off, float correction ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();

    
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();
    
    for( auto & vertex : srcVerts ){
        minX = ( vertex.x < minX ) ? vertex.x : minX; 
        maxX = ( vertex.x > maxX ) ? vertex.x : maxX;
        minY = ( vertex.y < minY ) ? vertex.y : minY; 
        maxY = ( vertex.y > maxY ) ? vertex.y : maxY;
    }    
    
    float radius = abs( maxY - minY );
    
    float avgx = (minX + maxX) * 0.5f;

    for( size_t i=0; i<destVerts.size(); ++i ){

        float y = ofMap( srcVerts[i].y, minY, maxY, 1.0f, 0.0f, true );
        float offset = 0.5f - y*correction;

        float theta = ofMap( srcVerts[i].x-avgx, -radius, radius, angle - arc*offset, angle + arc*offset );

        float r = (y+off) * radius;

        destVerts[i].x = origin.x + cos( theta ) * r;
        destVerts[i].y = origin.y + sin( theta ) * r;
    }
}

void np::polyworks::normals_expand( const ofPolyline & src, ofPolyline & dest, float amount, float sign ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();

    float mult = amount * sign;
    for (size_t v=0; v<destVerts.size(); v++) {
        glm::vec2 normal = src.getNormalAtIndex(v) * mult;
        destVerts[v] = srcVerts[v] + normal;
    }
}

void np::polyworks::jitter( const ofPolyline & src, ofPolyline & dest, float xAmount, float yAmount, float chance ){
    dest = src;
    auto & destVerts = dest.getVertices();
    
    for (size_t v=0; v<destVerts.size(); v++) {
        if( ofRandomuf() < chance ){
            destVerts[v].x += ofRandom( -xAmount, xAmount );
            destVerts[v].y += ofRandom( -yAmount, yAmount );
        }
    }
}

void np::polyworks::xslicer( const ofPolyline & src, ofPolyline & dest, float amount, float slicewidth, float speed, float density ){
    dest.clear();
    
    float step = 1.0f / density;
    for( float pct=0.0f; pct<=1.0f; pct+=step ){
        auto point = src.getPointAtPercent( pct );
        int c = point.y / slicewidth;
        point.x += ofSignedNoise( c*4.0f, ofGetElapsedTimef()*speed ) * amount;
        dest.addVertex( point.x, point.y );
    }
}

void np::polyworks::yslicer( const ofPolyline & src, ofPolyline & dest, float amount, float slicewidth, float speed, float density ){
    dest.clear();
    
    float step = 1.0f / density;
    for( float pct=0.0f; pct<=1.0f; pct+=step ){
        auto point = src.getPointAtPercent( pct );
        int c = point.x / slicewidth;
        point.y += ofSignedNoise( c*4.0f, ofGetElapsedTimef()*speed ) * amount;
        dest.addVertex( point.x, point.y );
    }
}


void np::polyworks::noise( const ofPolyline & src, ofPolyline & dest, float amount, float speed, float offset, float density ){
    dest.clear();
    float step = 1.0f / density;
    auto center = src.getCentroid2D();
    
    for( float pct=0.0f; pct<=1.0f; pct+=step ){
        auto point = src.getPointAtPercent( pct );
        auto difference = point - center;
        auto outside = difference;
        float noise = ofNoise(point.x*offset, point.y*offset, ofGetElapsedTimef()*speed) * amount;
        auto output = point + (outside * noise);
        dest.addVertex( output.x, output.y );
    }
}

void np::polyworks::lerp( const ofPolyline & srcA, const ofPolyline &srcB, ofPolyline & dest, float a, float density ){
    dest.clear();
    float step = 1.0f / density;
    for( float pct=0.0f; pct<=1.0f; pct+=step ){
        auto point = glm::mix( srcA.getPointAtPercent(pct), srcB.getPointAtPercent(pct), a );
        dest.addVertex( point.x, point.y );
    }
}

void np::polyworks::radialwarp( const ofPolyline & srcA, const ofPolyline &srcB, ofPolyline & dest, const glm::vec2 & origin, float a, float density ){
    dest.clear();
    float step = 1.0f / density;
    glm::vec3 origin3 = glm::vec3( origin.x, origin.y, 0.0f );
    for( float pct=0.0f; pct<=1.0f; pct+=step ){
        auto pA = srcA.getPointAtPercent(pct);
        float thetaA = atan2( pA.y - origin3.y, pA.x - origin3.x );
        float radA = glm::distance( pA, origin3 );
        
        auto pB = srcB.getPointAtPercent( pct );
        float thetaB = atan2( pB.y - origin3.y, pB.x - origin3.x );
        float radB = glm::distance( pB, origin3 );
 
        float theta = thetaA * (1.0f-a) + thetaB * a;
        float radius = radA * (1.0f-a) + radB * a;
        
        float x = origin3.x + cos( theta )*radius;
        float y = origin3.y + sin( theta )*radius;
        
        dest.addVertex( x, y );
    }
}


void np::polyworks::subpoly( const ofPolyline & src, ofPolyline & dest, float start, float stop ){
    dest.clear();
    bool wrap = false;
    
    float fMinIndex = start * float( src.size()-1 );
    float fMaxIndex = stop * float( src.size()-1 );
    
    if( stop > 1.0f ){
        wrap = true;
        fMaxIndex = fmod( fMaxIndex, float( src.size()-1 ));
    }
    int min = ceil( fMinIndex );
    int max = fMaxIndex;
    
    if( float(min) != fMinIndex ){
        dest.addVertex( src.getPointAtIndexInterpolated(fMinIndex) );
    }
    
    if( wrap ){
        auto & srcVerts = src.getVertices();
        for( int i=min; i<(int)srcVerts.size(); ++i ){
            dest.addVertex( srcVerts[i].x, srcVerts[i].y );
        }
        for( int i=0; i<=max; ++i ){
            dest.addVertex( srcVerts[i].x, srcVerts[i].y );
        }
    }else{
        auto & srcVerts = src.getVertices();
        for( int i=min; i<=max; ++i ){
            dest.addVertex( srcVerts[i].x, srcVerts[i].y );
        }        
    }

    if( float(max) != fMaxIndex ){
        dest.addVertex( src.getPointAtIndexInterpolated(fMaxIndex) );
    }
}


void np::polyworks::xmirror( const ofPolyline & src, ofPolyline & dest, float mirrorpoint ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();

    for( size_t v=0; v<destVerts.size(); v++ ){
        destVerts[v].x = mirrorpoint + mirrorpoint - srcVerts[v].x;
        destVerts[v].y = srcVerts[v].y;
    }
}

void np::polyworks::ymirror( const ofPolyline & src, ofPolyline & dest, float mirrorpoint ){
    dest.resize( src.size() );
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();

    for( size_t v=0; v<destVerts.size(); v++ ){
        destVerts[v].x = srcVerts[v].x;
        destVerts[v].y = mirrorpoint + mirrorpoint - srcVerts[v].y;
    }
}


void np::polyworks::inside( const ofPolyline & srcA, const ofPolyline & srcB, std::vector<ofPolyline> & results, float density  ){
    //dest.clear();
    float step = 1.0f / density;
    float outside = true;
    
    for( float pct=0.0f; pct<=1.0f; pct+=step ){
        auto pA = srcA.getPointAtPercent(pct);
        if( srcB.inside( pA.x, pA.y ) ) {
            if( outside ){
                results.emplace_back();
                results.back().clear();
                outside = false;
            }
            results.back().addVertex( pA.x, pA.y );
        }else{
            outside = true;
        }
    }
    
}
