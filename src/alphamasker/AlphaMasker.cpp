
// AlphaMasker.cpp
// Nicola Pisanti, MIT License, 2016-2018

#include "AlphaMasker.h"


void np::AlphaMasker::reallocate( int w, int h ) {
    mask.allocate( w, h );
    canvas.allocate( w, h );
}

void np::AlphaMasker::setup (int w, int h ){
    
    ofEnableAlphaBlending();
    
    //mask.allocate( w, h, GL_LUMINANCE );
    mask.allocate( w, h );
    mask.begin();
        ofClear(0,0,0,0);
    mask.end();
    
    canvas.allocate( w, h );
    canvas.begin();
        ofClear(0,0,0,0);
    canvas.end();
    
    masker.setupShaderFromSource( GL_VERTEX_SHADER, vertexShader() );
    masker.setupShaderFromSource( GL_FRAGMENT_SHADER, fragmentShader() );
    masker.linkProgram();  
    
}


void np::AlphaMasker::draw( int x, int y ) {
    ofPushMatrix();
        ofTranslate(x, y);
        masker.begin();
            masker.setUniformTexture("maskTex", mask.getTexture(), 1 );
            ofSetColor(255);
            canvas.draw(0, 0);    
        masker.end(); 
    ofPopMatrix();   
}


void np::AlphaMasker::draw( int x, int y, int w, int h ) {
    ofPushMatrix();
        ofTranslate(x, y);
        masker.begin();
            masker.setUniformTexture("maskTex", mask.getTexture(), 1 );
            ofSetColor(255);
            canvas.draw(0, 0, w, h);    
        masker.end(); 
    ofPopMatrix();   
}


void np::AlphaMasker::maskAndDraw( ofFbo & mask, ofFbo & canvas, int x, int y ) {
    ofPushMatrix();
        ofTranslate(x, y);
        masker.begin();
            masker.setUniformTexture("maskTex", mask.getTexture(), 1 );
            ofSetColor(255);
            canvas.draw(0, 0);    
        masker.end(); 
    ofPopMatrix(); 
}


void np::AlphaMasker::maskFromContours( const std::vector<ofPolyline> & contours ) {
    mask.begin();
        ofClear(0, 0, 0, 0);
        ofFill();                
        ofSetColor( 255 );
        for( auto & cont : contours){
            ofBeginShape();
                auto & vertices =  cont.getVertices();
                for ( size_t i=0; i<vertices.size(); ++i ){
                    ofVertex( vertices[i].x, vertices[i].y );
                }
            ofEndShape();
        }        
    mask.end();
}

    
string np::AlphaMasker::vertexShader() {
    string out = 
#ifdef TARGET_OPENGLES
// ------------------------ GLES2 VERTEX SHADERS CODE -------------------------
STRINGIFY_ALPHAMASK(
    // these are for the programmable pipeline system
    uniform mat4 modelViewProjectionMatrix;

    attribute vec4 position;
    attribute vec2 texcoord;

    varying vec2 texCoordVarying;

    void main()
    {
        texCoordVarying = texcoord;
        gl_Position = modelViewProjectionMatrix * position;
    }
);
// ----------------------------------------------------------------------------
#else
// ------------------------ GL2 VERTEX SHADERS CODE ---------------------------
string("#version 120\n") + 
STRINGIFY_ALPHAMASK(
    varying vec2 texCoordVarying;

    void main()
    {
        texCoordVarying = gl_MultiTexCoord0.xy;
        gl_Position = ftransform();
    }
);
// ----------------------------------------------------------------------------
#endif
    return out;
}

string np::AlphaMasker::fragmentShader() {
    string out = 
#ifdef TARGET_OPENGLES
// ------------------------ GLES2 FRAGMENT SHADERS CODE -----------------------
STRINGIFY_ALPHAMASK(
    precision highp float;

    uniform sampler2D tex0;
    uniform sampler2D maskTex;

    varying vec2 texCoordVarying;

    void main()
    {
        vec3 src = texture2D(tex0, texCoordVarying).rgb;
        float mask = texture2D(maskTex, texCoordVarying).r;
        gl_FragColor = vec4(src , mask);
    }
);    
// ----------------------------------------------------------------------------
#else    
// ------------------------ GL2 FRAGMENT SHADERS CODE -------------------------
string("#version 120\n") + 
STRINGIFY_ALPHAMASK(
    uniform sampler2DRect tex0;
    uniform sampler2DRect maskTex;

    varying vec2 texCoordVarying;

    void main()
    {
        // Get color value from
        vec3 src = texture2DRect(tex0, texCoordVarying).rgb;

        // Get alpha value
        float mask = texture2DRect(maskTex, texCoordVarying).r;

        // Set
        gl_FragColor = vec4(src , mask);
    }
);
// ----------------------------------------------------------------------------
#endif
    return out;
}
    

