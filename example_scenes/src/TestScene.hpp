
#pragma once

#include "components/Scenes.h"
#include "resources.h"

class TestScene : public np::Scene {

public:
    ofColor color;
    ofRectangle position;

    void setup(){
        color = ofColor( ofRandom(255.0f), ofRandom(255.0f), ofRandom(255.0f) );
    }

	void onStart() override {
        position.width = ofRandom( resources::width * 0.25 );
        position.height = ofRandom( resources::height * 0.25 );
        position.x = ofRandom( resources::width - position.width );
        position.y = ofRandom( resources::height - position.height );
    };

	void loop( ofFbo & fbo ) override {
        alpha = cursor()*255.0f;

        fbo.begin();
            ofClear( 0, 0, 0, 0 );
            ofSetColor( color );
            ofDrawRectangle( position );
        fbo.end();
    }

};
