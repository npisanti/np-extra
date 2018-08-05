
#pragma once 

#include "Modulator.h"

namespace np{
    
class ModMatrix{

public:
    
    ModMatrix();
    ~ModMatrix();

    void link( const float & source, ofParameter<float> & dest, std::string name );
    void link( const float & source, ofParameter<int> & dest, std::string name );
    void link( const float & source, ofParameter<float> & dest );
    void link( const float & source, ofParameter<int> &dest );
    
    
    np::Modulator & slot( int index );
    
    void update();

    ofParameterGroup & label( std::string name );

    ofParameterGroup parameters;

    
private:
    class Slot{
    public:
        Slot();
        const float * source;
        np::Modulator * modulator;
    };

    std::vector<Slot> slots;
    
};
    
    
}
