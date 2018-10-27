#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

#include "General.h"
#include "Sprite.h"

class Object {
public:
	void init(char* spr, const glm::ivec2 &Pos, int d, ShaderProgram &shaderProgram);
	void render();
	void update(int deltaTime);
	int damage();
	glm::ivec2 getPos();
private:
	glm::ivec2 PosObject;
	Sprite *sprite;
	Texture spritesheet;
	int dmg;
	void LoadSprite(char* spr, ShaderProgram &shaderProgram);
};
#endif