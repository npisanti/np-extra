
// Palette6.cpp
// Nicola Pisanti, GPLv3 License, 2016

#include "Palette6.h"


np::Palette6::Palette6() {
    
    colors.resize(6);
    ui.setName("palette");    
    ui.add( hue.set( "hue", 0, 0, 255) );
    ui.add( saturation.set( "saturation", 240, 0, 255) );
    ui.add( hueOffset.set( "hue offset", 12, 0, 130) ); 

    
    hue.addListener( this, &Palette6::onChange );
    saturation.addListener( this, &Palette6::onChange );
    satOffset.addListener( this, &Palette6::onChange );
    hueOffset.addListener( this, &Palette6::onChange );

    ui.add( satOffset.set( "saturation subtract", 80, 0, 200) );     
    
    testUi.setName("palette test");
    testUi.add( testAlpha.set( "alpha", 255, 0, 255) );
    testUi.add( testFill.set( "fill", false) );
    
    int fakeValue = 255;
    onChange(fakeValue);
}


void np::Palette6::setup ( int hue, int saturation, int satOffset, int hueOffset ) {
    
    this->hue = hue;
    this->saturation = saturation;
    this->satOffset = satOffset;
    this->hueOffset = hueOffset;
    
}


void np::Palette6::onChange( int & value ) {
    
    for(int x=0; x<3; ++x){
        
        for (int y=0; y<2; ++y){
            
            int ch = hue + x*hueOffset; 
            if(ch >= 256 ) ch -= 256;
            if(ch < 0 ) ch += 256;
            
            int csat;
            switch( y){
                case 0:
                    csat = saturation; 
                break;
                
                case 1:
                    csat = saturation  - satOffset; 
                    if(csat < 0 ) csat = 0;
                break;
            }

            colors[x + y*3].setHsb( ch, csat, 255);
            
        }
        
    }
    
}


void np::Palette6::draw( int x, int y, int w, int h) {
    
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
