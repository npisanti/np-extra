
#include "Scenes.h"

// ---------------- np::TransitionCursor ----------------------------

np::TransitionCursor::TransitionCursor(){
	parameters.setName("transition");
    parameters.add( min.set("time (min)", 0, 0, 60) );
	parameters.add( sec.set("time (sec)", 0, 0, 60) );
	parameters.add( ms.set("time (ms)", 500, 0, 1000) );
	parameters.add( exp.set("exponential", 1, 1, 4) ); // add more easing modes
	bTransitioning = false;
	phase = 0.0f;
}

void np::TransitionCursor::begin() {
    if( ! (min==0 && sec==0 && ms==0) ){
        bTransitioning = true;
        phase = 0.0f;
        start = std::chrono::high_resolution_clock::now();        
    }else{
        phase = 1.0f;
    }
}

bool np::TransitionCursor::update() {
    
    if(phase==1.0f){ // so that will transition up to 1.0f before stopping
        bTransitioning = false;
    }
    
	if(bTransitioning ){
		auto now = std::chrono::high_resolution_clock::now();
		auto elapsed = now - start;
		phase = std::chrono::duration_cast<chrono::milliseconds>(elapsed).count() / ( double ) ( ( min*60 + sec )*1000 + ms);
		
		if(phase>=1.0f){
			phase = 1.0f;
		}			
	}
	return bTransitioning;
}

float np::TransitionCursor::cursor() const {
	
    float multiplied = phase;
    
    for( int i=1; i<exp; ++i ){
        multiplied *= multiplied;
    }

	return multiplied;
}

bool np::TransitionCursor::isTransitioning( ) {
	return bTransitioning;
}

void np::TransitionCursor::kill() {
	phase = 1.0f;
	bTransitioning = false;
}

void np::TransitionCursor::stop(){
	phase = 0.0f;
	bTransitioning = false;
}

ofParameterGroup & np::TransitionCursor::label( std::string name ){
    parameters.setName( name );
    return parameters;
}



// ---------------- np::Scene ---------------------------------------

np::Scene::Scene(){
    transitions.setName( "transitions");
    transitions.add( beginningCursor.label("beginning") );
    transitions.add( endingCursor.label("ending") );
    alpha.set("alpha", 255, 0, 255);
}

void np::Scene::start(){
	beginningCursor.begin();
	state = Beginning;
	onStart();
}

void np::Scene::shutdown(){
	endingCursor.begin();
	state = Ending;
	onShutdown();
}

void np::Scene::updateCursors(){
    
    beginningCursor.update();
    endingCursor.update();
	
	if( state==Beginning && !beginningCursor.isTransitioning()){
        state = Loop;
        onLoop();
    } 
	
	if( state==Ending && !endingCursor.isTransitioning()){
		state = Ended;
		onEnd();
	} 
}

void np::Scene::update( ofFbo & fbo ){
    updateCursors();
    if( state!=Ended ) loop( fbo );
}

void np::Scene::update(){
    updateCursors();
    if( state!=Ended ) loop();
}



// ---------------- np::SceneManager -----------------------------

np::SceneManager::SceneManager(){
    width = 0;
    height = 0;
    modes.reserve(10);
    modes.clear();
    modes.push_back( nullptr );
    mode = 0;
}

void np::SceneManager::setup( int w, int h, bool useFbo ){
    
    bUseFbo = useFbo;
    width = w;
    height = h;
    
    if( bUseFbo ){
        fbos.resize(2);
        for( auto & fbo : fbos ){
            fbo.allocate( w, h );
            fbo.begin();
                ofClear( 0, 0, 0, 0 );
            fbo.end();
        }        
    }

    current = 0;
    old = 0;
    currentFbo = false;
    
    
    int prio = 0; // OF_EVENT_PRIORITY_BEFORE_APP
    ofAddListener( ofEvents().keyPressed, this, &np::SceneManager::onKey, prio );
    
}

void np::SceneManager::add( Scene* scenePointer ){
    scenes.push_back( scenePointer );
}

void np::SceneManager::set( int i ){
    
    while( i<0 ){ 
        i += scenes.size(); 
    }
    
    while( i >= int(scenes.size()) ){ 
        i -= scenes.size(); 
    }
        
    if( bUseFbo ){
        currentFbo = !currentFbo;

        fbos[currentFbo].begin();
            ofClear( 0, 0, 0, 0 );
        fbos[currentFbo].end();
        
        old = current;
        current = i;        
    }

    if( scenes[old] != nullptr ){
        scenes[old]->shutdown();
    }        

    if( scenes[current] != nullptr ){
        scenes[current]->start();
    }        
}

void np::SceneManager::next(){
    set( current+1 );
}
    
void np::SceneManager::prev(){
    set( current-1 );
}

void np::SceneManager::addMode( Mode* modePointer ){
    modes.push_back( modePointer );
}

void np::SceneManager::setMode( int i ){
    if( i<0 ){
        i=0; 
        ofLogError()<< "[np::SceneManager] mode index less than 0, setting to default (0).";
    }else if( i>=int(modes.size()) ){
        ofLogError()<< "[np::SceneManager] mode index greater than max, ignoring.";
    }else{
        mode = i;
    }
}

void np::SceneManager::nextMode(){
    mode++;
    if( mode>=int(modes.size()) ){
        mode = 0;
    }
}

void np::SceneManager::prevMode(){
    mode--;
    if( mode<0 ){
        mode = modes.size()-1;
    }
}

void np::SceneManager::update(){
    if( bUseFbo ){
        if( scenes[old] != nullptr ){
            scenes[old]->update( fbos[!currentFbo] );
        }        
        if( scenes[current] != nullptr ){
            scenes[current]->update( fbos[currentFbo] );
        }            
    }else{
        if( scenes[old] != nullptr ){
            scenes[old]->update();
        }        
        if( scenes[current] != nullptr ){
            scenes[current]->update();
        }          
    }
}

void np::SceneManager::draw(){
    if( bUseFbo ){
        if( scenes[old] != nullptr ){
            ofSetColor( 255, scenes[old]->alpha );
            fbos[!currentFbo].draw(0, 0);
        }        
        if( scenes[current] != nullptr ){
            ofSetColor( 255, scenes[current]->alpha );
            fbos[currentFbo].draw( 0, 0 );
        }          
    }
}

void np::SceneManager::draw( int x, int y, int w, int h, bool frame  ){
    if( bUseFbo ){
        if( scenes[old] != nullptr ){
            ofSetColor( 255, scenes[old]->alpha );
            fbos[!currentFbo].draw( x, y, w, h );
        }        
        if( scenes[current] != nullptr ){
            ofSetColor( 255, scenes[current]->alpha );
            fbos[currentFbo].draw( x, y, w, h );
        }  
        
        if( frame ){        
            ofPushStyle();
                ofSetColor( 255 );
                ofNoFill();
                ofDrawRectangle( x, y, w, h );
            ofPopStyle();
        }        
    }
}

void np::SceneManager::draw( int x, int y, float scale, bool frame ){
    if( bUseFbo ){
        if( scenes[old] != nullptr && scenes[old]->running() ){
            ofSetColor( 255, scenes[old]->alpha );
            fbos[!currentFbo].draw( x, y, fbos[!currentFbo].getWidth()*scale, fbos[!currentFbo].getHeight()*scale );
        }        
        if( scenes[current] != nullptr && scenes[current]->running()  ){
            ofSetColor( 255, scenes[current]->alpha );
            fbos[currentFbo].draw( x, y, fbos[currentFbo].getWidth()*scale, fbos[currentFbo].getHeight()*scale );
        }  
        if( frame ){        
            ofPushStyle();
                ofSetColor( 255 );
                ofNoFill();
                ofDrawRectangle( x, y, fbos[currentFbo].getWidth()*scale, fbos[currentFbo].getHeight()*scale );
            ofPopStyle();
        }        
    }
}

void np::SceneManager::draw( int x, int y ){
    if( bUseFbo ){
        if( scenes[old] != nullptr && scenes[old]->running() ){
            ofSetColor( 255, scenes[old]->alpha );
            fbos[!currentFbo].draw( x, y );
        }
        if( scenes[current] != nullptr && scenes[current]->running()  ){
            ofSetColor( 255, scenes[current]->alpha );
            fbos[currentFbo].draw( x, y );
        }
    }
}


void np::SceneManager::drawInterface(){
    if( modes[mode] == nullptr ){
        float x = 0.0f; 
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
        
        if( bUseFbo ){
            width = fbos[0].getWidth();
            height = fbos[0].getHeight();    
        }
        if( scenes[current] != nullptr ){
            scenes[current]->drawInterface( x, y, width, height );
        }
        if( bUseFbo ){
            draw( x, y, width, height, true );
        }
    }else{
        modes[mode]->draw();
    }
}

void np::SceneManager::onKey( ofKeyEventArgs & args ){
    switch ( args.type ){
        case ofKeyEventArgs::Pressed : 
            if( modes[mode] == nullptr ){
                if( scenes[current] != nullptr ){
                    scenes[current]->keyPressed( args.key );
                }          
            }else{
                modes[mode]->keyPressed( args.key );
            }
        
        
        break;
        
        case ofKeyEventArgs::Released : 
            if( modes[mode] != nullptr ){
                modes[mode]->keyReleased( args.key );
            }
        break;
        
        default: break;
    }
}

void np::SceneManager::onMouse( ofMouseEventArgs & args ){
    switch ( args.type ){
        case ofMouseEventArgs::Pressed : 
            if( modes[mode]!= nullptr ){
                modes[mode]->mousePressed( args.x, args.y, args.button );
            }
        break;      
          
        case ofMouseEventArgs::Dragged : 
            if( modes[mode]!= nullptr ){
                modes[mode]->mouseDragged( args.x, args.y, args.button );
            }
        break;      
        
        case ofMouseEventArgs::Released : 
            if( modes[mode]!= nullptr ){
                modes[mode]->mouseReleased( args.x, args.y, args.button );
            }
        break;      
        default: break;
    }
}
