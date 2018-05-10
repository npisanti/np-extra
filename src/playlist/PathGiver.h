
#pragma once

#include "ofMain.h"

namespace np {

class PathGiver{
public:
    virtual const std::string & next()=0;
};

}
