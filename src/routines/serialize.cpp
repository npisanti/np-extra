
#include "serialize.h"

void np::serialize_floats( std::string path, const std::vector<float> & v ){
    ofXml xml; 

    for ( size_t i=0; i<v.size(); ++i ){
        auto pt = xml.appendChild("number");
        pt.setAttribute("value", v[i] );
    }
        
    if( !xml.save( path ) ){
        ofLogError()<< "error saving serialized points";
    }
}

void np::deserialize_floats( std::string path, std::vector<float> & v ){
    ofXml xml;

    if( xml.load( path ) )  { 

        auto numbers = xml.getChildren("number");

        v.clear();        
        int size = 0;
        for( auto & num: numbers ){
            size++; // don't worry about the warning here
            // this is needed to allocate memory just once
        }
        v.reserve( size );
        
        for(auto & num: numbers){
            float value = num.getAttribute("value").getFloatValue();
            v.push_back( value );
        }
    }else{
        ofLogError( "error loading xml file" );
    }
}

void np::serialize_points( std::string path, const std::vector<glm::vec3> & v ) {

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

void np::deserialize_points( std::string path, std::vector<glm::vec3> & v ) {

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

void np::serialize_points( std::string path, const std::vector<ofVec3f> & v ) {

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

void np::deserialize_points( std::string path, std::vector<ofVec3f> & v ) {

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
