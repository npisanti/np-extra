
#include "LiveParameters.h"
#include <boost/filesystem.hpp>
#include "ofJson.h"
#include "ofAppRunner.h"

np::LiveParameters::LiveParameters(){
    parameters = nullptr;
}

void np::LiveParameters::watch( ofParameterGroup & parameters, std::string path ){
    
    this->parameters = &parameters;
    
    this->path = path;
    if( ! ofFilePath::isAbsolute( path )){
        path = ofFilePath::getCurrentWorkingDirectory() + "/" + path;
    }

    ofFile file( path );
    if( file.exists() ){
        ofAddListener(ofEvents().update, this, &np::LiveParameters::checkFile);
        writeTimestamp = boost::filesystem::last_write_time( path );    
        reload();
    }else{
        ofLogError() << "[np::LiveParameters] file does not exists, creating with default parameters\n";

        ofJson json;
        ofSerialize( json, parameters );
        ofSavePrettyJson( path, json );        
    }
}

void np::LiveParameters::checkFile(ofEventArgs &args){
    timePassed += ofGetLastFrameTime();
    if( timePassed > interval ){
        time_t checkTimestamp = boost::filesystem::last_write_time( path );
        if( checkTimestamp != writeTimestamp){
            writeTimestamp = checkTimestamp;
            reload();
            ofLogNotice() << "["<<path<<"] file reloaded";
        }
    }
}

void np::LiveParameters::reload(){
    ofJson json = ofLoadJson( path );
    ofDeserialize( json, *parameters );
}
