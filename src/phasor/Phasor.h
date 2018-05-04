
#pragma once

#include "ofMain.h"

namespace np{
    
/*
    // to add a listener: 
    phazor.bEvent = true;
    ofAddListener( phazor.event, this, &ofApp::phazorEvent);
	// the methods to pass should be like this
    void phazorEvent( float & value ){ }
 */     
    
class Phasor {

public:
    Phasor();
    
    void update( ofEventArgs & events );
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
    
private:

    float 	speedCalculated;    
    bool    bReached;
    float   ph;
    
    void onRetrigParameter( bool & value );
    void onSpeedParameter( float & value );
    
};    
    
}
