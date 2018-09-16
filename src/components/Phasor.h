
#pragma once

#include "ofMain.h"

namespace np{
    
/*
    // to add a listener: 
    phasor.bEvent = true;
    ofAddListener( phasor.event, this, &ofApp::phasorEvent);
	// the methods to pass should be like this
    void phasorEvent( float & value ){ }
 */     
    
class Phasor {

public:
    Phasor();
    
    void update();
    void retrigger();
    void retrigger( float startphase );
    float phase() const;
    float inverted() const;
    void set( float newphase );
    bool running() const;
    
    ofParameterGroup & label( std::string name );
    
    ofParameterGroup parameters;
    ofParameter<float>  speed;
    ofParameter<bool>   oneshot;
    ofParameter<bool>	retrig;
    ofParameter<bool>   direction;
    
    ofEvent<float>  event;
    bool            bEvent;
    
    float maxspeed;
    
    // enable automatic updating
    void autoupdate();
    
private:
    inline void update( ofEventArgs & events ) { update(); }

    float 	speedCalculated;    
    bool    bReached;
    float   ph;
    
    void onRetrigParameter( bool & value );
    void onSpeedParameter( float & value );
    
};    
    
}
