
#ifndef NPEXTRA_SERIALIZE_POINTS_H
#define NPEXTRA_SERIALIZE_POINTS_H

#include "ofMain.h"

namespace np {

    inline void serialize_points( std::string path, const std::vector<glm::vec3> & v ) {

        ofXml xml; 
        ofXml points = xml.appendChild("points"); 
        
        for ( size_t i=0; i<v.size(); ++i ){
            auto pt = points.appendChild("pt");
            pt.setAttribute("x", v[i].x );
            pt.setAttribute("y", v[i].y );
            pt.setAttribute("z", v[i].z );
        }
            
        if( !xml.save( path ) ){
            ofLogError()<< "error saving serialized points";
        }
    }

    inline void deserialize_points( std::string path, std::vector<glm::vec3> & v ) {

        ofXml xml;

        if( xml.load( path ) )  { 
            
            auto root = xml.getChild("points");
            
            if( root ){
                v.clear();
                //int size = v.size();
                auto pts = root.getChildren("pt");
                for(auto & pt: pts){
                    auto x = pt.getAttribute("x").getFloatValue();
                    auto y = pt.getAttribute("y").getFloatValue();
                    auto z = pt.getAttribute("z").getFloatValue();
                    v.push_back( glm::vec3(x, y, z) );
                }
                //if(size > v.size()) v.resize(size);
            }else{
                ofLogError( "error while loading points from xml, no points tag found" );
            }
        }else{
            ofLogError( "error loading xml file" );
        }
    }



    inline void serialize_points( std::string path, const std::vector<ofVec3f> & v ) {

        ofXml xml; 
        ofXml points = xml.appendChild("points"); 
        
        for ( size_t i=0; i<v.size(); ++i ){
            auto pt = points.appendChild("pt");
            pt.setAttribute("x", v[i].x );
            pt.setAttribute("y", v[i].y );
            pt.setAttribute("z", v[i].z );
        }
            
        if( !xml.save( path ) ){
            ofLogError()<< "error saving serialized points";
        }
    }

    inline void deserialize_points( std::string path, std::vector<ofVec3f> & v ) {

        ofXml xml;

        if( xml.load( path ) )  { 
            
            auto root = xml.getChild("points");
            
            if( root ){
                v.clear();
                //int size = v.size();
                auto pts = root.getChildren("pt");
                for(auto & pt: pts){
                    auto x = pt.getAttribute("x").getFloatValue();
                    auto y = pt.getAttribute("y").getFloatValue();
                    auto z = pt.getAttribute("y").getFloatValue();
                    v.push_back( ofVec3f(x, y, z) );
                }
                //if(size > v.size()) v.resize(size);
            }else{
                ofLogError( "error while loading points from xml, no points tag found" );
            }
        }else{
            ofLogError( "error loading xml file" );
        }
    }

}

#endif //NPEXTRA_SERIALIZE_POINTS_H
