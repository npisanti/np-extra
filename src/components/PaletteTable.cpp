
// PaletteTable.cpp
// Nicola Pisanti, MIT License, 2018

#include "PaletteTable.h"

void np::PaletteTable::setup ( int numPalettes, int numColors  ) {
    
    colors.resize(numPalettes+1);
    palettes.resize( numPalettes );
    for( size_t x=0; x<colors.size(); ++x){
        colors[x].resize( numColors );
    }
    for( size_t y=0; y<colors[numPalettes].size(); ++y){
        colors[numPalettes][y] = ofColor::black;
    }
    tColors.resize( numColors );
    
    parameters.setName("palette table");    

    cursor.addListener( this, &PaletteTable::indexChange );    
    parameters.add( cursor.set( "table cursor", 0.0f, 0.0f, numPalettes-1) ); 

    for( int x=0; x<palettes.size(); ++x){
        palettes[x].setName( "palette "+ofToString(x) );
        
        for( size_t y=0; y<colors[x].size(); ++y){
            palettes[x].add( colors[x][y].set( "color " + ofToString(y), ofColor(255), ofColor(0), ofColor(255)) );
             colors[x][y].addListener( this, &PaletteTable::refreshColor );  
        }
        parameters.add( palettes[x] );
    }
    
    float ok = cursor;
    indexChange( ok );
    
    
    test.setName("palette test");
    test.add( testAlpha.set( "alpha", 255, 0, 255) );
    test.add( testFill.set( "fill", false) );
}

void np::PaletteTable::refreshColor( ofColor & value ) {
    float ok = cursor;
    indexChange( ok );
}

void np::PaletteTable::indexChange( float & value ) {
    int i = value;
    float fract = value - i;
    for( size_t y=0; y<colors[0].size(); ++y ){
        tColors[y] = colors[i][y].get().getLerped( colors[i+1][y], fract);
    }
}

void np::PaletteTable::round() {
    int i = cursor;
    cursor = i;
}

const ofColor & np::PaletteTable::color( int index ) const {
    return tColors[index];
}


void np::PaletteTable::draw( int x, int y, int w, int h) {
    
    ofPushMatrix();
    ofTranslate( x, y);
        
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0, 0, w, h);
        
        int sidex =  w / 2.0f;
        int sidey =  h / (tColors.size()*2.0f);
        int xoff =  (w - sidex)/2;
        int yoff = sidey*0.5;
    
        if(testFill){
            ofFill();
        }else{
            ofNoFill();
        }
        
        for (int y=0; y<tColors.size(); ++y){
            ofSetColor( color(y), testAlpha );            
            ofDrawRectangle ( xoff, yoff + y*2*sidey, sidex, sidey );
        }
        
    ofPopMatrix();
}
