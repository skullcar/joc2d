#ifndef _BACKGROUND_INCLUDE
#define _BACKGROUND_INCLUDE

#include "General.h"
#include "Texture.h"
#include "Sprite.h"

struct f {
	Sprite *sprite;
	glm::ivec2 bg_size;
	glm::vec2 bg_frame;
};

class Background {
public:
	Background();

	void init(char * back, glm::ivec2 size,glm::vec2 frame,ShaderProgram &shaderProgram);
	void render();
	glm::ivec2 getSize();
	void addAnimation();
	void update(int deltaTime);

	
private:

	Texture text;
	vector<f> fons;
	Sprite *sprite;
	glm::ivec2 bg_size;
	glm::vec2 bg_frame;
	
};

#endif

