
// PaletteTableRGB.cpp
// Nicola Pisanti, GPLv3 License, 2018

#include "PaletteTableRGB.h"


void np::PaletteTableRGB::setup ( int numColors ) {
    
    colors.resize(numColors+1);
    colors[numColors] = ofColor::black;

    parameters.setName("palette");    

    tIndex.addListener( this, &PaletteTableRGB::indexChange );    
    parameters.add( tIndex.set( "table index", 0.0f, 0.0f, numColors-1) ); 

    for( int i=0; i<numColors; ++i){
        parameters.add( colors[i].set( "color " + ofToString(i), ofColor(255), ofColor(0), ofColor(255)) );  
        colors[i].addListener( this, &PaletteTableRGB::refreshColor );   
    }
    float ok = tIndex;
    indexChange( ok );
}

void np::PaletteTableRGB::refreshColor( ofColor & value ) {
    float ok = tIndex;
    indexChange( ok );
}

void np::PaletteTableRGB::indexChange( float & value ) {
    int i = value;
    float fract = value - i;
    tColor = colors[i].get().getLerped( colors[i+1], fract);
}


void np::PaletteTableRGB::roundIndex() {
    int i = tIndex;
    tIndex = i;
}

const ofColor & np::PaletteTableRGB::color() const {
    return tColor;
}
