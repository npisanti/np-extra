

#include "Phasor.h"

np::Phasor::Phasor() {
    ph = 0.0f;
    bReached = false;
    
    speed.addListener( this, &Phasor::onSpeedParameter );
    
    parameters.setName("please label me" );
    parameters.add( speed.set("speed", 0.15f, 0.0f, 1.0f ) );
    parameters.add( oneshot.set("oneshot", false));
    parameters.add( direction.set("positive", true));
    parameters.add( retrig.set("retrig button", false));

    retrig.addListener( this, &Phasor::onRetrigParameter);
    
	ofAddListener( ofEvents().update, this, &Phasor::update);  
}

    
ofParameterGroup & np::Phasor::label( std::string name ){
    parameters.setName(name);
    return parameters;
}

void np::Phasor::update( ofEventArgs & events ) {
    if( !bReached ){
		float step = abs(speedCalculated) * ofGetLastFrameTime();
		
		if( direction ){
			ph += step;
			
			if(ph >= 1.0f){
				if(oneshot){
					ph = 1.0f;
					bReached = true;
				}else{
					int ph_i = ph;
					ph -= (float) ph_i;                
				}
				if(bEvent) ofNotifyEvent(event, ph, this);
			}  			
		}else{
			ph -= step;	
			// do all the checks like positive
			if(ph < 0.0f){
				if(oneshot){
					ph = 0.0f;
					bReached = true;
				}else{
					int ph_i = ph;
					ph += 1.0f + (float) ph_i;                
				}
				if(bEvent) ofNotifyEvent(event, ph, this);		
			}
		}
    }
    
}

void np::Phasor::retrigger() {
    if(direction){
		ph = 0.0f;
	}else{
		ph = 1.0f;
	}
    bReached = false;
}

void np::Phasor::retrigger( float startphase ){
    ph = startphase;
    bReached = false;
}

bool np::Phasor::running() const{
    return !bReached;
}

void np::Phasor::set( float newphase ){
	ph = newphase;
}

float np::Phasor::phase() const {
    return ph;
}
    
float np::Phasor::inverted() const {
    return (1.0f-ph);
}
    
void np::Phasor::onRetrigParameter( bool & value ) {
	if( value ){ 
		retrigger();
		retrig = false;
	}
}
void np::Phasor::onSpeedParameter( float & value ) {
	speedCalculated = (value*value)*6.0f;
}
