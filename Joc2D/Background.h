#ifndef _BACKGROUND_INCLUDE
#define _BACKGROUND_INCLUDE

#include "General.h"
#include "Texture.h"
#include "Sprite.h"


class Background {
public:
	Background();

	void init(char* back, glm::ivec2 size, ShaderProgram &shaderProgram);
	void render();
	glm::ivec2 getSize();

	
private:

	Texture text;
	Sprite *sprite;
	glm::ivec2 bg_size;
};

#endif

