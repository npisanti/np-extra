#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofEnableAntiAliasing();
    bAntiAliasing = true;
    
    lines.reserve(128);
	lines.clear();
    max = 0;
    	
    bLight = false;
    bFill = false;
    bShowHelp = true;

    
    ofSetWindowTitle( "polylines<-->xml / mapping tool" );
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);

    if(bLight){
        ofFill();
        ofSetColor( 150 );
        ofDrawCircle( ofGetMouseX(), ofGetMouseY(), 100 );
    }

	if( bFill ){
		ofFill();
	} else {
		ofNoFill();
	}
	
	if( lines.size()>0 ){
		for( size_t k=0; k<lines.size()-1; ++k){
			//auto & vertices =  lines[k].getVertices();
			const std::vector<glm::vec3> & vertices =  lines[k].getVertices();
			if(vertices.size()>0){
				ofSetColor(255);
				ofBeginShape();
					for ( size_t i=0; i<vertices.size(); ++i ){
						ofVertex( vertices[i].x, vertices[i].y );
					}
				ofEndShape();
			}
		}
    }
    
    ofNoFill();
    if( lines.size()>0 ) {
		auto & vertices =  lines.back().getVertices();
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
    
    if(bShowHelp){
        ofSetColor(255);
        string info = "HELP, press h to hide\n";
        info += "z = undo point\n";
        info += "x = redo point\n";
        info += "c = close shape\n";
        info += "s = save\n";
        info += "l = load\n";
        info += "SPACEBAR = add polyline\n";
        info += "BACKSPACE = remove polyline\n";
        info += "t = spotlight\n";
        info += "f = fill lines\n";
        info += "a = antialiasing=";
        if( bAntiAliasing ){ info+="true\n"; }else{ info+="false\n"; }
        
        ofDrawBitmapString(info, ofGetWidth()-200, 20);
    }

}

//--------------------------------------------------------------
void ofApp::exit(){

}

void ofApp::vertexToCurrent( int x, int y) {
	if(lines.size()==0){ 
		lines.emplace_back(); 
		max = 0;
	}
	
	auto & vertices = lines.back().getVertices();
	while( vertices.size() > max ){
		vertices.pop_back();
	}
	
	lines.back().addVertex( x, y );
	max++;
}

void ofApp::mousePressed(int x, int y, int button){
	vertexToCurrent( x, y );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch( key ){
    
        case 'h': bShowHelp = !bShowHelp; break;
        
        case ' ':
            lines.emplace_back();
            max = 0;
        break;
        
        case OF_KEY_BACKSPACE:
			if( lines.size()>1 ){
				lines.pop_back();
				max = lines.back().getVertices().size();
			}else if( lines.size()>0 ){
				lines.pop_back();
				max = 0;
			}
        break;
    
        case 'c': 
        {
            auto & vertices =  lines.back().getVertices();
            vertexToCurrent( vertices.front().x, vertices.front().y );
        }
        break;
        
        case 'z': 
        {
			if( max > 0 ) max--;
        }
        break;
        
        case 'x': 
        {
			if( lines.size()>0 ){
				auto & vertices = lines.back().getVertices();
				if( max < vertices.size() ) max++;
			}
        }
        break;
        
        case 's': 
			cout<<"saving lines to mapping.xml\n";
            np::serialize_polylines( "mapping.xml", lines ); 
        break;
        
        case 'l': 
			cout<<"loading lines...\n";
            np::deserialize_polylines( "mapping.xml", lines ); 
            lines.emplace_back();
            max = 0;
        break;
        
        case 't': bLight = !bLight; break;
        case 'f': bFill = !bFill; break;
        
        case 'a':
			if( bAntiAliasing ){
				ofDisableAntiAliasing();
				bAntiAliasing = false;
			}else{
				ofEnableAntiAliasing();
				bAntiAliasing = true;
			}
		break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}

void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------
