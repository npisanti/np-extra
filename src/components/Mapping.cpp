
#include "Mapping.h"

void np::Mapping::setup( int pw, int ph, float mouseScale ){

    fbo.allocate( pw, ph );
    fbo.begin();
        ofClear( 0, 0, 0, 0 );
    fbo.end();

    this->mouseScale = mouseScale;

    mapping.reserve(128);
    mapping.clear();
    max = 0;

    bLight = false;
    bFill = false;
    bShowHelp = true;

    // priority should be post app for this to work
    ofAddListener( ofEvents().keyPressed, this, &Mapping::keyPressed );
    ofAddListener( ofEvents().mousePressed, this, &Mapping::mousePressed );

    loadMapping();

}


void np::Mapping::draw( float scale ){

    currentFrame = ofGetFrameNum();

    cursor.x = ofGetMouseX() / mouseScale;
    cursor.y = ofGetMouseY() / mouseScale;

    ofPushMatrix();

    if(scale !=1.0f) { ofScale( scale, scale ); }

    ofPushStyle();
    ofSetLineWidth(1.5f);

    if(bLight){
        ofFill();
        ofSetColor( 150 );
        ofDrawCircle( cursor.x, cursor.y, 100 );
    }

    if( !mapping.empty() ){

        if( bFill ){
            ofFill();
        } else {
            ofNoFill();
        }

        for( int k=0; k<int(mapping.size())-1; ++k){
            //auto & vertices =  mapping[k].getVertices();
            const std::vector<glm::vec3> & vertices =  mapping[k].getVertices();
            if(vertices.size()>0){
                ofSetColor(255);
                ofBeginShape();
                    for ( size_t i=0; i<vertices.size(); ++i ){
                        ofVertex( vertices[i].x, vertices[i].y );
                    }
                ofEndShape();
            }
            const auto & center = mapping[k].getCentroid2D();
            if( bFill ){
                ofSetColor(0);
            }else{
                ofSetColor(255);
            }
            ofDrawBitmapString( ofToString(k), center.x, center.y );
        }


        ofNoFill();
        auto & vertices =  mapping.back().getVertices();
        if(max>0){
            ofSetColor(255);
            ofBeginShape();
                for ( size_t i=0; i<max; ++i ){
                    ofVertex( vertices[i].x, vertices[i].y );
                }
            ofEndShape();

            ofSetColor( 255, 0, 0 );
            for ( size_t i=0; i<max; ++i ){
                ofDrawCircle( vertices[i].x, vertices[i].y, 5 );
            }
        }

    }


    static const int cdim = 10;
    ofSetColor(255);
    ofDrawLine( cursor.x-cdim, cursor.y, cursor.x+cdim, cursor.y );
    ofDrawLine( cursor.x, cursor.y-cdim, cursor.x, cursor.y+cdim );

    ofPopStyle();
    ofPopMatrix();

    if( bShowHelp ){ drawHelp(); }
}


void np::Mapping::drawHelp(){

    ofSetColor(255);

    if(bShowHelp){
        std::string info = "HELP, press h to hide\n";

        info += "z = undo point\n";
        info += "x = redo point\n";
        info += "c = close shape\n";
        info += "s = save\n";
        info += "l = load\n";
        info += "SPACEBAR = add polyline\n";
        info += "BACKSPACE = remove polyline\n";
        info += "t = spotlight\n";
        info += "f = fill lines\n";
        info += "F6 = switch to warping";
        info += "\n";

        ofSetColor(255);
        ofDrawBitmapString( info, ofGetWidth()-200, 20);
    }

}

void np::Mapping::renderMask( ofFbo & mask ){
    mask.begin();
        ofClear( 0, 0, 0, 0 );
        ofFill();
        ofSetColor(255);
        for( int k=0; k<int(mapping.size()); ++k){
            const std::vector<glm::vec3> & vertices =  mapping[k].getVertices();
            if(vertices.size()>0){
                ofSetColor(255);
                ofBeginShape();
                    for ( size_t i=0; i<vertices.size(); ++i ){
                        ofVertex( vertices[i].x, vertices[i].y );
                    }
                ofEndShape();
            }
        }
    mask.end();
}

void np::Mapping::keyPressed( ofKeyEventArgs& eventArgs ) {

    if( ofGetFrameNum() - currentFrame < 2 ){

        const int & key = eventArgs.key;

        switch(key){
            case 'h': bShowHelp = !bShowHelp; break;

            case ' ':
                while( max < mapping.back().size() ){
                    auto & vertices = mapping.back().getVertices();
                    vertices.pop_back();
                }
                mapping.emplace_back();
                max = 0;
            break;

            case OF_KEY_BACKSPACE:
                if( mapping.size()>1 ){
                    mapping.pop_back();
                    max = mapping.back().getVertices().size();
                }else if( mapping.size()>0 ){
                    mapping.pop_back();
                    max = 0;
                }
            break;

            case 'c':
            {
                auto & vertices =  mapping.back().getVertices();
                if(!vertices.empty())vertexToCurrent( vertices.front().x, vertices.front().y );
            }
            break;

            case 'z':
            {
                if( max > 0 ) max--;
            }
            break;

            case 'x':
            {
                if( mapping.size()>0 ){
                    auto & vertices = mapping.back().getVertices();
                    if( max < vertices.size() ) max++;
                }
            }
            break;

            case 's':
                saveMapping();
            break;

            case 'l':
                loadMapping();
            break;

            case 't': bLight = !bLight; break;
            case 'f': bFill = !bFill; break;

        }

    }

}

void np::Mapping::mousePressed( ofMouseEventArgs& eventArgs ) {
    if( ofGetFrameNum() - currentFrame < 2 ){
        const int & x = eventArgs.x / mouseScale;
        const int & y = eventArgs.y / mouseScale;
        vertexToCurrent( x, y );
    }
}

void np::Mapping::vertexToCurrent( int x, int y){
    if(mapping.size()==0){
		mapping.emplace_back();
		max = 0;
	}

	auto & vertices = mapping.back().getVertices();
	while( vertices.size() > max ){
		vertices.pop_back();
	}

	mapping.back().addVertex( x, y );
	max++;
}

void np::Mapping::saveMapping(){
    cout<<"saving lines to mapping.xml\n";

    ofXml xml;
    ofXml root = xml.appendChild("mapping");

    if( ! mapping.empty() ){

        for ( size_t i=0; i<mapping.size(); ++i ){
            auto & vertices =  mapping[i].getVertices();

            if(!vertices.empty()){
                ofXml line = root.appendChild("line");
                for( size_t k=0; k<vertices.size(); ++k ){
                    auto pt = line.appendChild("pt");
                    pt.setAttribute("x", vertices[k].x );
                    pt.setAttribute("y", vertices[k].y );
                    pt.setAttribute("z", vertices[k].z );
                }
            }
        }
    }


    if( !xml.save( "mapping.xml" ) ){
        ofLogError()<< "error saving serialized points";
    }
}

void np::Mapping::loadMapping(){
    cout<<"loading mapping polylines...\n";

    ofXml xml;

    if( xml.load( "mapping.xml" ) )  {

        auto root = xml.getChild("mapping");

        if( root ){

            mapping.clear();

            auto xmlLines = root.getChildren("line");

            for( auto & line : xmlLines ){
                mapping.emplace_back();

                auto pts = line.getChildren("pt");
                for(auto & pt: pts){
                    auto x = pt.getAttribute("x").getFloatValue();
                    auto y = pt.getAttribute("y").getFloatValue();
                    auto z = pt.getAttribute("z").getFloatValue();
                    mapping.back().addVertex( x, y, z );
                }
            }

        }else{
            ofLogError( "error while loading points from xml, no points tag found" );
        }
	}else{
        ofLogError( "error loading xml file" );
    }

    max = mapping.back().size();
}
