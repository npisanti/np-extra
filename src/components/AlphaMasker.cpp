
#include "AlphaMasker.h"

bool np::AlphaMasker::initialized = false;

ofShader np::AlphaMasker::shader = ofShader();

#ifdef __ARM_ARCH

const std::string np::AlphaMasker::vertex = ALPHAMASKSHADERSOURCE(
    attribute vec4 position;
    attribute vec4 color;
    attribute vec4 normal;
    attribute vec2 texcoord;

    uniform mat4 modelViewMatrix;
    uniform mat4 projectionMatrix;
    uniform sampler2D maskTex;

    varying vec4 colorVarying;
    varying vec2 texCoordVarying;

    void main(){
        
        //get our current vertex position so we can modify it
        vec4 pos = projectionMatrix * modelViewMatrix * position;
        
        gl_Position = pos;
        colorVarying = color;
        texCoordVarying = texcoord;
    }
); //ALPHAMASKSHADERSOURCE end

const std::string np::AlphaMasker::fragment = ALPHAMASKSHADERSOURCE(
    precision mediump float;

    uniform sampler2D tex0;
    uniform sampler2D maskTex;
    uniform vec4 globalColor;

    varying vec2 texCoordVarying;

    void main (void)
    {
        vec2 pos = texCoordVarying;
        vec3 src = texture2D(tex0, pos).rgb;
        float mask = texture2D(maskTex, pos).r;
        gl_FragColor = vec4( src , mask);
    }
); //ALPHAMASKSHADERSOURCE end

#else

const std::string np::AlphaMasker::fragment = "#version 120\n \
		#extension GL_ARB_texture_rectangle : enable\n \
		\
		uniform sampler2DRect tex0;\
		uniform sampler2DRect maskTex;\
		\
		void main (void){\
		vec2 pos = gl_TexCoord[0].st;\
		\
		vec3 src = texture2DRect(tex0, pos).rgb;\
		float mask = texture2DRect(maskTex, pos).r;\
		\
		gl_FragColor = vec4( src , mask);\
		}";

#endif

void np::AlphaMasker::init(){
    if( ! initialized ){
        ofDisableArbTex();
        ofLogNotice()<<"[np::AlphaMasker] disabling ARB textures for shader\n";
        #ifdef __ARM_ARCH
            shader.setupShaderFromSource( GL_VERTEX_SHADER, vertex );
        #endif
        
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
        shader.bindDefaults();
        shader.linkProgram();
        initialized = true;
    }
}

void np::AlphaMasker::draw( const ofFbo & source, const ofFbo & mask ) {
    if( initialized ){
        shader.begin();
        shader.setUniformTexture("maskTex", mask.getTexture(), 1 );
        //ofSetColor(255);
        source.draw( 0, 0 );
        shader.end();
    }else{
        ofLogError()<<"[np::AlphaMasker] not initialized! call setup() or np::masker::init() before use";
    }
}


void np::AlphaMasker::begin( const ofFbo & mask ) {
    if( initialized ){
        shader.begin();
        shader.setUniformTexture("maskTex", mask.getTexture(), 1 );
    }else{
        ofLogError()<<"[np::AlphaMasker] not initialized! call setup() or np::masker::init() before use";
    }
}

void np::AlphaMasker::end() {
    if( initialized ){
        shader.end();
    }else{
        ofLogError()<<"[np::AlphaMasker] not initialized! call setup() or np::masker::init() before use";
    }
}

void np::AlphaMasker::setup( int w, int h, int multisample, int mode ){
    switch(mode){
        case 2: canvas.allocate(w, h, GL_RGBA, multisample );
        case 1: mask.allocate(w, h, GL_RGBA, multisample );
        case 0: fbo.allocate(w, h, GL_RGBA, multisample );
        break;
    }
    init();
}

void np::AlphaMasker::update(){
    fbo.begin();
        ofClear( 0, 0, 0, 0 );
        draw( canvas, mask );
    fbo.end();
}

void np::AlphaMasker::update( const ofFbo & source ){
    fbo.begin();
        ofClear( 0, 0, 0, 0 );
        draw( source, mask );
    fbo.end();
}

void np::AlphaMasker::update( const ofFbo & source, const ofFbo & mask ){
    fbo.begin();
        ofClear( 0, 0, 0, 0 );
        draw( source, mask );
    fbo.end();
}
