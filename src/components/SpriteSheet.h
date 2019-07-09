
#pragma once

#include <iostream>
#include "ofMain.h"

namespace np{

class SpriteSheet {
public:

    SpriteSheet();

    bool load( std::string path, int spriteWidth, int spriteHeight, int mode );
    
    void draw(float x=0, float y=0);

    void bind();
    void unbind();
    
    void setFrame( int index );
    void setPlayhead( double pct );
    
    int getWidth() const { return sw; }
    int getHeight() const { return sh; }
    
private:
    std::string name;

    int sw;
    int sh;
    glm::vec2 offset;

    bool bInitialized;
    
    ofImage png;
    
    int frames;
    int cursor;

    void setupSpriteVbo();
    ofVbo vbo;

    void initVbo();

};

}
