
#pragma once

#include "ofParameterGroup.h"

namespace np {
    
class LiveParameters {

public:
    LiveParameters();

    void watch( ofParameterGroup & parameters, std::string path );
    void setInterval( float time ){ interval=time; }
    
private: 
    ofParameterGroup * parameters;
    
    std::string path;
    float interval = 0.05f;
    time_t writeTimestamp = 0.0f;
    float timePassed = 0.0f;;
    
    void checkFile(ofEventArgs &args);
    void reload();
};
    
}
