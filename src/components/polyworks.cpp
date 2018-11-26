
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
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();
    dest.resize( src.size() );
    
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
    auto & srcVerts = src.getVertices();
    auto & destVerts = dest.getVertices();
    dest.resize( src.size() );

    float mult = amount * sign;
    for (size_t v=0; v<destVerts.size(); v++) {
        glm::vec2 normal = src.getNormalAtIndex(v) * mult;
        destVerts[v] = srcVerts[v] + normal;
    }
}
