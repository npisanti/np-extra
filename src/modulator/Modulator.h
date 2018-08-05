
#pragma once

#include "ofMain.h"


namespace np {

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
	
};
