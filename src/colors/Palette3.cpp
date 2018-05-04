
// Palette3.cpp
// Nicola Pisanti, GPLv3 License, 2016

#include "Palette3.h"


np::Palette3::Palette3() {
    
    colors.resize(3);
    ui.setName("palette3");    
    ui.add( hue.set( "hue", 0, 0, 255) );
    ui.add( saturation0.set( "saturation 0", 240, 0, 255) );
    ui.add( hueOffset1.set( "hue offset 1", 12, 0, 130) ); 
    ui.add( saturation1.set( "saturation 1", 240, 0, 255) );
    ui.add( hueOffset2.set( "hue offset 2", 24, 0, 130) ); 
    ui.add( saturation2.set( "saturation 2", 240, 0, 255) );
    
    hue.addListener( this, &Palette3::onChange );
    hueOffset1.addListener( this, &Palette3::onChange );
    hueOffset2.addListener( this, &Palette3::onChange );
    saturation0.addListener( this, &Palette3::onChange );
    saturation1.addListener( this, &Palette3::onChange );
    saturation2.addListener( this, &Palette3::onChange );

    
    testUi.setName("palette test");
    testUi.add( testAlpha.set( "alpha", 255, 0, 255) );
    testUi.add( testFill.set( "fill", false) );
    
    int fakeValue = 255;
    onChange(fakeValue);
}


void np::Palette3::onChange( int & value ) {
    
    colors[0].setHsb( hue, saturation0, 255); 

    int ch = hue + hueOffset1; 
    if(ch >= 256 ) ch -= 256;
    if(ch < 0 ) ch += 256;
    
    colors[1].setHsb( ch, saturation1, 255);     

    ch = hue + hueOffset2; 
    if(ch >= 256 ) ch -= 256;
    if(ch < 0 ) ch += 256;
    
    colors[2].setHsb( ch, saturation2, 255);     
    
}


void np::Palette3::draw( int x, int y, int w, int h) {
    
    ofPushMatrix();
    ofTranslate( x, y);
        
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0, 0, w, h);
        
        int side =  w / 7.0f;
    
        if(testFill){
            ofFill();
        }else{
            ofNoFill();
        }
        
        for(int x=0; x<3; ++x){
            ofSetColor( colors[x], testAlpha );            
            ofDrawRectangle ( side+ x*2*side, 0, side, side );
        }
    ofPopMatrix();

}

