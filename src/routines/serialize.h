
#pragma once

#include "ofMain.h"

namespace np {

    void serialize_floats( std::string path, const std::vector<float> & v );
    
    void deserialize_floats( std::string path, std::vector<float> & v );


    void serialize_points( std::string path, const std::vector<glm::vec3> & v );
    void serialize_points( std::string path, const std::vector<ofVec3f> & v );
    
    void deserialize_points( std::string path, std::vector<glm::vec3> & v );
    void deserialize_points( std::string path, std::vector<ofVec3f> & v );

    void serialize_polylines( std::string path, const std::vector<ofPolyline> & v );
    
    void deserialize_polylines( std::string path, std::vector<ofPolyline> & v );
    
    void serialize_polylines( std::string path, const std::vector<std::vector<ofPolyline>> & v );
    
    void deserialize_polylines( std::string path, std::vector<std::vector<ofPolyline>> & v );
    
}
