
#pragma once

#include "ofMain.h"

namespace np {

    inline string homepath(){
        
        std::string user = ofSystem("whoami");
        user.erase(std::remove(user.begin(), user.end(), '\n'), user.end());
        std::string home = std::string("/home/") + user + std::string("/");
        
        return home;
    }
    
}
