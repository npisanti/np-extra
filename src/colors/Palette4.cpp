
// Palette4.cpp
// Nicola Pisanti, GPLv3 License, 2016

#include "Palette4.h"


np::Palette4::Palette4() {
    
    colors.resize(4);
    ui.setName("palette4");    
    ui.add( hue0.set( "hue 0", 0, 0, 255) );
    ui.add( saturation0.set( "saturation 0", 240, 0, 255) );
    ui.add( hue1.set( "hue 1", 12, 0, 255) ); 
    ui.add( saturation1.set( "saturation 1", 240, 0, 255) );
    ui.add( hue2.set( "hue 2", 24, 0, 255) ); 
    ui.add( saturation2.set( "saturation 2", 240, 0, 255) );
    ui.add( hue3.set( "hue 3", 24, 0, 255) ); 
    ui.add( saturation3.set( "saturation 3", 240, 0, 255) );
    
    hue0.addListener( this, &Palette4::onChange );
    hue1.addListener( this, &Palette4::onChange );
    hue2.addListener( this, &Palette4::onChange );
    hue3.addListener( this, &Palette4::onChange );
    saturation0.addListener( this, &Palette4::onChange );
    saturation1.addListener( this, &Palette4::onChange );
    saturation2.addListener( this, &Palette4::onChange );
    saturation3.addListener( this, &Palette4::onChange );
    
    testUi.setName("palette test");
    testUi.add( testAlpha.set( "alpha", 255, 0, 255) );
    testUi.add( testFill.set( "fill", false) );
    
    int fakeValue = 255;
    onChange(fakeValue);
}


void np::Palette4::onChange( int & value ) {
    
    colors[0].setHsb( hue0, saturation0, 255); 
    colors[1].setHsb( hue1, saturation1, 255);     
    colors[2].setHsb( hue2, saturation2, 255);     
    colors[3].setHsb( hue3, saturation3, 255);     
    
}


void np::Palette4::draw( int x, int y, int w, int h) {
    
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
        
        for(int x=0; x<4; ++x){
            ofSetColor( colors[x], testAlpha );            
            ofDrawRectangle ( side+ x*2*side, 0, side, side );
        }
    ofPopMatrix();

}

