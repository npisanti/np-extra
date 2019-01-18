
#pragma once 

#include "ofMain.h"

namespace np {
	

// ---------------- np::TransitionCursor ----------------------------
class TransitionCursor {
	
public:
	TransitionCursor();

	bool update();	

	bool isTransitioning();

	void begin();	
    void kill();
    void stop();
	
	float cursor() const;

	ofParameterGroup parameters;
        ofParameter<int> min;
        ofParameter<int> exp;
        ofParameter<int> ms;
        ofParameter<int> sec;
        
    ofParameterGroup & label( std::string name );
	
    void zeroTime();
    
private:
	float phase;
	float add;
	bool bTransitioning;
	
	std::chrono::high_resolution_clock::time_point start;
	
};
	

// ---------------- np::Scene ---------------------------------------
class Scene {

public:
    Scene();
	
    // methods to write: --------------------------------------------
	virtual void loop( ofFbo & fbo ){}; // override this if you use fbos
	virtual void loop(){}; // override this if you don't use the fbos in the manager
	
	virtual void onStart(){};       // optional on start
    virtual void onLoop(){};        // optional after the beginning and before loop
	virtual void onShutdown(){}; 	// optional on shutdown
	virtual void onEnd(){}; 	    // optional on end

    virtual void keyPressed( int key ){};
    virtual void keyReleased( int key ){};
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    
    virtual void drawInterface( int x, int y, int w, int h ){};
    
    // to be called inside the scene --------------------------------
    
    // check the transition point	
    inline float cursor() const {
        switch( state ){
            case Beginning : return beginningCursor.cursor(); break;
            case Loop : return 1.0f; break;
            case Ending :  return (1.0f-endingCursor.cursor()); break;
            case Ended: return 0.0f; break;
            default: break;
        }
        return 1.0f;
    }

    inline bool running(){ return (state!=Ended); }
    inline bool isBeginning(){ return state==Beginning; }
    inline bool isLooping(){ return state==Loop; }
    inline bool isEnding(){ return state==Ending; }
    inline bool isEnded() { return state==Ended; }
    
    // to avoid multiple scenes handling the same resources 
    inline bool resourcesAvailable(){ return state<2; } 

    void jump(){ if(state<3) state++; }


	// to be called by the manager ----------------------------------
	void update( ofFbo & fbo ); 
	void update(); 
	void start();
	void shutdown();
	
    ofParameterGroup transitions;
        ofParameter<int> alpha;
    
protected:	
	TransitionCursor beginningCursor;
	TransitionCursor endingCursor;
    
    // states 
    static const int Beginning = 0;
    static const int Loop = 1;
    static const int Ending = 2;
    static const int Ended = 3;

	int 			state;
    
    void updateCursors();

};


// ------------------ np::SceneManager ------------------------------
class SceneManager {
    
public:
    SceneManager();
    void setup( int w, int h, bool useFbo=true );
    void add( Scene* scenePointer );
    
    void set( int i );
    void next();
    void prev();
    
    void update();
    void draw();
    void draw( int x, int y );
    void draw( int x, int y, int w, int h, bool frame=false );
    void draw( int x, int y, float scale, bool frame=false );
    
    void drawSceneInterface();
    void drawSceneInterface( int x, int y, int w, int h );

    void keyPressed( ofKeyEventArgs & args );
    void keyReleased( ofKeyEventArgs & args );
    void mousePressed( ofMouseEventArgs & args );    
    void mouseReleased( ofMouseEventArgs & args );    
    void mouseDragged( ofMouseEventArgs & args );    
    
    int getWidth() const { return width; };
    int getHeight() const { return height; };

private:

    bool bUseFbo;
    std::vector<Scene*> scenes;
   
    int current;
    int old;
    
    bool currentFbo;
    std::vector<ofFbo> fbos;
    int width;
    int height;

};    

}
