
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

public:
    static void setup();
    static void draw( const ofTexture & source, const ofTexture & mask, int maskChannel=0 );
    static void draw( const ofTexture & source, const ofTexture & mask, float x, float y, float scale=1.0f, int maskChannel=0 );

private:
    static ofShader        shader;
    static const std::string vertex;
    static const std::string fragment;

    static int      constructed;
};

} // end namespaces



namespace np{
    namespace masker{
        inline void init(){ AlphaMasker::setup(); }
        inline void draw( const ofTexture & source, const ofTexture & mask, int maskChannel=0 ){
            AlphaMasker::draw(source, mask, maskChannel);
        }
        inline void draw( const ofTexture & source, const ofTexture & mask, float x, float y, float scale=1.0f, int maskChannel=0 ){
            AlphaMasker::draw(source, mask, x, y, scale, maskChannel);
        }
    }
}
