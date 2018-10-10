
#include "AlphaMasker.h"

int np::AlphaMasker::constructed = 0;

ofShader np::AlphaMasker::shader = ofShader();

const std::string np::AlphaMasker::vertex = ALPHAMASKSHADERSOURCE(

#ifdef GL_ES
    precision mediump float;
#endif

#ifdef __ARM_ARCH

    attribute vec4 position;
    attribute vec2 texcoord;
    uniform mat4 modelViewProjectionMatrix;
    varying vec2 texcoord0;
    varying vec2 st;

    void main(void){
        gl_Position = modelViewProjectionMatrix * position;
        texcoord0 = texcoord;
        st = texcoord0/u_resolution.xy;
    }

#else

    varying vec2 texcoord0;
    uniform vec2 u_resolution;
    varying vec2 st;

    void main(void){
        texcoord0 = gl_Vertex.xy;
        st = texcoord0/u_resolution.xy;
        gl_Position = ftransform();
    }

#endif

); //ALPHAMASKSHADERSOURCE end

const std::string np::AlphaMasker::fragment = ALPHAMASKSHADERSOURCE(

    #ifdef GL_ES
    precision mediump float;
    #endif

    uniform vec2 u_resolution;
    uniform sampler2D u_tex0;
    uniform sampler2D u_tex1;
    uniform int u_channel;
    varying vec2 st;

    void main (void) {
        vec4 source = texture2D( u_tex0, st );
        vec4 mask = texture2D( u_tex1, st );
        gl_FragColor = vec4( source.rgb, mask[u_channel] * source.a );
    }

); //ALPHAMASKSHADERSOURCE end

void np::AlphaMasker::setup(){
    if(constructed==0){
        ofDisableArbTex();
        ofLogNotice()<<"[np::AlphaMasker] disabling ARB textures for shader\n";
        shader.setupShaderFromSource( GL_VERTEX_SHADER, vertex );
        shader.setupShaderFromSource( GL_FRAGMENT_SHADER, fragment );
        shader.bindDefaults();
        shader.linkProgram();
    }
    constructed++;
}

void np::AlphaMasker::draw( const ofTexture & source, const ofTexture & mask, int maskChannel ) {
    shader.begin();
    shader.setUniform2f( "u_resolution", source.getWidth(), source.getHeight()  );
    shader.setUniform1i( "u_channel", maskChannel );
    shader.setUniformTexture("u_tex0", source, source.getTextureData().textureID );
    shader.setUniformTexture("u_tex1", mask, mask.getTextureData().textureID );
    ofPushStyle();
        ofFill();
        ofSetColor(255);
        ofDrawRectangle(0, 0, source.getWidth(), source.getHeight() );
    ofPopStyle();
    shader.end();
}

void np::AlphaMasker::draw( const ofTexture & source, const ofTexture & mask, float x, float y, float scale, int maskChannel ) {
    ofPushMatrix();
        ofTranslate( x, y );
        if( scale!=1.0f){ ofScale( scale, scale ); }
        draw( source, mask, maskChannel );
    ofPopMatrix();
}
