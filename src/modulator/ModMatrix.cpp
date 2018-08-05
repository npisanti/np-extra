
#include "ModMatrix.h"


np::ModMatrix::ModMatrix(){
    parameters.setName( "modulation matrix" );
}

np::ModMatrix::~ModMatrix(){
    for( size_t i=0; i<slots.size(); ++i ){
       delete slots[i].modulator;
    }
}

ofParameterGroup & np::ModMatrix::label( std::string name ){
    parameters.setName( name );
    return parameters;
}

np::ModMatrix::Slot::Slot(){
    source = nullptr;
    modulator = nullptr;
}

void np::ModMatrix::link( const float & source, ofParameter<float> & dest ){
    link( source, dest, "m2 "+dest.getName() );
}
void np::ModMatrix::link( const float & source, ofParameter<int> &dest ){
    link( source, dest, "m2 "+dest.getName() );
}

np::Modulator & np::ModMatrix::slot( int index ){
    return *(slots[index].modulator);
}

void np::ModMatrix::link( const float & source, ofParameter<float> & dest, std::string name ){
    slots.emplace_back();
    slots.back().source = &source;

    np::Modulator * mod = new np::Modulator();
    slots.back().modulator = mod;
        
    mod->link( dest, name );
    parameters.add( mod->parameters );
}

void np::ModMatrix::link( const float & source, ofParameter<int> & dest, std::string name ){
    slots.emplace_back();
    slots.back().source = &source;

    np::Modulator * mod = new np::Modulator();
    slots.back().modulator = mod;
        
    mod->link( dest, name );
    parameters.add( mod->parameters );
}

void np::ModMatrix::update(){
    for( size_t i=0; i<slots.size(); ++i ){
        slots[i].modulator->modulate( *(slots[i].source) );
    }
}

