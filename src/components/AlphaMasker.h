
#pragma once
#include "ofMain.h"

#ifndef ALPHAMASKSHADERSOURCE
#define ALPHAMASKSHADERSOURCE(...) ALPHAMASKSHADERSOURCE_AUX(__VA_ARGS__)
#define ALPHAMASKSHADERSOURCE_AUX(...) #__VA_ARGS__
#endif

#ifdef __ARM_ARCH
    #ifndef GL_ES
        #define GL_ES
    #endif
#endif

namespace np {

class AlphaMasker {

public: // --------------- PUBLIC API ------------------------------------------
    struct Mode{
        static const int Fbo = 0;
        static const int FboAndMask = 1;
        static const int All = 2;
    };

    // with internal canvas, mask and fbo
    void setup( int w, int h, int multisample=1, int mode=2 );
    void update(); // draws to fbo with canvas as source and internal mask as mask
    void update( const ofTexture & source ); // draws to fbo with internal mask as mask
    void update( const ofTexture & source, const ofTexture & mask ); // draws to fbo

    ofFbo canvas; // this is the source
    ofFbo mask; // this is the mask
    ofFbo fbo; // update() renders to this fbo

    // draws internal fbo
    void draw( float x=0.0f, float y=0.0f ){ fbo.draw(x, y); }
    void draw( float x, float y, float w, float h ){ fbo.draw(x, y, w, h); }


    // static functions, use np::masker wrapper for this, see down -------------
    static void init();
    static void draw( const ofTexture & source, const ofTexture & mask, int maskChannel=0 );
    static void draw( const ofTexture & source, const ofTexture & mask, float x, float y, float scale=1.0f, int maskChannel=0 );

private:
    static ofShader        shader;
    static const std::string vertex;
    static const std::string fragment;

    static bool initialized;
};

} // end namespaces


// ----------------------- STATIC API ------------------------------------------
namespace np{
    namespace masker{
        inline void init(){ AlphaMasker::init(); }
        inline void draw( const ofTexture & source, const ofTexture & mask, int maskChannel=0 ){
            AlphaMasker::draw(source, mask, maskChannel);
        }
        inline void draw( const ofTexture & source, const ofTexture & mask, float x, float y, float scale=1.0f, int maskChannel=0 ){
            AlphaMasker::draw(source, mask, x, y, scale, maskChannel);
        }
    }
}
