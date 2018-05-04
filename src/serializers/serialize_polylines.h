
#pragma once

#include "ofMain.h"

namespace np {
    
    void serialize_polylines( std::string path, const std::vector<ofPolyline> & v );
    void deserialize_polylines( std::string path, std::vector<ofPolyline> & v );
    
}
