
#pragma once

#include "PathGiver.h"
#include "ofMain.h"

namespace np {

class RandomPaths : public PathGiver {
    
public:
    RandomPaths();

    void add( std::string path );
    const std::string & next() override;
    
private:
    std::vector<std::string> paths;
    static const std::string wrong;
    
    int index;
    int mode;
};

}
