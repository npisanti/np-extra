
#pragma once

#include "ofMain.h"


namespace np {

// ---------------------- np::Modulator -----------------------------
class Modulator {

public:	

	Modulator();
	
	ofParameterGroup & link( ofParameter<float> & parameter, std::string name );
	ofParameterGroup & link( ofParameter<int>   & parameter, std::string name );
	ofParameterGroup & link( ofParameter<float> & parameter );
	ofParameterGroup & link( ofParameter<int>   & parameter );
    
	void modulate( float value );

	bool isFloat(){ return (mode==1); }
	bool isInt(){ return (mode==0); }
	
	ofParameterGroup parameters;

	ofParameter<bool>	bActive;

    ofParameterGroup & label( std::string name );
	
private:
    ofParameter<float>      tMin;
    ofParameter<float>      tMax;
	ofParameter<float> 		fMin;
	ofParameter<float> 		fMax;
	ofParameter<int> 		iMin;
	ofParameter<int> 		iMax;

    ofParameter<float> * fdest;
    ofParameter<int> *	 idest;

    int mode;
};


// ---------------------- np::ModMatrix -----------------------------
class ModMatrix{

public:
    
    void setup( int slotnum, std::string name = "modulation matrix" );

    void addSource( const float & source, std::string name );
    void addDestination( ofParameter<float> & param, std::string name );
    void addDestination( ofParameter<int> & param, std::string name );
    void addDestination( ofParameter<float> & param );
    void addDestination( ofParameter<int> & param );
    
    void update();

    ofParameterGroup & label( std::string name );

    ofParameterGroup parameters;

    
private:
    struct Slot{
        ofParameterGroup parameters;
            ofParameter<bool> bActive;
            ofParameter<int> source;
            ofParameter<std::string> sourceLabel;
            ofParameter<int> destination;
            ofParameter<std::string> destinationLabel;
            ofParameter<float> tMin;
            ofParameter<float> tMax;
            ofParameter<float> dMin;
            ofParameter<float> dMax;
    };

    struct Source{
        const float * source;
        std::string label;
    };

    class Destination{
    public:
        Destination();
        void link( ofParameter<float> & param );
        void link( ofParameter<int> & param );
        void set( float & value );
        
        float getMin() const;
        float getMax() const;
       
        std::string label;
    private:
        int mode;
        ofParameter<float> * fDest;
        ofParameter<int> * iDest;
    };

    std::vector<Slot> slots;
    std::vector<Source> sources;
    std::vector<Destination> destinations;
    
    
    void onSourceChange( int & value );
    void onDestinationChange( int & value );
    
};
    
};
