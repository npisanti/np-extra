
#include "SpriteSheet.h"

np::SpriteSheet::SpriteSheet()
{
	bInitialized = false;
    sw = sh = 0;
    offset = glm::vec2( 0, 0 );
}

bool np::SpriteSheet::load( std::string path, int spriteWidth, int spriteHeight, int mode )
{
    bool loaded = png.load( path );

    if( loaded ){
        sw = spriteWidth;
        sh = spriteHeight;
        frames = png.getWidth() / sw;
        
        switch( mode ){
            case 0:
                offset.x = 0;
                offset.y = -sh;
            break;
            
            case 1:
                offset.x = -sw/2;
                offset.y = -sh/2;
            break;
            
            default: 
                offset.x = 0;
                offset.y = 0;
            break;
        }
        
        cursor = 0;

        setupSpriteVbo();
        bInitialized = true;
        
        name = ofFilePath::removeExt( ofFilePath::getFileName( path ) );
        
        return true;
    }else{
        ofLogError()<<"[np-pixelscript] invalid spritesheet path\n";
        return false;
    }
}

void np::SpriteSheet::setFrame( int index )
{
    cursor = index;
    if(cursor>=frames){
        cursor = frames-1;
    }
    if( cursor < 0 ){ 
        cursor = 0; 
    }
}

void np::SpriteSheet::setPlayhead( double pct ){
    if( pct < 0.0f ){
        pct = 0.0f;
    }
    if( pct >=1.0 ){
        pct = 0.9999999;
    }
    cursor = pct * frames;
}

void np::SpriteSheet::draw(float x, float y)
{
	if (!bInitialized) {
		return;
	}
    
	ofPushMatrix();
	ofTranslate( x + offset.x, y + offset.y );

#ifdef NPSPRITE_USE_TRIANGLE_STRIP
	vbo.draw(GL_TRIANGLE_STRIP, cursor*4, 4);
#else
	vbo.draw(GL_TRIANGLES, cursor*6, 6);
#endif

	ofPopMatrix();
}

void np::SpriteSheet::bind()
{
    png.getTexture().bind();
}

void np::SpriteSheet::unbind()
{
    png.getTexture().unbind();
}

void np::SpriteSheet::setupSpriteVbo()
{
	std::vector<glm::vec2> verts;
	std::vector<glm::vec2> texCoords;

	glm::vec2 topright(sw, 0);
	glm::vec2 bottomleft(0, sh);
	glm::vec2 bottomright(sw, sh);

	glm::vec2 origin(0, 0);
    
	for (int i=0; i<frames; i++)
	{
		// first triangle
		verts.push_back(glm::vec2(0, 0));
		texCoords.push_back(origin);

		verts.push_back(glm::vec2(sw, 0));
		texCoords.push_back(origin + topright);

		verts.push_back(glm::vec2(0, sh));
		texCoords.push_back(origin + bottomleft);

		verts.push_back(glm::vec2(sw, sh));
		texCoords.push_back(origin + bottomright);

		// advance origin
		origin.x += sw;

		if (origin.x + sw > png.getTexture().getWidth()) {
			origin.y += sh;
			origin.x = 0;
		}
	}

	vbo.setVertexData(&verts[0], verts.size(), GL_STATIC_DRAW);
	vbo.setTexCoordData(&texCoords[0], texCoords.size(), GL_STATIC_DRAW);
}

