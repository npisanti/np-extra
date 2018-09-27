
#ifndef NPEXTRA_SERIALIZE_POINTS_H
#define NPEXTRA_SERIALIZE_POINTS_H

#include "ofMain.h"

namespace np {

    inline void serialize_points( std::string path, const std::vector<glm::vec3> & v );

    inline void deserialize_points( std::string path, std::vector<glm::vec3> & v );


    inline void serialize_points( std::string path, const std::vector<ofVec3f> & v );

    inline void deserialize_points( std::string path, std::vector<ofVec3f> & v );

}

#endif //NPEXTRA_SERIALIZE_POINTS_H
