
#include "pngfolder.h"

void np::load_png_folder( std::string path, std::vector<ofImage> & images ){
    
    ofDirectory dir;
	dir.listDir( path );
	dir.allowExt("png");
    dir.sort();

	if( dir.size() ){
		images.assign(dir.size(), ofImage());
	}

	for(int i = 0; i < (int)dir.size(); i++){
		images[i].load(dir.getPath(i));
	}
}
