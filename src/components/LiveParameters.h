
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

    void reload();

    // --- variables for live check ---
    float interval;
    time_t writeTimestamp;
    float timePassed;
    void checkFile(ofEventArgs &args);
};
    
}
