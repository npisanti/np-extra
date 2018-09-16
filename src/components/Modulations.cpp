
// Modulations.cpp
// Nicola Pisanti, MIT License, 2018

#include "Modulations.h"

// ---------------------- np::Modulator -----------------------------

np::Modulator::Modulator(){ 
	mode = -1; 
	parameters.setName("m2 not linked");
	bActive = false;
}

ofParameterGroup & np::Modulator::link( ofParameter<int> & parameter, std::string name ) {
	idest = &parameter;
	mode = 0;
    
    parameters.setName( name );
	parameters.add( bActive.set( "active", false) );
	parameters.add( tMin.set("threshold min", 0.0f, 0.0f, 1.0f ) );
	parameters.add( tMax.set("threshold max", 1.0f, 0.0f, 1.0f ) );
	parameters.add( iMin.set("dest min", parameter.getMin(), parameter.getMin(), parameter.getMax()));
	parameters.add( iMax.set("dest max", parameter.getMax(), parameter.getMin(), parameter.getMax()));

	cout << "linked parameter with name: \""<<parameter.getName()<<"\n";
    return parameters;
}


ofParameterGroup & np::Modulator::link( ofParameter<float> & parameter, std::string name ) {
	fdest = &parameter;
	mode = 1;

    parameters.setName( name );
	parameters.add( bActive.set( "active", false) );
	parameters.add( tMin.set("threshold min", 0.0f, 0.0f, 1.0f ) );
	parameters.add( tMax.set("threshold max", 1.0f, 0.0f, 1.0f ) );
	parameters.add( fMin.set("dest min", parameter.getMin(), parameter.getMin(), parameter.getMax()));
	parameters.add( fMax.set("dest max", parameter.getMax(), parameter.getMin(), parameter.getMax()));

	cout << "linked parameter with name: \""<<parameter.getName()<<"\n";
    return parameters;
}

	
ofParameterGroup & np::Modulator::link( ofParameter<float> & parameter ) {
    return link( parameter, "m2 "+ parameter.getName() );
}
ofParameterGroup & np::Modulator::link( ofParameter<int>   & parameter ){
    return link( parameter, "m2 "+ parameter.getName() );
}

void np::Modulator::modulate( float value ) {	
	if(bActive){
		switch( mode ){
			case 0:
				idest->set( ofMap(value, tMin, tMax, iMin, iMax, true ) );
			break;
			
			case 1:
				fdest->set( ofMap(value, tMin, tMax, fMin, fMax, true ) );
			break;
		}
	}
}


ofParameterGroup & np::Modulator::label( std::string name ){
    parameters.setName( name );
    return parameters;
}



// ---------------------- np::ModMatrix -----------------------------

ofParameterGroup & np::ModMatrix::label( std::string name ){
    parameters.setName( name );
    return parameters;
}

void np::ModMatrix::setup( int slotnum, std::string name ){
    parameters.setName( name );
    
    slots.resize( slotnum );
    
    for(size_t i=0; i<slots.size(); ++i){
        
        slots[i].parameters.setName( "slot "+ofToString(i) );
        
        slots[i].parameters.add( slots[i].bActive.set("active", false) );
        slots[i].parameters.add( slots[i].source.set("source", 0, 0, sources.size()-1) );
        slots[i].parameters.add( slots[i].sourceLabel.set("unknown") );
        slots[i].parameters.add( slots[i].destination.set("destination", 0, 0, destinations.size()-1) );
        slots[i].parameters.add( slots[i].destinationLabel.set("unknown") );
        slots[i].parameters.add( slots[i].tMin.set( "threshold min", 0.0f, 0.0f, 1.0f) );
        slots[i].parameters.add( slots[i].tMax.set( "threshold max", 1.0f, 0.0f, 1.0f) );
        slots[i].parameters.add( slots[i].dMin.set( "dest min", 0.0f, 0.0f, 1.0f) );
        slots[i].parameters.add( slots[i].dMax.set( "dest max", 1.0f, 0.0f, 1.0f) );
        
        parameters.add( slots[i].parameters );
        
        slots[i].source.addListener( this, &ModMatrix::onSourceChange );
        slots[i].destination.addListener( this, &ModMatrix::onDestinationChange );
    }
}

void np::ModMatrix::addSource( const float & source, std::string name ){
    sources.emplace_back();
    sources.back().source = &source;
    sources.back().label = name;
    
    for( size_t i=0; i<slots.size(); ++i ){
        slots[i].source.set("source", 0, 0, sources.size()-1);
    }
}

np::ModMatrix::Destination::Destination(){
    mode = -1;
    label = "unknown";
    fDest = nullptr;
    iDest = nullptr;
}

void np::ModMatrix::Destination::link( ofParameter<int> & param ){
    mode = 0;
    label = param.getName();
    iDest = &param;
}

void np::ModMatrix::Destination::link( ofParameter<float> & param ){
    mode = 1;
    label = param.getName();
    fDest = &param;
}

float np::ModMatrix::Destination::getMin() const {
    switch(mode){
        case 0: return float( iDest->getMin()); break;
        case 1: return fDest->getMin(); break;
        default : return 0.0f; break;
    }
}

float np::ModMatrix::Destination::getMax() const {
    switch(mode){
        case 0: return float( iDest->getMax()); break;
        case 1: return fDest->getMax(); break;
        default : return 1.0f; break;
    }
}

void np::ModMatrix::Destination::set( float & value ){
    switch(mode){
        case 0: *iDest = (int) value; break;
        case 1: *fDest = value; break;
        default : break;
    }
}

void np::ModMatrix::addDestination( ofParameter<float> & param ){
    destinations.emplace_back();
    destinations.back().link(param);
    
    for(size_t i=0; i<slots.size(); ++i){
        slots[i].destination.set("destination", 0, 0, destinations.size()-1);
    }
}
void np::ModMatrix::addDestination( ofParameter<int> & param ){
    destinations.emplace_back();
    destinations.back().link(param);

    for(size_t i=0; i<slots.size(); ++i){
        slots[i].destination.set("destination", 0, 0, destinations.size()-1);
    }
}
void np::ModMatrix::addDestination( ofParameter<float> & param, std::string name ){
    addDestination( param );
    destinations.back().label = name;
}
void np::ModMatrix::addDestination( ofParameter<int> & param, std::string name ){
    addDestination( param );
    destinations.back().label = name;
}

void np::ModMatrix::onSourceChange( int & value ){
    for(size_t i=0; i<slots.size(); ++i){
        if( slots[i].source < (int) sources.size() ){
            slots[i].sourceLabel = sources[slots[i].source].label;
        }else{
            slots[i].sourceLabel = "unknown";
        }
    }
}

void np::ModMatrix::onDestinationChange( int & value ){
    
    for(size_t i=0; i<slots.size(); ++i){
        
        if( slots[i].destination < (int) destinations.size() ){
            Destination & dest = destinations[slots[i].destination];
            
            slots[i].destinationLabel = dest.label;
            
            float min = dest.getMin();
            float max = dest.getMax();
            
            float newDMin = slots[i].dMin;
            newDMin = (newDMin>min) ? newDMin : min;
            newDMin = (newDMin<max) ? newDMin : max;
            
            float newDMax = slots[i].dMax;
            newDMax = (newDMax>min) ? newDMax : min;
            newDMax = (newDMax<max) ? newDMax : max;
            
            slots[i].dMin.set( "dest min", newDMin, min, max );
            slots[i].dMax.set( "dest max", newDMax, min, max );
            
        }else{
            
            slots[i].bActive = false;
            slots[i].sourceLabel = "unknown";
        
        }
    }
}



void np::ModMatrix::update(){
    for(size_t i=0; i<slots.size(); ++i){
        if( slots[i].bActive ){
            float input = *(sources[slots[i].source].source);
            float value = ofMap( input, slots[i].tMin, slots[i].tMax, slots[i].dMin, slots[i].dMax, true);
            destinations[slots[i].destination].set( value );            
        }
    }
}

    
