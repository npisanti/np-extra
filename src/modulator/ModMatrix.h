
#pragma once 

#include "Modulator.h"

namespace np{
    
class ModMatrix{

public:
    
    void setup( int slotnum, std::string name = "modulation matrix" );

    void addSource( const float & source, std::string name );
    void addDestination( ofParameter<float> & param, std::string name );
    void addDestination( ofParameter<int> & param, std::string name );
    void addDestination( ofParameter<float> & param );
    void addDestination( ofParameter<int> & param );
    
    void update();

    ofParameterGroup & label( std::string name );

    ofParameterGroup parameters;

    
private:
    struct Slot{
        ofParameterGroup parameters;
            ofParameter<bool> bActive;
            ofParameter<int> source;
            ofParameter<std::string> sourceLabel;
            ofParameter<int> destination;
            ofParameter<std::string> destinationLabel;
            ofParameter<float> tMin;
            ofParameter<float> tMax;
            ofParameter<float> dMin;
            ofParameter<float> dMax;
    };

    struct Source{
        const float * source;
        std::string label;
    };

    class Destination{
    public:
        Destination();
        void link( ofParameter<float> & param );
        void link( ofParameter<int> & param );
        void set( float & value );
        
        float getMin() const;
        float getMax() const;
       
        std::string label;
    private:
        int mode;
        ofParameter<float> * fDest;
        ofParameter<int> * iDest;
    };

    std::vector<Slot> slots;
    std::vector<Source> sources;
    std::vector<Destination> destinations;
    
    
    void onSourceChange( int & value );
    void onDestinationChange( int & value );
    
};
    
    
}
