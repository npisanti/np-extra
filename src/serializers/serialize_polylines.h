
#ifndef NPEXTRA_SERIALIZE_POLYLINES_H 
#define NPEXTRA_SERIALIZE_POLYLINES_H 


#include "ofMain.h"

namespace np {
    
    void serialize_polylines( std::string path, const std::vector<ofPolyline> & v );

    void deserialize_polylines( std::string path, std::vector<ofPolyline> & v );
    
}

#endif //NPEXTRA_SERIALIZE_POLYLINES_H 
