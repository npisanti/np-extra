
// PaletteTable.cpp
// Nicola Pisanti, GPLv3 License, 2016

#include "PaletteTable.h"


void np::PaletteTable::setup ( int numColors ) {
    
    colors.resize(numColors+1);
    hues.resize(numColors);
    saturations.resize(numColors);
    brightnesses.resize(numColors);
    colors[numColors] = ofColor::black;

    ui.setName("palette");    

    tIndex.addListener( this, &PaletteTable::indexChange );    
    ui.add( tIndex.set( "table index", 0.0f, 0.0f, numColors-1) ); 

    for( int i=0; i<numColors; ++i){
        hues[i].addListener( this, &PaletteTable::onChange );
        saturations[i].addListener( this, &PaletteTable::onChange );
        brightnesses[i].addListener( this, &PaletteTable::onChange );
        ui.add( hues[i].set( "hue " + ofToString(i), 0, 0, 255) );
        ui.add( saturations[i].set( "saturation " + ofToString(i), 240, 0, 255) );        
        ui.add( brightnesses[i].set( "brightness " + ofToString(i), 255, 0, 255) );        
    }
    
}


void np::PaletteTable::onChange( int & value ) {
    for(size_t i=0; i<colors.size()-1; ++i){
        colors[i].setHsb( hues[i], saturations[i], brightnesses[i]);
        tIndex = tIndex;       
    }
}


void np::PaletteTable::indexChange( float & value ) {
    int i = value;
    float fract = value - i;
    tColor = colors[i].getLerped( colors[i+1], fract);
}


void np::PaletteTable::roundIndex() {
    int i = tIndex;
    tIndex = i;
}

const ofColor & np::PaletteTable::color() const {
    return tColor;
}

/*
void np::PaletteTable::draw( int x, int y, int w, int h) {
    
    ofPushMatrix();
    ofTranslate( x, y);
        
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0, 0, w, h);
        
        int side =  w / 7.0f;
        int yoff = (h - side*3)/2;
    
        if(testFill){
            ofFill();
        }else{
            ofNoFill();
        }
        
        for(int x=0; x<3; ++x){
            for (int y=0; y<2; ++y){
                
                ofSetColor( colors[x+y*3], testAlpha );            
                ofDrawRectangle ( side+ x*2*side, yoff +y*2*side, side, side );
                
            }
        }
        
    ofPopMatrix();
}
*/
