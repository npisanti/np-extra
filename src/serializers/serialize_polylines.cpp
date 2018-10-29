
#include "serialize_polylines.h"

void np::serialize_polylines( std::string path, const std::vector<ofPolyline> & v ) {

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

void np::deserialize_polylines( std::string path, std::vector<ofPolyline> & v ){

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
            ofLogError( "error while loading polylines from xml, no polys tag found" );
        }
    }else{
        ofLogError( "error loading xml file" );
    }
}


void np::serialize_polylines( std::string path, const std::vector<std::vector<ofPolyline>> & v ){

    ofXml xml; 
    ofXml root = xml.appendChild("root"); 
    
    for ( size_t i=0; i<v.size(); ++i ){
    
        ofXml poly = root.appendChild("poly");

        for ( size_t k=0; k<v[i].size(); ++k ){
            auto & vertices =  v[i][k].getVertices();

            if(!vertices.empty()){
                ofXml line = poly.appendChild("line");
                for( size_t k=0; k<vertices.size(); ++k ){
                    auto pt = line.appendChild("pt");
                    pt.setAttribute("x", vertices[k].x );
                    pt.setAttribute("y", vertices[k].y );
                    pt.setAttribute("z", vertices[k].z );        
                }            
            }
        }
        
    }
        
    if( !xml.save( path ) ){
        ofLogError()<< "error saving serialized points";
    }
}

void np::deserialize_polylines( std::string path, std::vector<std::vector<ofPolyline>> & v ){
    
    ofXml xml;

    if( xml.load( path ) ){ 
        
        auto root = xml.getChild("root");
        
        if( root ){
            v.clear();

            auto polys = root.getChildren("poly");
            
            int i = 0;
            for( auto & poly : polys ){
                v.emplace_back();

                auto lines = poly.getChildren("line");

                for( auto & line : lines ){
                    v[i].emplace_back();

                    auto pts = line.getChildren("pt");
                    for( auto & pt: pts ){
                        auto x = pt.getAttribute("x").getFloatValue();
                        auto y = pt.getAttribute("y").getFloatValue();
                        auto z = pt.getAttribute("z").getFloatValue();
                        v.back().back().addVertex( x, y, z );
                    }                
                }

                i++;
            }
        }else{
            ofLogError( "error while loading polylines from xml, no polys tag found" );
        }
    }else{
        ofLogError( "error loading xml file" );
    }
}
