
#include "Modulator.h"

np::Modulator::Modulator(){ 
	mode = -1; 
	parameters.setName("m2 not linked");
	bActive = false;
}

ofParameterGroup & np::Modulator::link( ofParameter<int> & parameter, std::string name ) {
	idest = &parameter;
	mode = 0;
    
    parameters.setName( name );
	parameters.add( bActive.set( "active", false) );
	parameters.add( tMin.set("threshold min", 0.0f, 0.0f, 1.0f ) );
	parameters.add( tMax.set("threshold max", 1.0f, 0.0f, 1.0f ) );
	parameters.add( iMin.set("dest min", parameter.getMin(), parameter.getMin(), parameter.getMax()));
	parameters.add( iMax.set("dest max", parameter.getMax(), parameter.getMin(), parameter.getMax()));

	cout << "linked parameter with name: \""<<parameter.getName()<<"\n";
    return parameters;
}


ofParameterGroup & np::Modulator::link( ofParameter<float> & parameter, std::string name ) {
	fdest = &parameter;
	mode = 1;

    parameters.setName( name );
	parameters.add( bActive.set( "active", false) );
	parameters.add( tMin.set("threshold min", 0.0f, 0.0f, 1.0f ) );
	parameters.add( tMax.set("threshold max", 1.0f, 0.0f, 1.0f ) );
	parameters.add( fMin.set("dest min", parameter.getMin(), parameter.getMin(), parameter.getMax()));
	parameters.add( fMax.set("dest max", parameter.getMax(), parameter.getMin(), parameter.getMax()));

	cout << "linked parameter with name: \""<<parameter.getName()<<"\n";
    return parameters;
}

	
ofParameterGroup & np::Modulator::link( ofParameter<float> & parameter ) {
    return link( parameter, "m2 "+ parameter.getName() );
}
ofParameterGroup & np::Modulator::link( ofParameter<int>   & parameter ){
    return link( parameter, "m2 "+ parameter.getName() );
}

void np::Modulator::modulate( float value ) {	
	if(bActive){
		switch( mode ){
			case 0:
				idest->set( ofMap(value, tMin, tMax, iMin, iMax, true ) );
			break;
			
			case 1:
				fdest->set( ofMap(value, tMin, tMax, fMin, fMax, true ) );
			break;
		}
	}
}


ofParameterGroup & np::Modulator::label( std::string name ){
    parameters.setName( name );
    return parameters;
}
