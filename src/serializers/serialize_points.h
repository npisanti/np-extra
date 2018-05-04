
#pragma once

#include "ofMain.h"

namespace np {
    
    void serialize_points( std::string path, const std::vector<glm::vec3> & v );
    void deserialize_points( std::string path, std::vector<glm::vec3> & v );
    
    void serialize_points( std::string path, const std::vector<ofVec3f> & v );
    void deserialize_points( std::string path, std::vector<ofVec3f> & v );
    
}
