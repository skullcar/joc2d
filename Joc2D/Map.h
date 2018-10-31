#ifndef _MAP_INCLUDE
#define _MAP_INCLUDE

#include "General.h"
#include "Background.h"
#include "Object.h"
#include "cMusic.h"

class Map {
public:
	Map();

	void init(ShaderProgram &shaderProgram, glm::ivec2 &size);
	void render();
	void update(int deltaTime);
	int collisionDown(glm::ivec2 Pos, glm::ivec2 size);
	int collisionUp(glm::ivec2 Pos, glm::ivec2 size);
	int collisionLeft(glm::ivec2 Pos, glm::ivec2 size);
	int collisionRight(glm::ivec2 Pos, glm::ivec2 size);
	void SetCx(int cx);
	void LoadObject(char* spr, const glm::ivec2 &Pos, int d, ShaderProgram &shaderProgram);
	void AddMusic(cMusic m);
	void playerdoDMG(glm::vec2 Pos,int dmg,glm::vec2 hb,int dist);
	bool ObjectDamage(glm::vec2 hbc, glm::vec2 hb, int dmg);

private:
	Background back;
	glm::ivec2 floor_size;
	int c_x;
	list<Object*> objects;
};

#endif
