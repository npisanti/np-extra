
#pragma once

#include "ofMain.h"

// ------- shared resources between ofApp and scenes ----------------
// shared resources are defined in ofApp.cpp, in the global scope
// and declared here as externs

namespace resources{

    extern ofColor colorA;
    extern ofColor colorB;
    extern float width;
    extern float height;

}
