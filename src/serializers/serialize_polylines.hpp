
#ifndef NPEXTRA_SERIALIZE_POLYLINES_H 
#define NPEXTRA_SERIALIZE_POLYLINES_H 


#include "ofMain.h"

namespace np {
    
    inline void serialize_polylines( std::string path, const std::vector<ofPolyline> & v ) {

        ofXml xml; 
        ofXml root = xml.appendChild("polys"); 
        
        for ( size_t i=0; i<v.size(); ++i ){
        
            auto & vertices =  v[i].getVertices();
        
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
            
        if( !xml.save( path ) ){
            ofLogError()<< "error saving serialized points";
        }
    }

    inline void deserialize_polylines( std::string path, std::vector<ofPolyline> & v ){

        ofXml xml;

        if( xml.load( path ) )  { 
            
            auto root = xml.getChild("polys");
            
            if( root ){
                v.clear();
                //int size = v.size();
                auto lines = root.getChildren("line");
                
                for( auto & line : lines ){
                    v.emplace_back();
                    
                    auto pts = line.getChildren("pt");
                    for(auto & pt: pts){
                        auto x = pt.getAttribute("x").getFloatValue();
                        auto y = pt.getAttribute("y").getFloatValue();
                        auto z = pt.getAttribute("z").getFloatValue();
                        v.back().addVertex( x, y, z );
                    }                
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

#endif //NPEXTRA_SERIALIZE_POLYLINES_H 
